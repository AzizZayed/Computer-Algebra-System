package math.structure;

import java.util.HashMap;

import math.structure.Log.Ln;

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

	@Override
	public Expression differentiate(char var) {
		boolean baseIsNumber = expr instanceof Constant;
		boolean powerIsNumber = power instanceof Constant;

		if (baseIsNumber && powerIsNumber) // case b^k, where b and k are both numbers (constants)
			return new Constant(0d);

		if (!baseIsNumber && powerIsNumber) // case [ f(x) ]^k, where k is a constant
			return Product.create( // k*f^(k-1)*f'
					power, // k
					expr.differentiate(var), // f'
					new Power( // f^(k - 1)
							expr, // f
							new Constant(((Constant) power).getValue() - 1d) // end f^(k - 1)
					) // end f^(k - 1)
			); // end k*f^(k-1)*f'

		if (baseIsNumber && !powerIsNumber) // case k^[ f(x) ], where k is a constant
			return Product.create( // a^f * lna + f'
					this, // a^f
					power.differentiate(var), // f'
					new Ln(expr) // lna
			); // end a^f * lna + f'

		// otherwise: case [ f(x) ]^[ g(x) ], here we use the generalized power rule
		return Product.create( // [f(x)]^[g(x)] * ( g'*lnf + g*f'*(f)^(-1) )
				this, // [f(x)]^[g(x)]
				Sum.create( // g'*lnf + g*f'*(f)^(-1)
						Product.create( // g'*lnf
								power.differentiate(var), // g'
								new Ln(expr) // lnf
						), // end g'*lnf
						Product.create( // g*f'*(f)^(-1)
								power, // g
								expr.differentiate(var), // f'
								new Power( // (f)^(-1)
										expr, // f
										new Constant(-1d) // -1
								) // end (f)^(-1)
						) // end g*f'*(f)^(-1)
				) // end g'*lnf + g*f'*(f)^(-1)
		); // end [f(x)]^[g(x)] * ( g'*lnf + g*f'*(f)^(-1) )
	}
	
	@Override
	public String getName() {
		return "power";
	}

	/*
	 * natural exponential with e, so e^x, where x is any expression
	 */
	public static class Exp extends Power implements IMath {
		public Exp(Expression power) {
			super(Constant.EXP, power);
		}

		@Override
		public Expression differentiate(char var) {
			return Product.create( // e^(f) * f'
					this, // e^(f)
					power.differentiate(var) // f'
			); // end e^(f) * f'
		}
	}
}