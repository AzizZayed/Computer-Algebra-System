package math.structure;

public class Log extends Function implements IMath {

	private Expression base;

	public Log(Expression base, Expression expr) {
		super(expr);
		this.base = base;
	}

	@Override
	public double evaluate(double x) {
		return Math.log(expr.evaluate(x)) / Math.log(base.evaluate(x));
	}

	@Override
	public String toString() {
		return "log_" + base.toString() + " " + expr.toString();
	}
	
	public static class Ln extends Log implements IMath {
		public Ln(Expression expr) {
			super(Constant.EXP, expr);
		}
		
		@Override
		public double evaluate(double x) {
			return Math.log(expr.evaluate(x));
		}
		
		@Override
		public String toString() {
			return "ln" + expr.toString();
		}
	}
}
