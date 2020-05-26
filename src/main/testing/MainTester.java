package main.testing;

import math.wrapper.Equation;
import math.wrapper.EquationSet;

/**
 * Tester/main class
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class MainTester {
	public static void main(String[] args) {
		EquationSet set = new EquationSet();
		set.addEquation("(e^x + 200)^2");
		set.addEquation("e^(a*pi) - x*phi");
		set.set('x', 15d);
		set.set('a', 2d);
		set.calculate();
		
		Equation eq = new Equation("floor(x^15) + x^2 + 5*x");
		System.out.println(eq.equals(new Equation("floor(x^15) + x^2 + 5*x")));
	}
}
