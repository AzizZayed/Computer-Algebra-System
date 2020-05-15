package math.structure;

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
	public double evaluate(double x) {
		return Math.pow(expr.evaluate(x), power.evaluate(x));
	}

	@Override
	public String toString() {
		return expr.toString() + "\u005E" + power.toString();
	}

	/*
	 * natural exponential with e, so e^x, where x is any expression
	 */
	public static class Exp extends Power implements IMath {
		public Exp(Expression power) {
			super(Constant.EXP, power);
		}

		@Override
		public double evaluate(double x) {
			return Math.exp(power.evaluate(x));
		}
	}
}
