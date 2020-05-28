package math.structure;

import java.util.HashMap;

/**
 * class inherited by all trigonometric functions like cosine, sine, tangent
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class TrigonometricFunction extends Function implements IMath {

	/**
	 * constructor
	 * 
	 * @param expr - expression inside the function (to compute)
	 * @param name - name of the trigonometric function
	 */
	public TrigonometricFunction(String name, Expression expr) {
		super(name, expr);
	}

	@Override
	public double evaluate(HashMap<Character, Double> varValues) {
		return compute(expr.evaluate(varValues));
	}

	@Override
	public String toString() {
		if (!needsBrackets())
			return name + expr.toString();
		return name + "(" + expr.toString() + ")";
	}

	@Override
	public String toLatex() {
		if (needsBrackets())
			return '\\' + name + "{\\left(" + expr.toLatex() + "\\right)}";
		return '\\' + name + "{" + expr.toLatex() + "}";
	}

	@Override
	public boolean equals(Expression e) {
		if (e instanceof TrigonometricFunction) {
			TrigonometricFunction func = (TrigonometricFunction) e;
			if (name.equals(func.name))
				return expr.equals(func.expr);
		}
		return false;
	}

	/**
	 * @return if the input needs brackets
	 */
	protected boolean needsBrackets() {
		return expr instanceof Operator || expr instanceof Power || expr instanceof Fraction || expr instanceof Log;
	}

	/**
	 * @param in - input to the trigonometric function
	 * @return the computed value from the trigonometric function
	 */
	protected abstract double compute(double in);

	/*
	 * cosine function
	 */
	public static class Cos extends TrigonometricFunction implements IMath {
		public Cos(Expression expr) {
			super("cos", expr);
		}

		@Override
		protected double compute(double in) {
			return Math.cos(in);
		}

		@Override
		public Expression differentiate(char var) {
			return Product.create( // -1 * f' * sin(f)
					new Constant(-1d), // -1
					expr.differentiate(var), // f'
					new Sin(expr) // sin(f)
			); // end -1 * f' * sin(f)
		}

		@Override
		public Expression simplify() {
			return new Cos(expr.simplify());
		}
	}

	/*
	 * sine function
	 */
	public static class Sin extends TrigonometricFunction implements IMath {
		public Sin(Expression expr) {
			super("sin", expr);
		}

		@Override
		protected double compute(double in) {
			return Math.sin(in);
		}

		@Override
		public Expression differentiate(char var) {
			return Product.create( // f' * cos(f)
					expr.differentiate(var), // f'
					new Cos(expr) // cos(f)
			); // end f' * cos(f)
		}

		@Override
		public Expression simplify() {
			return new Sin(expr.simplify());
		}
	}

	/*
	 * tangent function
	 */
	public static class Tan extends TrigonometricFunction implements IMath {
		public Tan(Expression expr) {
			super("tan", expr);
		}

		@Override
		protected double compute(double in) {
			return Math.tan(in);
		}

		@Override
		public Expression differentiate(char var) {
//			System.out.println("in tan");

			Expression p = Product.create( // f' * (sec(f))^2
					expr.differentiate(var), // f'
					new Power( // (sec(f))^2
							new Sec(expr), // sec(f)
							new Constant(2d) // 2
					) // end (sec(f))^2
			); // end f' * (sec(f))^2
//			System.out.println(p);
			return p;
		}

		@Override
		public Expression simplify() {
			return new Tan(expr.simplify());
		}
	}

	/*
	 * cosecant function
	 */
	public static class Csc extends TrigonometricFunction implements IMath {
		public Csc(Expression expr) {
			super("csc", expr);
		}

		@Override
		protected double compute(double in) {
			return 1.0d / Math.sin(in);
		}

		@Override
		public Expression differentiate(char var) {
			return Product.create( // -1 * csc(f) * cot(f) * f'
					new Constant(-1d), // -1
					expr.differentiate(var), // f'
					new Csc(expr), // csc(f)
					new Cot(expr) // cot(f)
			); // end csc(f) * cot(f) * f'
		}

		@Override
		public Expression simplify() {
			return new Csc(expr.simplify());
		}
	}

	/*
	 * secant function
	 */
	public static class Sec extends TrigonometricFunction implements IMath {
		public Sec(Expression expr) {
			super("sec", expr);
		}

		@Override
		protected double compute(double in) {
			return 1.0d / Math.cos(in);
		}

		@Override
		public Expression differentiate(char var) {
			return Product.create( // sec(f) * tan(f) * f'
					expr.differentiate(var), // f'
					new Sec(expr), // sec(f)
					new Tan(expr) // tan(f)
			); // end sec(f) * tan(f) * f'
		}

		@Override
		public Expression simplify() {
			return new Sec(expr.simplify());
		}
	}

	/*
	 * cotangent function
	 */
	public static class Cot extends TrigonometricFunction implements IMath {
		public Cot(Expression expr) {
			super("cot", expr);
		}

		@Override
		protected double compute(double in) {
			return 1.0d / Math.tan(in);
		}

		@Override
		public Expression differentiate(char var) {
			return Product.create( // -1 * f' * (csc(f))^2
					new Constant(-1d), // -1
					expr.differentiate(var), // f'
					new Power( // (csc(f))^2
							new Csc(expr), // csc(f)
							new Constant(2d) // 2
					) // end (csc(f))^2
			); // end f' * (csc(f))^2
		}

		@Override
		public Expression simplify() {
			return new Cot(expr.simplify());
		}
	}
}