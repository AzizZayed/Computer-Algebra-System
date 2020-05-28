package main.testing;

import math.wrapper.Equation;
import rendering.latex.LatexRenderer;

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
		
		// "(e^sqrtx + (2 * x) + (1/x))/(sqrtx * sincostanx)"
//		Equation eq = new Equation("(e^sqrtx + (2 * x) + (1/x))/(sqrtx * sincostanx)");
//		System.out.println(eq);
//		eq.toLatex();
//		
//		Equation der = eq.derivative('x');
//		System.out.println(der);
//		der.toLatex();
		
//		Equation eq = new Equation("absx");
//		System.out.println(eq.equals(new Equation("ceilx")));
		
		Equation eq = new Equation("max(a*x, x^2, x^3, x^4, b*x^5)");
		LatexRenderer.render(eq);
		System.out.println(eq.valueAt(5.5d));
		
	}
}