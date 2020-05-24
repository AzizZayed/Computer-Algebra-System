package math.structure;

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
	public double evaluate(double x) {
		return numerator.evaluate(x) / denominator.evaluate(x);
	}

	@Override
	public String toString() {
		return "(" + numerator.toString() + "/" + denominator.toString() + ")";
	}

	@Override
	public String toLatex() {
		return "\\left(\\frac{" + numerator.toLatex() + "}{" + denominator.toLatex() + "}\\right)";
	}
}