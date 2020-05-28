package math.structure;

import java.util.HashMap;

/**
 * logarithmic functions
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Log extends Function implements IMath {

	private Expression base; // the expression for the base of the logarithm

	/*
	 * constructor with base expression if it's custom, so like log base 5
	 */
	public Log(Expression base, Expression expr) {
		super(expr);
		this.base = base;
	}

	/*
	 * constructor with base 10
	 */
	public Log(Expression expr) {
		super(expr);
		this.base = new Constant(10.0d);
	}

	@Override
	public double evaluate(HashMap<Character, Double> varValues) {
		return Math.log(expr.evaluate(varValues)) / Math.log(base.evaluate(varValues));
	}

	@Override
	public String toString() {
		if (needsBrackets())
			return "log_" + base.toString() + "_(" + expr.toString() + ")";
		return "log_" + base.toString() + "_" + expr.toString();
	}

	@Override
	public String toLatex() {
		if (needsBrackets())
			return "log_{" + base.toLatex() + "}{\\left(" + expr.toLatex() + "\\right)}";
		return "log_{" + base.toLatex() + "}{" + expr.toLatex() + "}";
	}

	protected boolean needsBrackets() {
		return expr instanceof Operator || expr instanceof Power || expr instanceof Fraction || expr instanceof Log;
	}

	@Override
	public boolean equals(Expression e) {
		if (e instanceof Log) {
			Log log = (Log) e;
			return expr.equals(log.expr) && base.equals(log.base);
		}
		return false;
	}

	@Override
	public Expression differentiate(char var) {
		boolean baseIsNumber = base instanceof Constant;
		boolean inputIsNumber = expr instanceof Constant;

		if (baseIsNumber && inputIsNumber) // case log_b(k), where b and k are both numbers (constants)
			return new Constant(0d);

		if (baseIsNumber && !inputIsNumber) // case log_b( f(x) ) where b is a numbers (constants)
			return Product.create( // f' * [ f * lnb ]^(-1)
					expr.differentiate(var), // f'
					new Power( // [f * lnb]^(-1)
							Product.create( // f * lnb
									expr, // f
									new Ln(base) // lnb
							), // end f * lnb
							new Constant(-1d) // -1
					) // end [f * lnb]^(-1)
			); // end f' * [ f * lnb ]^(-1)

		// otherwise: case log_(g(x))(f(x))
		return new Fraction( // derivative of ln(f(x)) / ln(g(x))
				new Ln(expr), // ln(f(x))
				new Ln(base) // ln(g(x))
		) // end of ln(f(x)) / ln(g(x))
				.differentiate(var); // end derivative of ln(f(x)) / ln(g(x))
	}
	
	@Override
	public String getName() {
		return "logarithm";
	}

	/*
	 * natural logarithm
	 */
	public static class Ln extends Log implements IMath {
		public Ln(Expression expr) {
			super(Constant.EXP, expr);
		}

		@Override
		public String toString() {
			if (needsBrackets())
				return "ln(" + expr.toString() + ")";
			return "ln" + expr.toString();
		}

		@Override
		public String toLatex() {
			if (needsBrackets())
				return "ln\\left(" + expr.toLatex() + "\\right)";
			return "ln" + expr.toLatex();
		}

		@Override
		public Expression differentiate(char var) {
			return Product.create( // f' * f^(-1)
					expr.differentiate(var), // f'
					new Power( // f^(-1)
							expr, // f
							new Constant(-1d) // -1
					) // end f^(-1)
			); // end f' * f^(-1)
		}
	}
}