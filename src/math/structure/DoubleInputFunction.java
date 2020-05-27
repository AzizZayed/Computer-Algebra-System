package math.structure;

import java.util.HashMap;

/**
 * represents any function that takes 2 inputs
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class DoubleInputFunction extends Function implements IMath {

	protected Expression expr2;
	private String name;

	/*
	 * constructor with 2 expression inputs and a name
	 */
	public DoubleInputFunction(Expression e1, Expression e2, String name) {
		super(e1);
		expr2 = e2;
		this.name = name;
	}

	@Override
	public String toString() {
		return name + "(" + expr.toString() + ", " + expr2.toString() + ")";
	}

	@Override
	public String toLatex() {
		return "\\" + name + "\\left(" + expr.toLatex() + ", " + expr2.toLatex() + "\\right)";
	}

	@Override
	public double evaluate(HashMap<Character, Double> varValues) {
		return compute(expr.evaluate(varValues), expr2.evaluate(varValues));
	}

	@Override
	public boolean equals(Expression e) {
		if (e instanceof DoubleInputFunction) {
			DoubleInputFunction func = (DoubleInputFunction) e;
			if (name.equals(func.name))
				return expr.equals(func.expr) && expr2.equals(func.expr2);
		}
		return false;
	}

	@Override
	public Expression differentiate(char var) {
		return null;
	}

	/**
	 * @param in1 - first input to the double input function
	 * @param in2 - second input to the double input function
	 * @return the computed value from the double input function
	 */
	public abstract double compute(double in1, double in2);

	public static class Min extends DoubleInputFunction implements IMath {
		public Min(Expression e1, Expression e2) {
			super(e1, e2, "min");
		}

		@Override
		public double compute(double in1, double in2) {
			return Math.min(in1, in2);
		}
	}

	public static class Max extends DoubleInputFunction implements IMath {
		public Max(Expression e1, Expression e2) {
			super(e1, e2, "max");
		}

		@Override
		public double compute(double in1, double in2) {
			return Math.max(in1, in2);
		}
	}
}