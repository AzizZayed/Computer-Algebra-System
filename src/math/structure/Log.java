package math.structure;

import java.util.HashMap;

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
	public double evaluate(HashMap<Character, Double> varValues) {
		return Math.log(expr.evaluate(varValues)) / Math.log(base.evaluate(varValues));
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
	
	@Override
	public boolean equals(Expression e) {
		if (e instanceof Log) {
			Log log = (Log) e;
			return expr.equals(log.expr) && base.equals(log.base);
		}
		return false;
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