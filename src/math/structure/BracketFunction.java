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
public abstract class BracketFunction extends FixedInputFunction implements IMath {

	private char open, closed; // open and close brackets for

	/**
	 * constructor for different open and close brackets
	 */
	public BracketFunction(String name, Expression expr, char open, char closed) {
		super(name, expr);
		this.open = open;
		this.closed = closed;
	}

	/**
	 * constructor for similar open and close brackets
	 */
	public BracketFunction(String name, Expression expr, char bracket) {
		this(name, expr, bracket, bracket);
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

	@Override
	public boolean equals(Expression e) {
		if (e instanceof BracketFunction) {
			BracketFunction func = (BracketFunction) e;
			if (open == func.open && closed == func.closed)
				return expr.equals(func.expr);
		}
		return false;
	}

	@Override
	public Expression differentiate(char var) {
		return new Constant(0d);
	}

	/**
	 * Common simplification between all bracket functions: when the input is a
	 * constant, the operation can be computed and returned without needing the
	 * bracket function
	 * 
	 * @return a constant node with the result, null if the operation is impossible
	 */
	protected Constant evaluate() {
		if (expr instanceof Constant) {
			Constant c = (Constant) expr;
			return new Constant(compute(c.getValue()));
		}
		return null;
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
			super("floor", expr, '\u230A', '\u230B');
		}

		@Override
		protected double compute(double in) {
			return Math.floor(in);
		}

		@Override
		public Expression simplify() {
			Constant eval = evaluate();
			return eval == null ? new Floor(expr.simplify()) : eval;
		}
	}

	/**
	 * the ceiling function
	 */
	public static class Ceiling extends BracketFunction implements IMath {
		public Ceiling(Expression expr) {
			super("ceiling", expr, '\u2308', '\u2309');
		}

		@Override
		protected double compute(double in) {
			return Math.ceil(in);
		}

		@Override
		public Expression simplify() {
			Constant eval = evaluate();
			return eval == null ? new Ceiling(expr.simplify()) : eval;
		}
	}

	/**
	 * the absolute value function
	 */
	public static class Abs extends BracketFunction implements IMath {
		public Abs(Expression expr) {
			super("absolutevalue", expr, '|');
		}

		@Override
		protected double compute(double in) {
			return Math.abs(in);
		}

		@Override
		public Expression differentiate(char var) {
			return Product.create( // f/abs(f) * f'
					new Fraction(expr, this), // f/abs(f)
					expr.differentiate(var) // f'
			); // end f/abs(f) * f'
		}

		@Override
		public Expression simplify() {
			Constant eval = evaluate();
			return eval == null ? new Abs(expr.simplify()) : eval;
		}
	}
}