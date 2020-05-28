package math.structure;

import java.util.HashMap;

/**
 * class to represent a fraction
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Fraction extends Expression implements IMath {

	protected Expression numerator, denominator; // components

	public Fraction(Expression num, Expression denom) {
		super("fraction");
		numerator = num;
		denominator = denom;
	}

	@Override
	public double evaluate(HashMap<Character, Double> varValues) {
		return numerator.evaluate(varValues) / denominator.evaluate(varValues);
	}

	@Override
	public String toString() {
		return "(" + numerator.toString() + "/" + denominator.toString() + ")";
	}

	@Override
	public String toLatex() {
		return "\\frac{" + numerator.toLatex() + "}{" + denominator.toLatex() + "}";
	}

	@Override
	public boolean equals(Expression e) {
		if (e instanceof Fraction) {
			Fraction frac = (Fraction) e;
			return numerator.equals(frac.numerator) && denominator.equals(frac.denominator);
		}
		return false;
	}

	@Override
	public Expression differentiate(char var) {
		return new Fraction( // quotient rule
				Sum.create( // f'g - fg'
						Product.create( // f'g
								numerator.differentiate(var), // f'g
								denominator // g
						), // end f'*g
						Product.create( // -fg'
								new Constant(-1d), // -1
								numerator, // f
								denominator.differentiate(var) // g'
						) // end -fg'
				), // end f'g - fg'
				new Power( // g^2
						denominator, // g
						new Constant(2d) // 2
				) // end g^2
		); // end quotient rule
	}
}