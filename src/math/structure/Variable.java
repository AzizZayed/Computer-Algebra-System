package math.structure;

import java.util.HashMap;

/**
 * class to represent any term like x, y, z
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Variable extends Expression implements IMath {

	private char symbol; // variable character

	public Variable(char sym) {
		super("variable");
		symbol = sym;
	}

	public Variable() {
		this('x');
	}

	@Override
	public double evaluate(HashMap<Character, Double> varValues) {
		return varValues.get(symbol);
	}

	@Override
	public String toString() {
		return Character.toString(symbol);
	}

	@Override
	public String toLatex() {
		return toString();
	}

	@Override
	public boolean equals(Expression e) {
		if (e instanceof Variable)
			return symbol == ((Variable) e).symbol;
		return false;
	}

	@Override
	public Expression differentiate(char var) {
		double derivative = symbol == var ? 1d : 0d;
		return new Constant(derivative);
	}
}