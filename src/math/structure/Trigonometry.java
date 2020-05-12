package math.structure;

public abstract class Trigonometry extends Function implements IMath {

	public Trigonometry(Expression expr) {
		super(expr);
	}
	
	@Override
	public double evaluate(double x) {
		return compute(expr.evaluate(x));
	}
	
	@Override
	public String toString() {
		return name() + expr.toString();
	}
	
	protected abstract double compute(double in);
	protected abstract String name();

	public static class Cos extends Trigonometry implements IMath {
		public Cos(Expression expr) {
			super(expr);
		}

		@Override
		protected double compute(double in) {
			return Math.cos(in);
		}

		@Override
		protected String name() {
			return "cos";
		}
	}

	public static class Sin extends Trigonometry implements IMath {
		public Sin(Expression expr) {
			super(expr);
		}

		@Override
		protected double compute(double in) {
			return Math.sin(in);
		}

		@Override
		protected String name() {
			return "sin";
		}
	}

	public static class Tan extends Trigonometry implements IMath {
		public Tan(Expression expr) {
			super(expr);
		}

		@Override
		protected double compute(double in) {
			return Math.tan(in);
		}

		@Override
		protected String name() {
			return "tan";
		}
	}
}
