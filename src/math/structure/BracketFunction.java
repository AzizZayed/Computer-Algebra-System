package math.structure;

import java.util.HashMap;

/**
 * functioned defined with brackets like the floor function and the ceiling
 * function. This parent class is used for all functions that don't need to be
 * redefined every time, so we or mathematicians define a bracket notation to
 * refer to them
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class BracketFunction extends Function implements IMath {

	private char open, closed; // open and close brackets for

	/**
	 * constructor for different open and close brackets
	 */
	public BracketFunction(Expression expr, char open, char closed) {
		super(expr);
		this.open = open;
		this.closed = closed;
	}

	/**
	 * constructor for similar open and close brackets
	 */
	public BracketFunction(Expression expr, char bracket) {
		super(expr);
		this.open = this.closed = bracket;
	}

	@Override
	public double evaluate(HashMap<Character, Double> varValues) {
		return compute(expr.evaluate(varValues));
	}

	@Override
	public String toString() {
		return open + expr.toString() + closed;
	}
	
	@Override
	public String toLatex() {
		return open + expr.toLatex() + closed;
	}

	/**
	 * calculate the value of the function
	 * 
	 * @param in - the input to the function
	 * @return the value returned by the mathematical function
	 */
	protected abstract double compute(double in);

	/**
	 * the floor function
	 */
	public static class Floor extends BracketFunction implements IMath {
		public Floor(Expression expr) {
			super(expr, '\u230A', '\u230B');
		}

		@Override
		protected double compute(double in) {
			return Math.floor(in);
		}
	}

	/**
	 * the ceiling function
	 */
	public static class Ceiling extends BracketFunction implements IMath {
		public Ceiling(Expression expr) {
			super(expr, '\u2308', '\u2309');
		}

		@Override
		protected double compute(double in) {
			return Math.ceil(in);
		}
	}

	/**
	 * the absolute value function
	 */
	public static class Abs extends BracketFunction implements IMath {
		public Abs(Expression expr) {
			super(expr, '|');
		}

		@Override
		protected double compute(double in) {
			return Math.abs(in);
		}
	}
}
