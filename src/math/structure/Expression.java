package math.structure;

/**
 * class for an arbitrary mathematical expression
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class Expression implements IMath {

	/**
	 * calculate the value of the mathematical expression
	 * 
	 * @param x - value of x
	 * @return the value of the expression
	 */
	public abstract double evaluate(double x);
	
	/*
	 * class to represent a fraction
	 */
	public static class Fraction extends Expression implements IMath {

		private Expression numerator, denominator;

		public Fraction(Expression num, Expression denom) {
			numerator = num;
			denominator = denom;
		}

		@Override
		public double evaluate(double x) {
			return numerator.evaluate(x) / denominator.evaluate(x);
		}

		@Override
		public String toString() {
			return "(" + numerator.toString() + "/" + denominator.toString() + ")";
		}
		
		@Override
		public String toLatex() {
			return "\\left(\\frac{" + numerator.toLatex() + "}{" + denominator.toLatex() + "}\\right)";
		}
	}

	/*
	 * class to represent any term like x, y, z
	 */
	public static class Variable extends Expression implements IMath {

		private char symbol;

		public Variable(char sym) {
			symbol = sym;
		}

		public Variable() {
			symbol = 'x';
		}

		@Override
		public double evaluate(double x) {
			return x;
		}

		@Override
		public String toString() {
			return Character.toString(symbol);
		}
		
		@Override
		public String toLatex() {
			return toString();
		}
	}

	/*
	 * class to represent any constant/number
	 */
	public static class Constant extends Expression implements IMath {

		public static final Constant PI = new Constant(3.141592653589793d);
		public static final Constant EXP = new Constant(2.718281828459045d);
		public static final Constant GOLDEN_RATIO = new Constant(1.618033988749895d);

		private double value;
		
		/**
		 * @return the value of the constant
		 */
		public double getValue() {
			return value;
		}

		public Constant(double val) {
			value = val;
		}

		@Override
		public double evaluate(double x) {
			return value;
		}

		@Override
		public String toString() {
			if (this == PI || value == PI.value)
				return "\u03C0";
			if (this == EXP || value == EXP.value)
				return "e";
			if (this == GOLDEN_RATIO || value == GOLDEN_RATIO.value)
				return "\u03D5";

			return Double.toString(value);
		}

		@Override
		public String toLatex() {
			return toString();
		}
	}
}
