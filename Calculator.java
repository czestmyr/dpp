import java.lang.System.*;
import java.lang.annotation.*;
import org.ow2.dsrg.jpmf.util.*;
import org.ow2.dsrg.jpmf.util.Configurator.*;

public class Calculator {
	public static void main(String args[]) {
		System.out.println("Hello, world!");

		Calculator calc = new Calculator();
		Configurator.set(calc, "magic", "41");
		Configurator.check(calc);

		int result = calc.add(2,2);
		System.out.println("The result is: "+result);
		calc.printDefault();
	}

	public int add(int a, int b) {
		return a + b + magic;
	}

	@Setter (name = "magic")
	public void setOddMagic(String newMagic) {
		int magicVal = Integer.parseInt(newMagic);
		if (magicVal % 2 == 1) {
			magic = magicVal;
			System.out.println("Magic was odd");
		} else {
			System.out.println("Magic was NOT odd");
		}
	}

	public void printDefault() {
		System.out.println("The default value is: " + defaultInt);
	}

	@Property (name = "magic", required = true)
	private Integer magic;

	@Property (name = "default", defaultValue = "15")
	private Integer defaultInt;
}
