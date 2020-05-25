package math.structure;

/**
 * class inherited by all operators, so summations and products
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class Operator extends Expression implements IMath {

	protected Expression[] children; // all the children to sum
	protected char symbol; // the symbol of the operator

	/**
	 * constructor receiving all the expressions to sum up
	 * 
	 * @param expressions
	 */
	protected Operator(char sym, Expression... expressions) {
		children = expressions;
		symbol = sym;
	}

	protected Operator(char sym, String... strExpressions) {
//		System.out.println("in here " + Arrays.toString(strExpressions));
		Expression[] expressions = new Expression[strExpressions.length];
		for (int i = 0; i < expressions.length; i++)
			expressions[i] = Parser.parseExpression(strExpressions[i]);
		children = expressions;
		symbol = sym;
	}

	@Override
	public double evaluate(double x) {
		double result = neutral();
		for (Expression node : children) {
			if (node == null)
				continue;

//			System.out.println("Op: " + node.toString());
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

	@Override
	public String toLatex() {
		if (children.length == 0)
			return "";

		StringBuilder sb = new StringBuilder();
		sb.append("\\left(");
		int i = 0;
		for (i = 0; i < children.length - 1; i++) {
			sb.append(children[i].toLatex());
			sb.append(' ');
			sb.append(symbol);
			sb.append(' ');
		}
		sb.append(children[i].toLatex());
		sb.append("\\right)");
		return sb.toString();
	}

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

	/*
	 * a finite product
	 */
	public static class Product extends Operator implements IMath {
		public Product(Expression... expressions) {
			super('*', expressions);
		}

		public Product(String... strExpression) {
			super('*', strExpression);
		}
		
		public static Expression create(String... strExpression) {
			if (strExpression.length == 1)
				return Parser.parseExpression(strExpression[0]);
			return new Product(strExpression);
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

	/*
	 * a finite sum
	 */
	public static class Sum extends Operator implements IMath {
		public Sum(Expression... expressions) {
			super('+', expressions);
		}

		public Sum(String... strExpression) {
			super('+', strExpression);
		}
		
		public static Expression create(String... strExpression) {
			if (strExpression.length == 1)
				return Parser.parseExpression(strExpression[0]);
			return new Sum(strExpression);
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
