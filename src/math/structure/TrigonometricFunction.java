package math.structure;

/**
 * class inherited by all trigonometric functions like cosine, sine, tangent
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class TrigonometricFunction extends Function implements IMath {

	private String name; // the name of the function

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
		return name + expr.toString();
	}
	
	@Override
	public String toLatex() {
		return '\\' + name + expr.toString();
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
}
