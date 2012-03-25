package org.ow2.dsrg.jpmf.util;

import java.lang.annotation.Documented;
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Utility class for configuration and validation of configurable objects.
 * <p>
 * A configurable object is an object that exposes configurable properties. A
 * configurable property is a simple field annotated with the {@link Property}
 * annotation. The values of the properties (i.e. fields) are set using
 * introspection. There are two ways to configure the value of a configurable
 * field:
 * <p>
 * <ol>
 * <li>If the field type is class that provides either a string constructor
 * (i.e. a constructor with a single {@code String} parameter) or a static
 * factory method {@code valueOf (String)} returning an instance of the class,
 * then the value of the field is set to an instance of the field type created
 * from a string representation of the value.</li>
 * <li>If creating instances of the field type is more complex, the field value
 * can be set through a method annotated with the {@link Setter} annotation.
 * Such a method must have a setter signature, i.e. it must return {@code void}
 * and accept a single {@code String} parameter.</li>
 * </ol>
 * <p>
 * Configurable properties of an object can be set using the
 * {@link #set(Object, String, String) set()} method, while validation of object
 * properties can be achieved using the {@link #check(Object) check()} method.
 * The validation ensures that no field representing a mandatory configurable
 * property contains {@code null}.
 */
public class Configurator {

    public static Logger log = Logger.getAnonymousLogger();

    /* ***********************************************************************
     * ANNOTATIONS
     * ***********************************************************************/

    @Documented
    @Retention ( RetentionPolicy.RUNTIME )
    @Target ( ElementType.FIELD )
    public @interface Property {

        /**
         * Returns the name of the configuration property held in the annotated
         * field.
         *
         * @return
         *      name of the property held in the annotated field, or empty
	 *      string indicating that the name is identical to the field name
         */
        String name() default "";

        /**
         * Determines whether the property is required or not.
         *
         * @return
         *      {@code true} if the property must have a non-null value,
         *      {@code false} otherwise
         */
        boolean required() default true;

        /**
         * Returns the string representation of the default value of the
         * annotated field. Empty string indicates that the default value
         * has not been set.
         *
         * @return
         *      string representation of the default value
         */
        String defaultValue() default "";

        /**
         * Returns an optional description of the property held in the
         * annotated field.
         *
         * @return
         *      name
         */
        String description() default "";
    }

    @Documented
    @Retention ( RetentionPolicy.RUNTIME )
    @Target ( ElementType.METHOD )
    public @interface Setter {

        /**
         * Returns the name of the property configured by the annotated method.
         *
         * @return
         *      name of the property configured by the annotated method, or
         *      empty string indicating that the name corresponds to method
         *      name without the "set" prefix with the first letter in lowercase
         */
        String name() default "";
    }

    /* ***********************************************************************
     * PUBLIC METHODS
     * ***********************************************************************/

    /**
     * Sets the given property to the given value in the given configurable
     * object. 
     *
     * @param object
     *      target configurable object to set the property on
     * @param name
     *      property name
     * @param value
     *      property value
     * @throws ConfigurationException
     *      if the value of the given property cannot be set on the
     *      given object
     */
    public static void setProperty (
        Object object,
        String name,
        String value
    ) {
        //
        // First try to obtain a method based setter, which is necessary
        // for more complex properties. If that fails, try to obtain a
        // field based setter, assuming the property is simple enough to
        // convert to object instance. If that also fails, log a warning.
        //
        Method propertySetter = findPropertySetter ( object, name );
        if ( propertySetter != null ) {
            try {
                trace ( "setting method property %s to %s", name, value );
                setUsingMethod ( propertySetter, object, value );
            } catch ( Exception e ) {
		String fmt = "Unable to set property %s=%s using method %s()";
                wrap ( e, fmt, name, value, propertySetter.getName() );
            }
            return;
        }
        
        Field property = findProperty ( name, object );
        if ( property != null ) {
            trace ( "setting field property %s to %s", name, value );
            setDirectly ( name, object, value, property );
            return;
        }

        if ( log.isLoggable ( Level.WARNING ) ) {
            String fmt = "Unable to find configuration method for property %s";
            log.log ( Level.WARNING, fmt, name );
        }
        return;
    }

    /**
     * Checks if all configurable fields in the passed object are not null.
     *
     * @param object
     *      object with configurable fields
     */
    public static void check ( Object object ) {
        //
        // Find all configurable fields and make sure that all mandatory
        // fields have a non-null value. If any configurable field with
        // a null value is found and has a default value specified, an
        // instance of the value is created and the field is initialized
        // to the default value.
        //
        // If any mandatory field remains uninitialized, throw an exception.
        //

        try {
            for ( Field field : new FieldsIterable ( object.getClass() ) ) {
                //
                // Skip fields without the @Property annotation or fields
                // with non-null value.
                //
                Property property = field.getAnnotation ( Property.class );
                if ( property == null ) continue;

                Object oldValue;

                //
                // Make the field accessible before getting its value and
                // restore the previous accessibility state after that.
                //
                boolean accessibility = field.isAccessible();
                field.setAccessible ( true );
                oldValue = field.get ( object );
                field.setAccessible ( accessibility );

                //
                // Set default value for null fields.
                //
                if ( oldValue != null ) continue;

                String name;
	        if ( property.name().length() > 0 ) {
		    name = property.name();
		} else {
		    name = field.getName();
		}

                if ( property.defaultValue().length() == 0 ) {
                    if ( property.required () ) {
			String fmt = "Required property '%s' is not configured";
                        throw new ConfigurationException ( fmt, name );
                    } else {
		        continue;
		    }
		}

	        String fmt = "setting field property %s to default value %s";
                trace ( fmt, name, property.defaultValue() );
                setDirectly ( name, object, property.defaultValue(), field );
            }
        } catch ( ConfigurationException ce ) {
            // propagate without wrapping
            throw ce;
        } catch ( Exception e ) {
            wrap ( e, "Unable to verify object property configuration!" );
        }
    }

    /* ***********************************************************************
     * Field-based properties
     * ***********************************************************************/

    /**
     * Finds a field-based property of an object.
     * The Field has to be correctly annotated and the annotation name has to 
     * match the supplied name argument.
     *
     * @param name
     *      name of the property that is to be found
     * @param target
     *      target object on which to perform the search
     *
     * @return
     *      the found property
     */
    static Field findProperty ( final String name, final Object target ) {
        //
        // Find a configurable field for the given property and create a
        // PropertySetter for the property.
        //
        // Specifically, enumerate all fields in the given object's class
        // hierarchy and find the first field annotated with the
        // @Property annotation matching the given property field.
        //
        for ( final Field field : new FieldsIterable ( target.getClass() ) ) {
            Property property = field.getAnnotation ( Property.class );
            String propertyName = null;
            if ( property != null && property.name().length() <= 0 ) {
                propertyName = field.getName();
            }

            if ( name.equals ( propertyName ) ) {
                return field;
            }
        }

        //
        // No match found.
        //
        return null;
    }

    /**
     * Sets the given field of the given object to the given value. The
     * value is converted from string representation to an instance of
     * the field type.
     *
     * @param name
     *      name of the property being configured
     * @param object
     *      target object on which to set the field value
     * @param value
     *      string value of the property being configured
     * @param field
     *      the field to set to the given value
     *
     * @throws ConfigurationException
     *      if the string representation of the value could not be
     *      converted to an instance of the field type or if setting
     *      the field failed
     */
    static void setDirectly (
        String name,
	Object object,
	String value,
	Field field
    ) {
        //
        // Create an instance of the property value and set the field
        // value on the target object.
        //
        Object typedValue = makeValueInstance ( field, value );
        if ( typedValue == null ) {
            String fmt = "property %s: could not create %s instance for %s";
	    String typeName = field.getType().getName();
            throw new ConfigurationException ( fmt, name, typeName, value );
        }

        try {
            //
            // Make the field accessible before setting its value and
            // restore the previous accessibility state after that.
            //
            boolean accessibility = field.isAccessible();
            field.setAccessible ( true );
            field.set ( object, typedValue );
            field.setAccessible ( accessibility );
        } catch ( Exception e ) {
	    String fmt = "Unable to configure field %s with property %s=%s";
            wrap ( e, fmt, field.getName(), name, value );
        }
    }

    /* ***********************************************************************
     * Method-based properties
     * ***********************************************************************/

    /**
     * Returns a setter method that sets a property of the given name.
     *
     * @param target
     *      target object on which to set the property
     * @param name
     *      name of the property to set
     * @return
     *      setter method that can be used to set the given property
     */
    static Method findPropertySetter ( final Object target, final String name ){
        Class <?> targetClass;
  
        //
        // Find a setter method for the given property and create a
        // PropertySetter for the property.
        //
        // Specifically, enumerate all methods in the given object's class
        // hierarchy and find the first setter method annotated with the
        // @Setter annotation matching the given property field.
        //
        targetClass = target.getClass();
        do {
            for ( final Method method : targetClass.getDeclaredMethods() ) {
                Setter setter = method.getAnnotation ( Setter.class );
                if ( setter == null ) {
                    continue;
                }
      
                String propertyName = setter.name();
                if ( propertyName.length() == 0 ) {
                    propertyName = getPropertyName ( method.getName() );
                }
      
                if ( name.equals ( propertyName ) ) {
                    return method;
                }
            }
            targetClass = targetClass.getSuperclass();
        } while ( targetClass != null );
        //
        // No match found.
        //
        return null;
    }

    /**
     * Calls the method on target and adds value as a parametr. If necessary
     * makes the method accessible from this point.
     *
     * @param method
     *      method wchich is called to set the propetry
     * @param target
     *      object on which is the method called
     * @param value
     *      value which should be setted using method
     */
    static void setUsingMethod(
        Method method,
	Object target,
	String value
    ) throws Exception {
        boolean hasMoreParameters = method.getParameterTypes().length != 1;
        boolean hasReturnValue =
            ( Class <?> ) method.getReturnType() != void.class;
        boolean hasBadType = method.getParameterTypes() [ 0 ] != String.class;
        if ( hasReturnValue || hasBadType || hasMoreParameters ) {
            String fmt = "method %s() is not a setter";
            throw new ConfigurationException ( fmt, method.getName() );
        }
  
        boolean accessibility = method.isAccessible();
        method.setAccessible ( true );
        method.invoke ( target, value );
        method.setAccessible ( accessibility );
    }

    /* ***********************************************************************
     * Helper methods
     * ***********************************************************************/

    /**
     * Creates an object instance from the string representation of a property
     * value. The instance type is determined by the type of the given field and
     * the instance is created either by calling a string constructor or a
     * static factory method on the field class.
     *
     * @param field
     *      field to create value for
     * @param value
     *      string representation of field value
     * @return
     *      an object of the given field type representing the given value, or
     *      {@code null} if the instance could not be created
     */
    static Object makeValueInstance ( Field field, String value ) {
        // First try to create the value instance by invoking a string
	// constructor of the field class.
        Class <?> fieldType = field.getType();

        try {
            Constructor <?> fieldConstructor =
		fieldType.getConstructor ( new Class <?> [] { String.class } );
            return fieldConstructor.newInstance ( value );
        } catch ( Exception e ) {
            /* quell the exception and try the next method */
        }

        // If there is no suitable constructor, try to create the instance by
	// invoking a static factory method.
        try {
            Method method = fieldType.getMethod (
	        "valueOf",
		new Class <?> [] { String.class } 
	    );
            if ( fieldType.isAssignableFrom( method.getReturnType() ) ) {
              return method.invoke ( null, value );
            }
        } catch ( Exception e ) {
            /* quell the exception */ 
        }

        // Could not create the instance, return null.
        return null;
    }

    /**
     *  Finds the name of the set property when given name of the setter.
     *  If the methodName starts with "set", strips the prefix and lower cases
     *  the first letter of the suffix.
     *
     *  @param methodName
     *       name of the method which is
     *  @return 
     *       name without beginning "set" if exist
     */
    static String getPropertyName ( String methodName ) {
        if ( methodName.startsWith( "set" ) ) {
            return methodName.substring ( 3, 4 ).toLowerCase() +
		   methodName.substring( 4 );
        } else {
            return methodName;
        }
    }

    /* ***********************************************************************
     * Logging
     * ***********************************************************************/

    private static void trace ( String format, Object ... args ) {
        if ( log.isLoggable ( Level.FINE ) ) {
            log.log ( Level.FINE, format, args );
        }
    }

    /* ***********************************************************************
     * ConfigurationException
     * ***********************************************************************/

    /**
     * Common exception for all configuration errors.
     */
    public static class ConfigurationException extends RuntimeException {
        ConfigurationException ( String format, Object ... args ) {
            super ( String.format ( format, args ) );
        }

        ConfigurationException ( Throwable e, String format, Object ... args ) {
            super ( String.format ( format, args ), e );
        }
    }

    /**
     * Wraps the given {@link Throwable} as a {@link ConfigurationException}
     * along with an additional formatted message.
     */
    private static void wrap ( Throwable exc, String format, Object ... args ) {
        throw new ConfigurationException ( exc, format, args );
    }

    /* ***********************************************************************
     * FieldsIterable
     * ***********************************************************************/

    /**
     * Provides an iterable interface to fields declared in a class hierarchy.
     * The provided iterator traverses the inheritance hierarchy from the given
     * (leaf) class to the (root) base class and returns all fields declared in
     * the classes along the inheritance path. The iterator (obviously) does not
     * support element removal, since it operates on an immutable structure.
     */
    static class FieldsIterable implements Iterable <Field> {
        private Class <?> leaf;

        /**
         * Creates an iterable for the given leaf class. If the leaf class
         * is {@code null}, the iterable produces an empty iterator.
         */
        FieldsIterable ( Class <?> leafClass ) {
            leaf = leafClass;
        }

        @Override
        public Iterator <Field> iterator() {
            return new Iterator <Field>() {
                        
                private Class <?> currentClass = leaf;
    
                private Iterator <Field> fields =
		    new ArrayIterator <Field> ( new Field [ 0 ] );
    
                public boolean hasNext() {
                    //
                    // If there are no fields, check if there is another class
                    // where to look for fields. If we run out of classes, there
                    // are no more fields left.
                    //
                    while ( !fields.hasNext() ) {
                        if ( currentClass == null ) {
                            return false;
                        }
                        
			Field[] fieldArray = currentClass.getDeclaredFields();
                        fields = new ArrayIterator <Field> ( fieldArray );
                            
                        currentClass = currentClass.getSuperclass();
                    }
      
                    return true;
                }
    
                @Override
                public Field next() {
                    if ( !hasNext() ) {
                      throw new NoSuchElementException();
                    }
                    return fields.next();
                }
    
                public void remove() {
                    throw new UnsupportedOperationException();
                }
            };
        }
    }

    /* *******************************************************************
     * ArrayIterator
     * *******************************************************************/

    static class ArrayIterator <ElementType> implements Iterator <ElementType> {
        private ElementType [] array;
        private int length;
        private int pos;

        ArrayIterator ( ElementType [] elements ) {
            array = elements;
            length = elements.length;
            pos = 0;
        }

        @Override
        public void remove() {
            String msg = "cannot remove elements from array";
            throw new UnsupportedOperationException ( msg );
        }

        public boolean hasNext() {
            return pos < length;
        }

        @Override
        public ElementType next() {
            if ( !hasNext() ) {
                throw new NoSuchElementException();
            }
            return array [ pos++ ];
        }
    }
}
