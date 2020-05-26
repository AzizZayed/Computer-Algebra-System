package math.wrapper;

import java.util.HashMap;
import java.util.HashSet;

import javax.swing.JOptionPane;

import org.scilab.forge.jlatexmath.TeXConstants;
import org.scilab.forge.jlatexmath.TeXFormula;
import org.scilab.forge.jlatexmath.TeXIcon;

import math.structure.Constant;
import math.structure.Expression;
import math.structure.Fraction;
import math.structure.IMath;
import math.structure.Parser;
import math.structure.Power;
import math.structure.Power.Exp;
import math.structure.Product;
import math.structure.Sum;
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
public class Equation implements IMath {

	private String expression; // the inputed expression
	private Expression root; // the root of the expression tree
	protected HashSet<Character> variables = new HashSet<Character>();

	/*
	 * Constructor with expression
	 */
	public Equation(String exp) {
		expression = Parser.clean(exp);
		try {
			root = Parser.parseExpression(expression, variables);
		} catch (IllegalArgumentException e) {
			System.out.println("ERROR: " + e);
		}
	}

	/*
	 * constructor with default expression
	 */
	public Equation() {
		root = new Fraction(
				new Sum(new Exp(new Power(new Variable(), new Constant(1d / 2d))),
						new Product(new Constant(2), new Variable()), new Fraction(new Constant(1), new Variable())),
				new Product(new Power(new Variable(), new Constant(1d / 2d)),
						new Sin(new Cos(new Tan(new Variable())))));
		variables.add('x');
	}

	/**
	 * get the value of the expression with the given values for the variables
	 * 
	 * @param varValues - values of each variable
	 * @return the value of the expression at the given values
	 */
	public double valueAt(HashMap<Character, Double> varValues) {
		if (root == null)
			throw new NullPointerException("The expression is empty.");
		return root.evaluate(varValues);
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
		if (root == null)
			throw new NullPointerException("The expression is empty.");
		String latex = root.toLatex();

		TeXFormula formula = new TeXFormula(latex);
		TeXIcon icon = formula.createTeXIcon(TeXConstants.STYLE_DISPLAY, 20);
		JOptionPane.showMessageDialog(null, "", "LaTeX", JOptionPane.PLAIN_MESSAGE, icon);

		return latex;
	}
	
	public boolean equals(Equation eq) {
		return root.equals(eq.root);
	}
	
	public boolean equals(Expression e) {
		return root.equals(e);
	}
}