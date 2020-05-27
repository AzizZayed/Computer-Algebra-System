package math.structure;

import java.util.HashSet;

/**
 * a class representing a finite sum
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Sum extends Operator implements IMath {
	private Sum(Expression... expressions) {
		super('+', expressions);
	}

	private Sum(HashSet<Character> vars, String... strExpression) {
		super('+', vars, strExpression);
	}

	/**
	 * function to create an expression node with the given children as strings,
	 * they still need to be parsed. The point of this function is to perform early
	 * refactoring to make life easier later on. It does not have to return a sum
	 * node if the refactored expression does not require a sum node
	 * 
	 * @param vars          - the set of all variables
	 * @param strExpression - the array of strings to be parsed into expressions
	 * @return the refactored expression
	 */
	public static Expression create(HashSet<Character> vars, String... strExpression) {
		if (strExpression.length == 0)
			return null;
		else if (strExpression.length == 1)
			return Parser.generateExpression(strExpression[0], vars);
		return new Sum(vars, strExpression);
	}

	/**
	 * function to create expression node from the given expressions. The point of
	 * this function is to perform early refactoring and simplification to make life
	 * easier later on. It does not have to return a sum node if the simplified
	 * expression does not require a sum node
	 * 
	 * @param expressions - array of expressions
	 * @return simplified and refactored expression
	 */
	public static Expression create(Expression... expressions) {
		if (expressions.length == 0)
			return null;
		if (expressions.length == 1)
			return expressions[0];
		return new Sum(expressions);
	}

	@Override
	protected double operate(double a, double b) {
		return a + b;
	}

	@Override
	protected double neutral() {
		return 0;
	}

	@Override
	protected void latex(int index, StringBuilder builder) {
		boolean putSymbol = true;

		// don't put + sign if next element is negated, like -sinx : -1*sinx in memory
		if (children[index] instanceof Product) {
			Product product = (Product) children[index];
			if (product.children[0] instanceof Constant) {
				Constant constant = (Constant) product.children[0];
				putSymbol = !(Math.signum(constant.getValue()) < 0);
			}
		}

		if (putSymbol && index != 0)
			builder.append(symbol);
		builder.append(children[index].toLatex());
	}

	@Override
	protected boolean needsBrackets(Expression e) {
		return false;
	}

	@Override
	public Expression differentiate(char var) {
		Expression[] derivatives = new Expression[children.length];
		for (int i = 0; i < children.length; i++)
			derivatives[i] = children[i].differentiate(var);
		return Sum.create(derivatives);
	}
}