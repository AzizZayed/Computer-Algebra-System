package math.structure;

import java.util.ArrayList;
import java.util.HashSet;

/**
 * a class representing a finite product
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Product extends Operator implements IMath {
	private Product(Expression... expressions) {
		super('*', expressions);
	}

	private Product(HashSet<Character> vars, String... strExpression) {
		super('*', vars, strExpression);
	}

	/**
	 * function to create an expression node with the given children as strings,
	 * they still need to be parsed. The point of this function is to perform early
	 * refactoring to make life easier later on. It does not have to return a
	 * product node if the refactored expression does not require one
	 * 
	 * @param vars          - the set of all variables
	 * @param strExpression - the array of strings to be parsed into expressions
	 * @return the refactored expression
	 */
	public static Expression create(HashSet<Character> vars, String... strExpression) {
		if (strExpression.length == 0)
			return null;
		if (strExpression.length == 1)
			return Parser.generateExpression(strExpression[0], vars);
		return new Product(vars, strExpression);
	}

	/**
	 * function to create expression node from the given expressions. The point of
	 * this function is to perform early refactoring and simplification to make life
	 * easier later on. It does not have to return a product node if the simplified
	 * expression does not require one
	 * 
	 * @param expressions - array of expressions
	 * @return simplified and refactored expression
	 */
	public static Expression create(Expression... expressions) {
		if (expressions.length == 0)
			return null;
		if (expressions.length == 1)
			return expressions[0];
		
		ArrayList<Expression> valid = new ArrayList<>();
		Constant c0 = new Constant(0d), c1 = new Constant(1d);
		for (int i = 0; i < expressions.length; i++) {
			if (expressions[i].equals(c0))
				return c0;
			if (!expressions[i].equals(c1))
				valid.add(expressions[i]);
		}
		
		if (valid.isEmpty())
			return c1;
		if (valid.size() == 1)
			return valid.get(0);

		return new Product(valid.toArray(new Expression[0]));
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
		 * special case for something like k*f(x) -> k*f'(x)
		 */
		if (children.length == 2)
			if (children[0] instanceof Constant)
				return Product.create( // k*f'(x)
						children[0], // k
						children[1].differentiate(var) // f'
				); // end k*f'(x)

		/*
		 * (f(x)g(x)h(x))' = f'gh + fg'h + fgh'--------------------------
		 * (f(x)g(x)h(x)k(x)) = f'ghk + fg'hk + fgh'k + fghk'------------
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
	
	@Override
	public String getName() {
		return "product";
	}
}