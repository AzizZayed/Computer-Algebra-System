package math.structure;

/**
 * class to represent any term like x, y, z
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Variable extends Expression implements IMath {

	private char symbol;

	public Variable(char sym) {
		symbol = sym;
	}

	public Variable() {
		symbol = 'x';
	}

	@Override
	public double evaluate(double x) {
		return x;
	}

	@Override
	public String toString() {
		return Character.toString(symbol);
	}

	@Override
	public String toLatex() {
		return toString();
	}
}