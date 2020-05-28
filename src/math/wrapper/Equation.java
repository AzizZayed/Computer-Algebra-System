package math.wrapper;

import java.util.HashMap;
import java.util.HashSet;

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
	public Equation(Expression exp) {
		root = exp;
	}

	/*
	 * Constructor with string expression
	 */
	public Equation(String exp) {
		expression = Parser.clean(exp);
		try {
			root = Parser.parseExpression(expression, variables);
		} catch (Exception e) {
			System.out.println("ERROR: " + e);
		}
	}

	/*
	 * constructor with default expression
	 */
	public Equation() {
		root = new Fraction(
				Sum.create(new Exp(new Power(new Variable(), new Constant(1d / 2d))),
						Product.create(new Constant(2), new Variable()), new Fraction(new Constant(1), new Variable())),
				Product.create(new Power(new Variable(), new Constant(1d / 2d)),
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

	/**
	 * get the value of the expression with the given value for the all the
	 * variables
	 * 
	 * @param value - value for every variable
	 * @return the value of the expression at the given value
	 */
	public double valueAt(double value) {
		if (root == null)
			throw new NullPointerException("The expression is empty.");
		
		HashMap<Character, Double> values = new HashMap<>();
		variables.forEach(var -> values.put(var, value));
		
		return root.evaluate(values);
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
		return root.toLatex();
	}

	/**
	 * checks if this equation is equal to the given equation
	 * 
	 * @param eq - given equation to check equality
	 * @return true if the equations are equal, false otherwise
	 */
	public boolean equals(Equation eq) {
		return root.equals(eq.root);
	}

	/**
	 * checks if this equation is equal to the given expression
	 * 
	 * @param e - given expression to check equality
	 * @return true if the equations are equal, false otherwise
	 */
	public boolean equals(Expression e) {
		return root.equals(e);
	}

	/**
	 * compute the derivative of this equation with respect to the give variable
	 * 
	 * @param var - variable to differentiate with respect to
	 * @return the equation of the derivative
	 */
	public Equation derivative(char var) {
		return new Equation(root.differentiate(var));
	}
}