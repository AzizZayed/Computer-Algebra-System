package math.structure;

import java.util.HashMap;

/**
 * class representing exponentials with any base and power expression
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Power extends Function implements IMath {

	protected Expression power; // the expression in the exponent

	/**
	 * constructor, example: a^b : a is the base and b is the power/exponent
	 * 
	 * @param base  - expression at the base
	 * @param power - expression in the exponent
	 */
	public Power(Expression base, Expression power) {
		super(base);
		this.power = power;
	}

	@Override
	public double evaluate(HashMap<Character, Double> varValues) {
		return Math.pow(expr.evaluate(varValues), power.evaluate(varValues));
	}

	@Override
	public String toString() {
		if (power instanceof Constant) {
			Constant constant = (Constant) power;
			if (constant.getValue() == 0.5d)
				return "sqrt" + expr.toString() + "";
		}

		if (!needsBrackets())
			return expr.toString() + "^" + power.toString();
		else
			return "(" + expr.toString() + ")^" + power.toString();
	}

	@Override
	public String toLatex() {
		if (power instanceof Constant) {
			Constant constant = (Constant) power;
			if (constant.getValue() == 0.5d)
				return "\\sqrt{" + expr.toLatex() + "}";
		}

		if (!needsBrackets())
			return expr.toLatex() + "^{" + power.toLatex() + "}";
		else
			return "\\left(" + expr.toLatex() + "\\right)^{" + power.toLatex() + "}";
	}

	@Override
	public boolean equals(Expression e) {
		if (e instanceof Power) {
			Power pow = (Power) e;
			return expr.equals(pow.expr) && power.equals(pow.power);
		}
		return false;
	}

	private boolean needsBrackets() {
		return !(expr instanceof Variable || expr instanceof Constant || expr instanceof BracketFunction);
	}

	/*
	 * natural exponential with e, so e^x, where x is any expression
	 */
	public static class Exp extends Power implements IMath {
		public Exp(Expression power) {
			super(Constant.EXP, power);
		}

//		@Override
//		public double evaluate(double x) {
//			return Math.exp(power.evaluate(x));
//		}
	}
}