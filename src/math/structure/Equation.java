package math.structure;

import java.util.HashMap;
import java.util.HashSet;

/**
 * This is a wrapper class for an expression. It contains all the methods we
 * would need to access outside the data structure package
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Equation implements IMath {

	private Expression root;

	public Equation(Expression root) {
		this.root = root;
	}

	public Equation(String exp, HashSet<Character> variables) {
		exp = Parser.clean(exp);
		root = Parser.parseExpression(exp, variables);
	}

	/**
	 * get the value of the expression with the given values for the variables
	 * 
	 * @param varValues - values of each variable
	 * @return the value of the expression at the given values
	 */
	public double valueAt(HashMap<Character, Double> varValues) {
		return root.evaluate(varValues);
	}

	@Override
	public String toLatex() {
		return root.toLatex();
	}

	/**
	 * compute a full simplification of this expression
	 * 
	 * @return a fully simplified version of the root expression
	 */
	public Equation simplified() {
		Expression simplified = root;
		Expression previous;

		do {
			previous = simplified;
			simplified = simplified.simplify();
		} while (!simplified.equals(previous));

		return new Equation(simplified.simplify());
	}

	/**
	 * compute a fully simplified version of the derivative of this equation
	 * 
	 * @param var - variable we wish to differentiate with respect to
	 * @return a fully simplified version of the derivative of this equation
	 */
	public Equation derivative(char var) {
		Equation derivative = new Equation(root.differentiate(var));
		return derivative.simplified();
	}
}