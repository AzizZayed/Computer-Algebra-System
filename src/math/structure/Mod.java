package math.structure;

import java.util.HashMap;

public class Mod extends FixedInputFunction {

	protected Expression input;

	public Mod(Expression in1, Expression in2) {
		super(ExpressionType.MODULUS, in1);
		input = in2;
	}

	@Override
	public String toString() {
		return type + "(" + expr + "," + input + ")";
	}

	@Override
	public String toLatex() {
		return type + "\\left(" + expr.toLatex() + "," + input.toLatex() + "\\right)";
	}

	@Override
	public double evaluate(HashMap<Character, Double> varValues) {
		return expr.evaluate(varValues) % input.evaluate(varValues);
	}

	@Override
	public boolean equals(Expression e) {
		if (e instanceof Mod) {
			Mod mod = (Mod) e;
			return expr.equals(mod.expr) && input.equals(mod.input);
		}
		return false;
	}

	@Override
	public Expression differentiate(char var) {
		throw new IllegalArgumentException("Cannot differentiate modulus. Compute numerically instead.");
	}

	@Override
	public Expression simplify() {
		return new Mod(expr.simplify(), input.simplify());
	}
}