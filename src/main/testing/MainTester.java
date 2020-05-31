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
		Equation eq = new Equation(
				"4*x*x*x*x^(-3)*a^x*b^x*e^x*e^x*a^x*5*6*a^x*c^(x + 5)*c^5*lna*lna*lna*lna + x + 5+ x+6");
		LatexRenderer.render(eq);
		LatexRenderer.render(eq.simplified().simplified().simplified());

//		System.out.println(eq);
//		System.out.println(eq.toLatex());
//		LatexRenderer.render(eq);
//			
//		Equation der = eq.derivative('x');
//		LatexRenderer.render(der);
//		
//		Equation simp = der.simplified();
//		LatexRenderer.render(simp);
//		
//		Equation eq = new Equation("absx");
//		System.out.println(eq.equals(new Equation("ceilx")));

//		Equation eq = new Equation("max(a*x, x^2, x^3, x^4, b*x^5)");
//		LatexRenderer.render(eq);
//		System.out.println(eq.valueAt(5.5d));

		// x^2 + sinx + absx + cosx + floorx
//		Expression[] expr = { // start
//				new Power(new Variable(), new Constant(2d)),
//				new Sin(new Variable()),
//				new Abs(new Power(new Variable(), new Constant(2d))),
//				new Abs(new Variable()),
//				new Cos(new Variable()),
//				new Floor(new Variable()),
//				}; // end

//		for (int i = 0; i < expr.length; i++) {
//			LatexRenderer.render(expr[i]);
//		}

//		Arrays.sort(expr, Product.SORTER);

//		for (int i = 0; i < expr.length; i++) {
//			LatexRenderer.render(expr[i]);
//		}

	}
}