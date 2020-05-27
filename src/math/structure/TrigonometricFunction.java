package math.structure;

import java.util.HashMap;

/**
 * class inherited by all trigonometric functions like cosine, sine, tangent
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class TrigonometricFunction extends Function implements IMath {

	protected String name; // the name of the function

	/**
	 * constructor
	 * 
	 * @param expr - expression inside the function (to compute)
	 * @param name - name of the trigonometric function
	 */
	public TrigonometricFunction(Expression expr, String name) {
		super(expr);
		this.name = name;
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
//		if (!needsBrackets())
//			return '\\' + name + "{" + expr.toLatex() + "}";
		return '\\' + name + "{\\left(" + expr.toLatex() + "\\right)}";
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

	protected boolean needsBrackets() {
		return !(expr instanceof Variable || expr instanceof Constant || expr instanceof BracketFunction
				|| expr instanceof TrigonometricFunction || expr instanceof Min || expr instanceof Max);
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
			super(expr, "cos");
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
	}

	/*
	 * sine function
	 */
	public static class Sin extends TrigonometricFunction implements IMath {
		public Sin(Expression expr) {
			super(expr, "sin");
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
	}

	/*
	 * tangent function
	 */
	public static class Tan extends TrigonometricFunction implements IMath {
		public Tan(Expression expr) {
			super(expr, "tan");
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
	}

	/*
	 * cosecant function
	 */
	public static class Csc extends TrigonometricFunction implements IMath {
		public Csc(Expression expr) {
			super(expr, "csc");
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
	}

	/*
	 * secant function
	 */
	public static class Sec extends TrigonometricFunction implements IMath {
		public Sec(Expression expr) {
			super(expr, "sec");
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
	}

	/*
	 * cotangent function
	 */
	public static class Cot extends TrigonometricFunction implements IMath {
		public Cot(Expression expr) {
			super(expr, "cot");
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
	}
}
