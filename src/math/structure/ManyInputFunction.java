package math.structure;

import java.util.HashMap;

import org.apache.commons.lang3.math.NumberUtils;

/**
 * a class that parents any function that can take an arbitrary number of inputs
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class ManyInputFunction extends Expression implements IMath {

	private Expression[] children; // input expressions

	public ManyInputFunction(String name, Expression[] expressions) {
		super(name);
		children = expressions;
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(name);
		sb.append("(");
		for (int i = 0; i < children.length - 1; i++) {
			sb.append(children[i]);
			sb.append(", ");
		}
		sb.append(children[children.length - 1]);
		sb.append(")");
		return sb.toString();
	}

	@Override
	public String toLatex() {
		StringBuilder sb = new StringBuilder();
		sb.append("\\");
		sb.append(name);
		sb.append("\\left(");
		for (int i = 0; i < children.length - 1; i++) {
			sb.append(children[i].toLatex());
			sb.append(", ");
		}
		sb.append(children[children.length - 1].toLatex());
		sb.append("\\right)");
		return sb.toString();
	}

	@Override
	public double evaluate(HashMap<Character, Double> varValues) {
		double[] values = new double[children.length];
		for (int i = 0; i < values.length; i++)
			values[i] = children[i].evaluate(varValues);
		return compute(values);
	}

	@Override
	public boolean equals(Expression e) {
		if (e instanceof ManyInputFunction) {
			ManyInputFunction func = (ManyInputFunction) e;
			if (name.equals(func.name)) {
				for (int i = 0; i < children.length; i++)
					if (!children[i].equals(func.children[i]))
						return false;
				return true;
			}
		}
		return false;
	}

	@Override
	public Expression differentiate(char var) {
		return null; // throw exception here
	}

	protected abstract double compute(double[] in);

	/**
	 * a min function with arbitrary number of inputs
	 * 
	 * @author Abd-El-Aziz Zayed
	 *
	 */
	public static class Min extends ManyInputFunction implements IMath {
		public Min(Expression... expressions) {
			super("min", expressions);
		}

		@Override
		protected double compute(double[] in) {
			return NumberUtils.min(in);
		}
	}

	/**
	 * a max function with arbitrary number of inputs
	 * 
	 * @author Abd-El-Aziz Zayed
	 *
	 */
	public static class Max extends ManyInputFunction implements IMath {
		public Max(Expression... expressions) {
			super("max", expressions);
		}

		@Override
		protected double compute(double[] in) {
			return NumberUtils.max(in);
		}
	}
}