package math.structure;

public abstract class Operator extends Expression implements IMath {

	protected Expression[] children;
	protected char symbol;

	public Operator(Expression... expressions) {
		children = expressions;
	}

	@Override
	public double evaluate(double x) {
		double result = neutral();
		for (Expression node : children) {
			result = operate(result, node.evaluate(x));
		}
		return result;
	}

	@Override
	public String toString() {
		if (children.length == 0)
			return "";

		StringBuilder sb = new StringBuilder();
		sb.append('(');
		int i = 0;
		for (i = 0; i < children.length - 1; i++) {
			sb.append(children[i]);
			sb.append(' ');
			sb.append(symbol);
			sb.append(' ');
		}
		sb.append(children[i]);
		sb.append(')');
		return sb.toString();
	}

	/**
	 * @param a - input 1 to operate on
	 * @param b - input 2 to operate on
	 * @return the operator operation on the inputs
	 */
	protected abstract double operate(double a, double b);

	/**
	 * @return the neutral element of the operation
	 */
	protected abstract double neutral();

	public static class Product extends Operator implements IMath {

		public Product(Expression... expressions) {
			super(expressions);
			symbol = '*';
		}

		@Override
		protected double operate(double a, double b) {
			return a * b;
		}

		@Override
		protected double neutral() {
			return 1;
		}

	}

	public static class Sum extends Operator implements IMath {

		public Sum(Expression... expressions) {
			super(expressions);
			symbol = '+';
		}

		@Override
		protected double operate(double a, double b) {
			return a + b;
		}

		@Override
		protected double neutral() {
			return 0;
		}
	}
}
