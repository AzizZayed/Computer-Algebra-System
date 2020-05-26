package math.structure;

import java.util.HashMap;

/**
 * class that represents any elementary function like trigonometric functions,
 * absolute value, floor, ceiling ... etc
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class Function extends Expression implements IMath {

	protected Expression expr;

	public Function(Expression expr) {
		this.expr = expr;
	}

	public static class Min extends Function implements IMath {

		private Expression expr2;

		public Min(Expression e1, Expression e2) {
			super(e1);
			expr2 = e2;
		}

		@Override
		public String toString() {
			return "min(" + expr.toString() + ", " + expr2.toString() + ")";
		}

		@Override
		public String toLatex() {
			return "\\min\\left(" + expr.toLatex() + ", " + expr2.toLatex() + "\\right)";
		}
		
		@Override
		public double evaluate(HashMap<Character, Double> varValues) {
			return Math.min(expr.evaluate(varValues), expr2.evaluate(varValues));
		}

		@Override
		public boolean equals(Expression e) {
			if (e instanceof Min) {
				Min max = (Min) e;
				return expr.equals(max.expr) && expr2.equals(max.expr2);
			}
			return false;
		}
	}

	public static class Max extends Function implements IMath {

		private Expression expr2;

		public Max(Expression e1, Expression e2) {
			super(e1);
			expr2 = e2;
		}

		@Override
		public String toString() {
			return "max(" + expr.toString() + ", " + expr2.toString() + ")";
		}

		@Override
		public String toLatex() {
			return "\\max\\left(" + expr.toLatex() + ", " + expr2.toLatex() + "\\right)";
		}

		@Override
		public double evaluate(HashMap<Character, Double> varValues) {
			return Math.max(expr.evaluate(varValues), expr2.evaluate(varValues));
		}

		@Override
		public boolean equals(Expression e) {
			if (e instanceof Max) {
				Max max = (Max) e;
				return expr.equals(max.expr) && expr2.equals(max.expr2);
			}
			return false;
		}
	}
}