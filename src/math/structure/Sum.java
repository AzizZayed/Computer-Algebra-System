package math.structure;

import java.util.HashSet;

/**
 * a class representing a finite sum
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Sum extends Operator implements IMath {
	public Sum(Expression... expressions) {
		super('+', expressions);
	}

	public Sum(HashSet<Character> vars, String... strExpression) {
		super('+', vars, strExpression);
	}

	public static Expression create(HashSet<Character> vars, String... strExpression) {
		if (strExpression.length == 0)
			return null;
		else if (strExpression.length == 1)
			return Parser.parseExpression(strExpression[0], vars);
		return new Sum(vars, strExpression);
	}

	@Override
	protected double operate(double a, double b) {
		return a + b;
	}

	@Override
	protected double neutral() {
		return 0;
	}

	@Override
	protected void string(int index, StringBuilder builder) {
		builder.append(symbol);
		builder.append(' ');
		builder.append(children[index]);
	}

	@Override
	protected void latex(int index, StringBuilder builder) {
		boolean putSymbol = true;

		if (children[index] instanceof Product) {
			Product product = (Product) children[index];
			if (product.children[0] instanceof Constant) {
				Constant constant = (Constant) product.children[0];
				if (Math.signum(constant.getValue()) < 0)
					putSymbol = false;
			}
		}

		if (putSymbol && index != 0)
			builder.append(symbol);
		builder.append(' ');
		builder.append(children[index].toLatex());
	}

	@Override
	protected boolean needsBrackets() {
		return false;
	}
}