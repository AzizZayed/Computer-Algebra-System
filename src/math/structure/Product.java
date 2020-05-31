package math.structure;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;

/**
 * a class representing a finite product
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Product extends Operator implements IMath {

	public static final ExpressionSorter SORTER = new ExpressionSorter(false); // sorter

	private Product(Expression... expressions) {
		super("product", '*', expressions);
	}

	private Product(HashSet<Character> vars, String... strExpression) {
		super("product", '*', vars, strExpression);
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

		// remove all the 1s and if there is a zero, return a zero constant
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
		if (valid.size() == 2)
			if (valid.get(0) instanceof Constant && valid.get(1) instanceof Constant) {
				Constant a = (Constant) valid.get(0);
				Constant b = (Constant) valid.get(1);
				System.out.println(a);
				System.out.println(b);

				return new Constant(a.getValue() * b.getValue());
			}

		/*
		 * transform fractions into products
		 */
		////////////////////

		/*
		 * extract inner products if any
		 */
		for (int i = valid.size() - 1; i >= 0; i--) {
			Expression exp = valid.get(i);
			if (exp instanceof Product) {
				Product prod = (Product) exp;
				for (int j = 0; j < prod.children.length; j++) {
					valid.add(prod.children[j]);
				}
				valid.remove(i);
			}
		}

		ArrayList<Expression> grouped = new ArrayList<>(); // grouped expressions

		/*
		 * group constant
		 */
		double total = 1d;
		for (int i = valid.size() - 1; i >= 0; i--) {
			Expression expression = valid.get(i);
			if (expression instanceof Constant) {
				total *= ((Constant) expression).getValue();
				valid.remove(i);
			}
		}
		if (total != 1d)
			grouped.add(new Constant(total));

		/*
		 * transform everything into a power to make simplifications easier
		 */
		for (int i = 0; i < valid.size(); i++) {
			Expression exp = valid.get(i);
			if (!(exp instanceof Power)) {
				valid.set(i, new Power(exp, new Constant(1d)));
			}
		}

		/*
		 * group powers
		 */
		ArrayList<Power> powers = new ArrayList<>();
		for (int i = valid.size() - 1; i >= 0; i--) {
			Expression expression = valid.get(i);
			if (expression instanceof Power) {
				powers.add((Power) expression);
				valid.remove(i);
			}
		}
		for (int i = powers.size() - 1; i > 0; i--) {
			for (int j = i - 1; j >= 0; j--) {
				Power p1 = powers.get(i);
				Power p2 = powers.get(j);
				if (p1.expr.equals(p2.expr)) {
					p1.power = Sum.create(p1.power, p2.power); // add powers
					powers.remove(j);
					i--;
				}
			}
		}
		for (int i = powers.size() - 1; i > 0; i--) {
			for (int j = i - 1; j >= 0; j--) {
				Power p1 = powers.get(i);
				Power p2 = powers.get(j);
				if (p1.power.equals(p2.power)) {
					p1.expr = Product.create(p1.expr, p2.expr); // multiply bases
					powers.remove(j);
					i--;
				}
			}
		}
		grouped.addAll(powers);

		/*
		 * rest of the expressions that were not eligible for simplifications
		 */
		grouped.addAll(valid);

		Collections.sort(grouped, SORTER); // sort

		if (grouped.isEmpty())
			return new Constant(1d);

		return new Product(grouped.toArray(new Expression[0]));
//		return new Product(valid.toArray(new Expression[0]));
//		return new Product(expressions);
	}

	@Override
	protected double operate(double a, double b) {
		return a * b;
	}

	@Override
	protected double neutral() {
		return 1d;
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
		 * (f(x)g(x)h(x)i(x)) = f'ghi + fg'hi + fgh'i + fghi'------------
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
	public Expression simplify() {
		return create(simplifiedChildren());
	}
}