package math.structure;

import java.util.HashMap;
import java.util.HashSet;

/**
 * class inherited by all operators, so summations and products
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class Operator extends Expression implements IMath {
	
	/*
	 * Sorters for operators
	 */
	protected static final ExpressionSorter PRODUCT_SORTER = new ExpressionSorter(false);
	protected static final ExpressionSorter SUMMATION_SORTER = new ExpressionSorter(true);

	protected Expression[] children; // all the children to sum
	protected char symbol; // the symbol of the operator

	/*
	 * constructor receiving all the children already as expressions
	 */
	protected Operator(char sym, Expression... expressions) {
		children = expressions;
		symbol = sym;
	}

	/*
	 * constructor receiving all children as strings that still need to be parsed
	 */
	protected Operator(char sym, HashSet<Character> vars, String... strExpressions) {
		Expression[] expressions = new Expression[strExpressions.length];
		for (int i = 0; i < expressions.length; i++)
			expressions[i] = Parser.generateExpression(strExpressions[i], vars);
		children = expressions;
		symbol = sym;
	}

	@Override
	public double evaluate(HashMap<Character, Double> varValues) {
		double result = neutral();
		for (Expression node : children)
			result = operate(result, node.evaluate(varValues));
		return result;
	}

	@Override
	public String toString() {
		if (children.length == 0)
			return "";

		StringBuilder sb = new StringBuilder();
		sb.append('(');
		int i = 0;
		sb.append(children[i]);
		sb.append(' ');
		for (i = 1; i < children.length - 1; i++) {
			sb.append(symbol);
			sb.append(' ');
			sb.append(children[i]);
			sb.append(' ');
		}
		sb.append(symbol);
		sb.append(' ');
		sb.append(children[i]);
		sb.append(')');
		return sb.toString();
	}

	@Override
	public String toLatex() {
		if (children.length == 0)
			return "";

		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < children.length; i++) {
			boolean brackets = needsBrackets(children[i]);
			if (brackets)
				sb.append("\\left(");
			latex(i, sb);
			if (brackets)
				sb.append("\\right)");
			if (i < children.length - 1 && this instanceof Product) // remove later
				sb.append(symbol); // remove later
			sb.append(' ');
		}
		return sb.toString();
	}

	@Override
	public boolean equals(Expression e) {
		if (e instanceof Operator) {
			Operator op = ((Operator) e);
			if (children.length == op.children.length && symbol == op.symbol) {
				for (int i = 0; i < children.length; i++)
					if (!children[i].equals(op.children[i]))
						return false;
				return true;
			}
		}
		return false;
	}

	/**
	 * add the latex code representation of the child at the index
	 * 
	 * @param index   - index of the child
	 * @param builder - where to store latex code representation
	 */
	protected abstract void latex(int index, StringBuilder builder);

	/**
	 * @param a - input 1 to operate on
	 * @param b - input 2 to operate on
	 * @return the specific operation on the inputs
	 */
	protected abstract double operate(double a, double b);

	/**
	 * @return the neutral element of the operation
	 */
	protected abstract double neutral();

	/**
	 * @return true if brackets around an element is needed
	 */
	protected abstract boolean needsBrackets(Expression e);
}
