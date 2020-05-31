package math.structure;

import java.util.Comparator;

/**
 * comparator class to sort expressions
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class ExpressionSorter implements Comparator<Expression> {

	private boolean reverse;

	public ExpressionSorter(boolean reverse) {
		this.reverse = reverse;
	}

	/*
	 * the desired orders we want the functions in
	 */
	private static String[] order = { "constant", "variable", "power", "fraction", "logarithm", "absolutevalue",
			"floor", "ceiling", "sin", "cos", "tan", "csc", "sec", "cot", "arcsin", "arccos", "arctan", "max", "min",
			"product", "sum" };

	@Override
	public int compare(Expression e1, Expression e2) {
		int mult = 1;
		if (reverse)
			mult = -1;

		int index1 = indexOf(e1.getName());
		int index2 = indexOf(e2.getName());
		int diff = mult * (index1 - index2);

		if (diff == 0) {
			if (e1 instanceof Function) {
				Function func1 = (Function) e1;
				Function func2 = (Function) e2;
				return mult * (indexOf(func1.expr.getName()) - indexOf(func2.expr.getName()));
			}
			if (e1 instanceof Fraction) {
				Fraction func1 = (Fraction) e1;
				Fraction func2 = (Fraction) e2;
				diff = mult * (indexOf(func1.numerator.getName()) - indexOf(func2.numerator.getName()));
				if (diff == 0)
					return mult * (indexOf(func1.denominator.getName()) - indexOf(func2.denominator.getName()));
				return diff;
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