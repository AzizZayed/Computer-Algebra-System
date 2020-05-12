package math.structure;

public abstract class Function extends Expression implements IMath {

	Expression expr;

	public Function(Expression expr) {
		this.expr = expr;
	}

	public static class Floor extends Function implements IMath {
		public Floor(Expression expr) {
			super(expr);
		}

		@Override
		public double evaluate(double x) {
			return Math.floor(expr.evaluate(x));
		}

		@Override
		public String toString() {
			return "\u230A" + expr.toString() + "\u230B";
		}
	}

	public static class Ceil extends Function implements IMath {
		public Ceil(Expression expr) {
			super(expr);
		}

		@Override
		public double evaluate(double x) {
			return Math.ceil(expr.evaluate(x));
		}

		@Override
		public String toString() {
			return "\u2308" + expr.toString() + "\u2309";
		}
	}
}