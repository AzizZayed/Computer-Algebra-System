package math.structure;

public abstract class InverseTrigonometricFunction extends TrigonometricFunction implements IMath {

	public InverseTrigonometricFunction(Expression expr, String name) {
		super(expr, name);
	}

	@Override
	public String toLatex() {
		if (!needsBrackets())
			return name.substring(3) + "^{-1}" + expr.toLatex();
		return name.substring(3) + "^{-1}\\left(" + expr.toLatex() + "\\right)";
	}

	/*
	 * arccosine function
	 */
	public static class ArcCos extends InverseTrigonometricFunction implements IMath {
		public ArcCos(Expression expr) {
			super(expr, "arccos");
		}

		@Override
		protected double compute(double in) {
			return Math.acos(in);
		}
	}

	/*
	 * arcsine function
	 */
	public static class ArcSin extends InverseTrigonometricFunction implements IMath {
		public ArcSin(Expression expr) {
			super(expr, "arcsin");
		}

		@Override
		protected double compute(double in) {
			return Math.asin(in);
		}
	}

	/*
	 * arctangent function
	 */
	public static class ArcTan extends InverseTrigonometricFunction implements IMath {
		public ArcTan(Expression expr) {
			super(expr, "arctan");
		}

		@Override
		protected double compute(double in) {
			return Math.atan(in);
		}
	}
}
