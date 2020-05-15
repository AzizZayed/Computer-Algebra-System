package math.structure;

/**
 * logarithmic functions
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Log extends Function implements IMath {

	private Expression base; // the expression for the base of the logarithm

	/*
	 * constructor with base expression if it's custom, so like log base 5
	 */
	public Log(Expression base, Expression expr) {
		super(expr);
		this.base = base;
	}

	/*
	 * constructor with base 10
	 */
	public Log(Expression expr) {
		super(expr);
		this.base = new Constant(10);
	}

	@Override
	public double evaluate(double x) {
		return Math.log(expr.evaluate(x)) / Math.log(base.evaluate(x));
	}

	@Override
	public String toString() {
		return "log_" + base.toString() + " " + expr.toString();
	}

	/*
	 * natural logarithm
	 */
	public static class Ln extends Log implements IMath {
		public Ln(Expression expr) {
			super(Constant.EXP, expr);
		}

		@Override
		public String toString() {
			return "ln" + expr.toString();
		}
	}
}