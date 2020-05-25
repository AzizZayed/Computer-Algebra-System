package main.testing;

import math.wrapper.MathTree;

/**
 * Tester/main class
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class MainTester {
	public static void main(String[] args) {

		String exp;

		exp = "((x+3)*(x+2) + x^4 + 2*x^3 + 15*x)*(x+5)^2";
		exp = "((((x^2 + 4*x^3)*x)*x)^17 + (15*x + x^3 + x^5 + x^7 + x^2)^2^2)";
		exp = "((((x^2 + 4*x^3)*x)*x)^17.5 + (15*x + x^2)^2^2 + (x + 3)^2)";
		exp = "5*sin(3*x^2 + x + 12.5) + 5*tan5 + 5*cosx + 5*abs(x) + 5*floor(x) + ceil(x)";
		exp = "(e^(17*x^2 + 15*x^15) + (9*x^15)/(5*e^7) + (log_(5*x^2)_(x*e^(x^2)))^2)^2 + lnx + lne + ln7";
		exp = "floorx + ceil(x)^2 + abs(x)";
//		exp = "min((x +15)/(x+1), x*(x^2^2^2)x)";
//		exp = "-cos(x^2) - sinx + tanx*cscx + secx + cot(x)^2 + arccos(x^2) + arcsinx + arctanx";
//		exp = "sqrt(x^2)";
//		exp = "absx^2 + floorx^2 + ceilx^2";
		exp = "log_(2^x^4^7)_(x)";
//		exp = "(x^2 + 4)/(2*x^4) * 4";

		MathTree tree = null;

		try {
			tree = new MathTree(exp);
		} catch (IllegalArgumentException e) {
			System.out.println(e);
			System.exit(1);
		}

		System.out.println("Input: " + exp);
		System.out.println("Cleaned Input: " + tree.getExpression());
		System.out.println("Latex: " + tree.toLatex());

		double testVal = .5d;
		System.out.println(tree + " |x = " + testVal + " -> " + tree.valueAt(testVal));
	}
}
