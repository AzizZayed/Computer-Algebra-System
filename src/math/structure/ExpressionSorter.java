package math.structure;

import java.util.Comparator;

/**
 * comparator class to sort expressions
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class ExpressionSorter implements Comparator<Expression> {

	/*
	 * the desired orders we want the functions in
	 */
	private static String[] order = { "constant", "variable", "power", "fraction", "logarithm", "absolutevalue",
			"floor", "ceiling", "sin", "cos", "tan", "csc", "sec", "cot", "arcsin", "arccos", "arctan", "max", "min",
			"product", "summation" };

	@Override
	public int compare(Expression e1, Expression e2) {
		int index1 = indexOf(e1.getName());
		int index2 = indexOf(e2.getName());
		int diff = index1 - index2;

		if (diff == 0) {
			if (e1 instanceof FixedInputFunction) {
				FixedInputFunction func1 = (FixedInputFunction) e1;
				FixedInputFunction func2 = (FixedInputFunction) e2;
				return indexOf(func1.expr.getName()) - indexOf(func2.expr.getName());
			}
			if (e1 instanceof Fraction) {
				Fraction func1 = (Fraction) e1;
				Fraction func2 = (Fraction) e2;
				diff = indexOf(func1.numerator.getName()) - indexOf(func2.numerator.getName());
				if (diff == 0)
					return indexOf(func1.denominator.getName()) - indexOf(func2.denominator.getName());
				return diff;
			}
			if (e1 instanceof Variable) {
				Variable var1 = (Variable) e1;
				Variable var2 = (Variable) e2;
				return var1.getSymbol() - var2.getSymbol();
			}
		}

		return diff;
	}

	/**
	 * @param str - expression type
	 * @return index of the expression type in the order arrays
	 */
	private int indexOf(String str) {
		for (int i = 0; i < order.length; i++)
			if (order[i].equals(str))
				return i;
		return -1;
	}
}