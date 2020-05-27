package math.structure;

import java.util.HashSet;

/**
 * a class representing a finite product
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Product extends Operator implements IMath {
	protected Product(Expression... expressions) {
		super('*', expressions);
	}

	protected Product(HashSet<Character> vars, String... strExpression) {
		super('*', vars, strExpression);
	}

	public static Expression create(HashSet<Character> vars, String... strExpression) {
		if (strExpression.length == 0)
			return null;
		if (strExpression.length == 1)
			return Parser.generateExpression(strExpression[0], vars);
		return new Product(vars, strExpression);
	}

	public static Expression create(Expression... expressions) {
		if (expressions.length == 0)
			return null;
		if (expressions.length == 1)
			return expressions[0];
		return new Product(expressions);
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
//		Constant constant = null;
//		if (children[index] instanceof Constant)
//			constant = (Constant) children[index];
//
//		if (constant != null && Math.signum(constant.getValue()) < 0)
//			builder.append('-');
//		else if (!(constant != null && Math.abs(constant.getValue()) == 1d))
//			builder.append(children[index].toLatex());
		builder.append(children[index].toLatex());
//		if (index < children.length - 1)
//			builder.append(symbol);
	}

	@Override
	protected boolean needsBrackets(Expression e) {
		return e instanceof Sum;
	}

	@Override
	public Expression differentiate(char var) { // product rule for n functions
		/*
		 * (f(x)g(x)h(x))' = f'gh + fg'h + fgh'--------------------------
		 * (f(x)g(x)h(x)k(x)) = f'ghk + fg'hk + fgh'k + fghk'
		 */
		Expression[] sums = new Expression[children.length];

		for (int i = 0; i < sums.length; i++) {
			Expression[] products = new Expression[children.length];
			for (int j = 0; j < products.length; j++) {
				if (i == j)
					products[j] = children[j].differentiate(var);
				else
					products[j] = children[j];
			}
			sums[i] = Product.create(products);
		}
		return Sum.create(sums);
	}
}