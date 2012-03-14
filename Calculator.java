import java.lang.System.*;
import org.ow2.dsrg.jpmf.util.*;

public class Calculator {
	public static void main(String args[]) {
		System.out.println("Hello, world!");
		Calculator calc = new Calculator();
		int result = calc.add(2,2);
		System.out.println("The result is: "+result);
	}

	public int add(int a, int b) {
		return a + b + magic;
	}

	int magic = 5;
}
