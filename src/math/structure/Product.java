package math.structure;

import java.util.HashSet;

/**
 * a class representing a finite product
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Product extends Operator implements IMath {
	public Product(Expression... expressions) {
		super('*', expressions);
	}

	protected Product(HashSet<Character> vars, String... strExpression) {
		super('*', vars, strExpression);
	}

	public static Expression create(HashSet<Character> vars, String... strExpression) {
		if (strExpression.length == 0)
			return null;
		else if (strExpression.length == 1)
			return Parser.generateExpression(strExpression[0], vars);
		return new Product(vars, strExpression);
	}

	@Override
	protected double operate(double a, double b) {
		return a * b;
	}

	@Override
	protected double neutral() {
		return 1;
	}

	@Override
	protected void latex(int index, StringBuilder builder) {
		Constant constant = null;
		if (children[index] instanceof Constant)
			constant = (Constant) children[index];

		if (constant != null && Math.signum(constant.getValue()) < 0)
			builder.append('-');
		else
			builder.append(children[index].toLatex());
	}

	@Override
	protected boolean needsBrackets(Expression e) {
		return e instanceof Sum;
	}
}