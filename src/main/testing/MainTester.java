package main.testing;

import math.wrapper.Equation;

/**
 * Tester/main class
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class MainTester {
	public static void main(String[] args) {
//		EquationSet set = new EquationSet();
//		set.addEquation("(e^x + 200)^2");
//		set.addEquation("e^(a*pi) - x*phi");
//		set.set('x', 15d);
//		set.set('a', 2d);
//		set.calculate();
		
		Equation eq = new Equation("(e^sqrtx + (2 * x) + (1/x))/(sqrtx * sincostanx)");
		System.out.println(eq);
		eq.toLatex();
		
		Equation der = eq.derivative('x');
		System.out.println(der);
		der.toLatex();
		
	}
}
