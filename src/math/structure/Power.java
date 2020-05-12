package math.structure;

public class Power extends Function implements IMath {

	protected Expression power;

	public Power(Expression base, Expression power) {
		super(base);
		this.power = power;
	}

	@Override
	public double evaluate(double x) {
		return Math.pow(expr.evaluate(x), power.evaluate(x));
	}

	public String toString() {
		return expr.toString() + "^" + power.toString();
	}

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
