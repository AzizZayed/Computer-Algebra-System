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
				"x*y*z*w*a*sinx*s*c*d"); 
		LatexRenderer.render(eq);
		LatexRenderer.render(eq.simplified());
		LatexRenderer.render(eq.simplified().simplified());
		LatexRenderer.render(eq.simplified().simplified().simplified());
//		LatexRenderer.render(eq);
		
//		System.out.println(Math.acos(1d));
//		System.out.println(Math.floor(Math.acos(1d)) == 0d);

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