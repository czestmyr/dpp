#ifndef _ARGLIB_OPTION_SYNTAX_H_
#define _ARGLIB_OPTION_SYNTAX_H_

#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>
#include "Type.h"
#include "ParameterAttribute.h"
#include "OptionAttribute.h"

typedef std::list<std::string>::iterator StrListIt;

/// \brief Class that holds information about syntax of the options.
/// This class can be used to set new options together with their parameters. It is also able to print help for all
/// the options that were defined.
class OptionSyntax {
	public:
		OptionSyntax();
		OptionSyntax(const OptionSyntax& other);
		~OptionSyntax();

		/// Assignment operator.
		/// The old options that were saved into this object are deleted and the whole syntax is copied fron
		/// the other object.
		/// @param other The object from which to copy the syntax.
		/// @return Reference to this OptionSyntax object.
		OptionSyntax& operator=(const OptionSyntax& other);

		/// Adds an option to the syntax held by this object.
		/// @param optionName Name of the newly added option.
		/// @param optionAttrib The attribute of the new option.
		///	Possible values are OPTION_ALLOWED and OPTION_REQUIRED.
		/// @param paramType Pointer to a Type instance that specifies type of this option's parameter.
		///	The ownership of the Type instance is transfered to the OptionSyntax object.
		/// @param paramAttrib Attribute of the parameter. Defines whether the parameter is optional,
		///	allowed or required. Possible values are PARAM_REQUIRED, PARAM_ALLOWED amd PARAM_FORBIDDEN
		void addOption(const std::string& optionName, OptionAttribute optionAttrib, Type* paramType, ParameterAttribute paramAttrib);

		/// Adds an option that is synonymous to another option.
		/// All the properties (option attribute and parameter type and attribute) are retained from the
		/// original option. This basically just specifies another way to set the option. Both names will
		/// have the same option id (see OptionSyntax::getId()) and will point to the same option.
		/// @param original Name of the original option (e.g. "version")
		/// @param synonym Name of the synonym (e.g. "v")
		void addSynonym(const std::string& original, const std::string& synonym);

		/// Returns the attribute of the given option.
		/// The option can be specified by any of the so-far defined synonyms for it.
		/// @param option Name of the option.
		/// @return attribute that says whether the option is allowed or required.
		ParameterAttribute getAttribute(const std::string& option) const;

		/// Returns the type of the parameter of a given option.
		/// The option can be specified by any of the so-far defined synonyms for it.
		/// @param option The name of the option.
		/// @return Type of the option's parameter. If the option has no parameter, DummyType is returned.
		const Type* getParameterType(const std::string& option) const;

		/// Sets a help string for the given option.
		/// The option can be specified by any of the so-far defined synonyms for it.
		/// If this method is not called, the default help string is used that informs about lack of
		/// documentation for the option ;-)
		/// @param option Name of the option.
		/// @param helpString Help for this option.
		void setOptionHelp(const std::string& option, const std::string& helpString);

		/// Writes help for all options into the given output stream.
		/// The size of the terminal can be set so that the text wraps naturally.
		/// @param stream Output stream the help should be written into.
		/// @param terminalSize Width of the desired output width in characters.
		void writeHelp(std::ostream& stream, int terminalSize) const;

		/// Returns identification number of the option with a given name.
		/// The option can be specified by any of the so-far defined synonyms for it. In fact, the definition
		/// of a synonymous option is that it has the same id. The id can be used in calls to ArgumentData.
		/// @return Id of the option.
		unsigned int getId(const std::string& option) const;

		/// Returns a set of the options that have to be set in order for the parsing to succeed.
		/// @return A std::set of the required option Ids (see OptionSyntax::getId()).
		const std::set<unsigned int>& getRequiredOptions() const;
	private:
		/// Internal deinitializing function. Called e.g. in the destructor.
		void deinit();
		/// Initializes the data members from another object.
		/// @param other The object to copy the data from.
		void initFrom(const OptionSyntax& other);

		/// Returns a new and unique Id number that can be used in a new option.
		/// @return a unique option Id.
		unsigned int getUnusedId();

		unsigned int lastId; ///< Recently assigned unique option Id.

		/// Tells, whether the given option was already defined with the OptionSyntax::addOption() method.
		/// @param optionName Any of the synonymous names for the option.
		/// @return true when the option was defined, false otherwise.
		bool isOptionDefined(const std::string& optionName) const;

		/// Writes synonyms for the given option to the given output stream. Used in OptionSyntax::writeHelp().
		/// @param id the unique Id for the option
		/// @param stream output stream for the write.
		void writeSynonyms(unsigned int id, std::ostream& stream) const;

		/// Writes parameters of the given option to the given output stream. Used in OptionSyntax::writeHelp().
		/// @param id the unique Id for the option
		/// @param stream output stream for the write.
		void writeParameter(unsigned int id, std::ostream& stream) const;

		/// Writes a string into the given stream obeying the character limit. The string is divided into words
		/// separated by whitespace and these words are written into the stream so that the length of each line
		/// does not exceed the given limit. Used in OptionSyntax::writeHelp().
		/// @param string the string that should be written into the stream
		/// @param limit How many characters can fit into one line.
		/// @param stream output stream for the write.
		void writeWithLimit(std::string& string, int limit, std::ostream& stream) const;

		/// Writes out words from a string list into an output stream so that they form a line. Each line is
		/// prepended by two tabulator characters.
		/// @param lineBegin iterator pointing at the first word of the line.
		/// @param lineEnd iterator pointing at one word after the last word of the line.
		/// @param stream output stream to write into.
		void writeOutLine(StrListIt lineBegin, StrListIt lineEnd, std::ostream& stream) const;

		std::map<std::string, unsigned int> ids;                    ///< Map of all option names to unique Ids
		std::multimap<unsigned int, std::string> synonyms;          ///< Map of synonymous names for each Id
		std::map<unsigned int, ParameterAttribute> paramAttributes; ///< Parameter attributes for each option
		std::map<unsigned int, Type*> types;                        ///< Parameter types for each option
		std::map<unsigned int, std::string> helpStrings;            ///< Help strings for each option

		std::set<unsigned int> requiredOptions; ///< Set of options that have to be set for a successful parse.
};

#endif

