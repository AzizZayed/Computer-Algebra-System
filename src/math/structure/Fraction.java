package math.structure;

import java.util.HashMap;

/**
 * class to represent a fraction
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Fraction extends Expression implements IMath {

	private Expression numerator, denominator; // components

	public Fraction(Expression num, Expression denom) {
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
}