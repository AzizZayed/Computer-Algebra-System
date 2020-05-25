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
		this.base = new Constant(10.0d);
	}

	@Override
	public double evaluate(double x) {
		return Math.log(expr.evaluate(x)) / Math.log(base.evaluate(x));
	}

	@Override
	public String toString() {
		if (needsBrackets())
			return "log_" + base.toString() + "_(" + expr.toString() + ")";
		return "log_" + base.toString() + "_" + expr.toString();
	}

	@Override
	public String toLatex() {
		if (needsBrackets())
			return "log_{" + base.toLatex() + "}{\\left(" + expr.toLatex() + "\\right)}";
		return "log_{" + base.toLatex() + "}{" + expr.toLatex() + "}";
	}

	protected boolean needsBrackets() {
		return !(expr instanceof Variable || expr instanceof Constant || expr instanceof BracketFunction
				|| expr instanceof TrigonometricFunction || expr instanceof Min || expr instanceof Max);
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
			if (needsBrackets())
				return "ln(" + expr.toString() + ")";
			return "ln" + expr.toString();
		}

		@Override
		public String toLatex() {
			if (needsBrackets())
				return "ln\\left(" + expr.toLatex() + "\\right)";
			return "ln" + expr.toLatex();
		}
	}
}