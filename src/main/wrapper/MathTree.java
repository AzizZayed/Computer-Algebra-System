package main.wrapper;

import javax.swing.JOptionPane;

import org.scilab.forge.jlatexmath.TeXConstants;
import org.scilab.forge.jlatexmath.TeXFormula;
import org.scilab.forge.jlatexmath.TeXIcon;

import math.structure.Constant;
import math.structure.Expression;
import math.structure.Fraction;
import math.structure.IMath;
import math.structure.Operator.Product;
import math.structure.Operator.Sum;
import math.structure.Parser;
import math.structure.Power;
import math.structure.Power.Exp;
import math.structure.TrigonometricFunction.Cos;
import math.structure.TrigonometricFunction.Sin;
import math.structure.TrigonometricFunction.Tan;
import math.structure.Variable;

/**
 * class containing the expression tree: the entire expression
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class MathTree implements IMath {

	private String expression; // the inputed expression
	private Expression root; // the root of the expression tree

	/*
	 * Constructor with expression
	 */
	public MathTree(String exp) {
		expression = Parser.clean(exp);
		root = Parser.parseExpression(expression);
	}

	/*
	 * constructor with default expression
	 */
	public MathTree() {
		root = new Fraction(
				new Sum(new Exp(new Power(new Variable(), new Constant(1d / 2d))),
						new Product(new Constant(2), new Variable()), new Fraction(new Constant(1), new Variable())),
				new Product(new Power(new Variable(), new Constant(1d / 2d)),
						new Sin(new Cos(new Tan(new Variable())))));
	}

	/**
	 * get the value of the expression with the given values for the variables
	 * @param x - value of x
	 * @return the value of the expression at the given values
	 */
	public double valueAt(double x) {
		if (root == null)
			throw new NullPointerException("The expression is empty.");
		return root.evaluate(x);
	}

	@Override
	public String toString() {
		if (root == null)
			throw new NullPointerException("The expression is empty.");
		return "Tree Expression: " + root.toString();
	}

	/**
	 * @return the inputed expression, a cleaned version
	 */
	public String getExpression() {
		return expression;
	}

	@Override
	public String toLatex() {
		String latex = root.toLatex();
//		System.out.println(latex.substring(230));

		// create a formula
		TeXFormula formula = new TeXFormula(latex);

		// render the formla to an icon of the same size as the formula.
		TeXIcon icon = formula.createTeXIcon(TeXConstants.STYLE_DISPLAY, 20);

		JOptionPane.showMessageDialog(null, "", "LaTeX", JOptionPane.PLAIN_MESSAGE, icon);

		return latex;
	}
}