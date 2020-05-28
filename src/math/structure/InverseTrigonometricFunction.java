package math.structure;

/**
 * class for the inverse trigonometric functions like arctan, arccos, arcsin
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class InverseTrigonometricFunction extends TrigonometricFunction implements IMath {

	public InverseTrigonometricFunction(String name, Expression expr) {
		super(name, expr);
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
			super("arccos", expr);
		}

		@Override
		protected double compute(double in) {
			return Math.acos(in);
		}

		@Override
		public Expression differentiate(char var) {
			return Product.create( // -1 * (1-f^2)^(-1/2) * f'
					new Constant(-1d), expr.differentiate(var), // -f'
					new Power( // (1-f^2)^(-1/2)
							Sum.create( // 1-f^2
									new Constant(1d), // 1
									Product.create( // -f^2
											new Constant(-1d), // -1
											new Power(expr, new Constant(2d)) // f^2
									) // end product -f^2
							), // end sum of 1-f^2
							new Constant(-0.5d) // -1/2, the power
					) // end power: (1-f^2)^(-1/2)
			); // end Product -1 * (1-f^2)^(-1/2) * f'
		}
	}

	/*
	 * arcsine function
	 */
	public static class ArcSin extends InverseTrigonometricFunction implements IMath {
		public ArcSin(Expression expr) {
			super("arcsin", expr);
		}

		@Override
		protected double compute(double in) {
			return Math.asin(in);
		}

		@Override
		public Expression differentiate(char var) {
			return Product.create( // (1-f^2)^(-1/2) * f'
					expr.differentiate(var), // f'
					new Power( // (1-f^2)^(-1/2)
							Sum.create( // 1-f^2
									new Constant(1d), // 1
									Product.create( // -f^2
											new Constant(-1d), // -1
											new Power(expr, new Constant(2d)) // f^2
									) // end product -f^2
							), // end sum of 1-f^2
							new Constant(-0.5d) // -1/2, the power
					) // end power: (1-f^2)^(-1/2)
			); // end Product (1-f^2)^(-1/2) * f'
		}
	}

	/*
	 * arctangent function
	 */
	public static class ArcTan extends InverseTrigonometricFunction implements IMath {
		public ArcTan(Expression expr) {
			super("arctan", expr);
		}

		@Override
		protected double compute(double in) {
			return Math.atan(in);
		}

		@Override
		public Expression differentiate(char var) {
			return Product.create( // f' * (1 + f^2)^(-1)
					expr.differentiate(var), // f'
					new Power( // (1 + f^2)^(-1)
							Sum.create( // 1 + f^2
									new Constant(1d), // 1
									new Power( // f^2
											expr, // f
											new Constant(2d) // 2: squared
									) // end f^2
							), // end 1 + f^2
							new Constant(-1d) // -1
					) // end (1 + f^2)^(-1)
			); // end of f' * (1 + f^2)^(-1)
		}
	}
}