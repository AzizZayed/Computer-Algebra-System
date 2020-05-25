package math.structure;

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
	public double evaluate(double x) {
		return compute(expr.evaluate(x));
	}

	@Override
	public String toString() {
		if (!needsBrackets())
			return name + expr.toString();
		return name + "(" + expr.toString() + ")";
	}

	@Override
	public String toLatex() {
		if (!needsBrackets())
			return '\\' + name + "{" + expr.toLatex() + "}";
		return '\\' + name + "{\\left(" + expr.toLatex() + "\\right)}";
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
	}
}
