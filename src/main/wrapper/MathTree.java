package main.wrapper;

import java.util.LinkedList;

import javax.swing.JOptionPane;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.math.NumberUtils;
import org.scilab.forge.jlatexmath.TeXConstants;
import org.scilab.forge.jlatexmath.TeXFormula;
import org.scilab.forge.jlatexmath.TeXIcon;

import math.structure.BracketFunction.Abs;
import math.structure.BracketFunction.Ceiling;
import math.structure.BracketFunction.Floor;
import math.structure.Expression;
import math.structure.Expression.Constant;
import math.structure.Expression.Fraction;
import math.structure.Expression.Variable;
import math.structure.IMath;
import math.structure.Log;
import math.structure.Log.Ln;
import math.structure.Operator.Product;
import math.structure.Operator.Sum;
import math.structure.Power;
import math.structure.Power.Exp;
import math.structure.TrigonometricFunction.Cos;
import math.structure.TrigonometricFunction.Sin;
import math.structure.TrigonometricFunction.Tan;

/**
 * class containing the expression tree: the entire expression
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class MathTree implements IMath {

	private String expression;
	private Expression root; // the root function
	private ExpressionParser parser;

	public MathTree(String exp) {
		parser = new ExpressionParser(exp);

		if (!parser.isValidExpression())
			throw new IllegalArgumentException("Invalid Expression");

		expression = parser.get();
		root = generate(expression);
	}

	public MathTree() {
		root = new Fraction(
				new Sum(new Exp(new Power(new Variable(), new Constant(1d / 2d))),
						new Product(new Constant(2), new Variable()), new Fraction(new Constant(1), new Variable())),
				new Product(new Power(new Variable(), new Constant(1d / 2d)),
						new Sin(new Cos(new Tan(new Variable())))));
	}

	private Expression generate(String strExp) {
		int[] p = ExpressionParser.getBiggestBracket(strExp);

		if (p != null && p.length > 0 && p[0] == 0 && p[1] == strExp.length() - 1)
			strExp = strExp.substring(1, strExp.length() - 1);

//		System.out.println("In: " + strExp);

		if (strExp.contains("(")) {
			int[] pos = ExpressionParser.getBiggestBracket(strExp);

			String cut = strExp; // where we will cut out the inside of the brackets
			LinkedList<String> remove = new LinkedList<String>();
			while (pos != null) {
				String rem = cut.substring(pos[0] + 1, pos[1]);
				remove.add(rem);
//				System.out.println(cut);
				cut = StringUtils.replaceOnce(cut, '(' + rem + ')', "()");
				pos = ExpressionParser.getBiggestBracket(cut);
			}
//			System.out.println("Final: " + cut);
//			System.out.println("Brackets: " + remove);

			if (cut.contains("+")) {
				String[] exps = StringUtils.split(cut, "+");
//				System.out.println(Arrays.toString(exps));
				// replace all the () with the respective expression
				for (int i = 0; i < exps.length; i++)
					while (exps[i].contains("()"))
						exps[i] = StringUtils.replaceOnce(exps[i], "()", "(" + remove.pop() + ")");

				// create children expression for sum
				Expression[] exp = new Expression[exps.length];
				for (int i = 0; i < exp.length; i++)
					exp[i] = generate(exps[i]);

				return new Sum(exp);// finally create it
			} else if (cut.contains("*")) {
				String[] exps = StringUtils.split(cut, "*");

				// replace all the () with the respective expression
				for (int i = 0; i < exps.length; i++)
					while (exps[i].contains("()"))
						exps[i] = StringUtils.replaceOnce(exps[i], "()", "(" + remove.pop() + ")");

				// create children expression for product
				Expression[] exp = new Expression[exps.length];
				for (int i = 0; i < exp.length; i++)
					exp[i] = generate(exps[i]);

				return new Product(exp); // finally create it
			} else if (strExp.contains("/")) {
				int sign = cut.indexOf('/');
				String num = cut.substring(0, sign);
				String denum = cut.substring(sign + 1);

				while (num.contains("()"))
					num = StringUtils.replaceOnce(num, "()", "(" + remove.pop() + ")");
				while (denum.contains("()"))
					denum = StringUtils.replaceOnce(denum, "()", "(" + remove.pop() + ")");

				return new Fraction(generate(num), generate(denum));
			} else if (cut.contains("^")) {
				int sign = cut.indexOf('^');
				String base = cut.substring(0, sign);
				String power = cut.substring(sign + 1);

				while (base.contains("()"))
					base = StringUtils.replaceOnce(base, "()", "(" + remove.pop() + ")");
				while (power.contains("()"))
					power = StringUtils.replaceOnce(power, "()", "(" + remove.pop() + ")");

				return new Power(generate(base), generate(power));
			} else if (cut.equals("sin()"))
				return new Sin(generate(remove.pop()));
			else if (cut.equals("cos()"))
				return new Cos(generate(remove.pop()));
			else if (cut.equals("tan()"))
				return new Tan(generate(remove.pop()));
			else if (cut.equals("abs()"))
				return new Abs(generate(remove.pop()));
			else if (cut.equals("floor()"))
				return new Floor(generate(remove.pop()));
			else if (cut.equals("ceil()"))
				return new Ceiling(generate(remove.pop()));
			else if (cut.equals("log()"))
				return new Log(generate(remove.pop()));
			else if (cut.equals("ln()"))
				return new Ln(generate(remove.pop()));
			else if (cut.substring(0, 4).equals("log_")) {
				String log = cut.substring(4);
				int sign = log.indexOf('_');
				String base = log.substring(0, sign);
				String num = log.substring(sign + 1);

				while (base.contains("()"))
					base = StringUtils.replaceOnce(base, "()", "(" + remove.pop() + ")");
				while (num.contains("()"))
					num = StringUtils.replaceOnce(num, "()", "(" + remove.pop() + ")");

				return new Log(generate(base), generate(num));
			}
//			System.out.println("Final: " + cut);
//			System.out.println("Brackets: " + remove);

		} else if (strExp.equals("x"))
			return new Variable();
		else if (strExp.equals("e"))
			return new Constant(Constant.EXP.getValue());
		else if (NumberUtils.isParsable(strExp))
			return new Constant(NumberUtils.createDouble(strExp));
		else if (strExp.contains("+")) {
			String[] exps = StringUtils.split(strExp, "+");
			Expression[] exp = new Expression[exps.length];
			for (int i = 0; i < exp.length; i++)
				exp[i] = generate(exps[i]);
			return new Sum(exp);
		} else if (strExp.contains("*")) {
			String[] exps = StringUtils.split(strExp, "*");
			Expression[] exp = new Expression[exps.length];
			for (int i = 0; i < exp.length; i++)
				exp[i] = generate(exps[i]);
			return new Product(exp);
		} else if (strExp.contains("/")) {
			int sign = strExp.indexOf('/');
			String num = strExp.substring(0, sign);
			String denum = strExp.substring(sign + 1);
			return new Fraction(generate(num), generate(denum));
		} else if (strExp.contains("^")) {
			int sign = strExp.indexOf('^');
			String base = strExp.substring(0, sign);
			String power = strExp.substring(sign + 1);
			return new Power(generate(base), generate(power));
		} else if (strExp.substring(0, 2).equals("ln"))
			return new Ln(generate(strExp.substring(2)));
		else if (strExp.substring(0, 3).equals("sin"))
			return new Sin(generate(strExp.substring(3)));
		else if (strExp.substring(0, 3).equals("cos"))
			return new Cos(generate(strExp.substring(3)));
		else if (strExp.substring(0, 3).equals("tan"))
			return new Tan(generate(strExp.substring(3)));
		else if (strExp.substring(0, 3).equals("abs"))
			return new Abs(generate(strExp.substring(3)));
		else if (strExp.substring(0, 3).equals("log") && strExp.length() < 4)
			return new Log(generate(strExp.substring(3)));
		else if (strExp.substring(0, 4).equals("log_")) {
			int sign = strExp.substring(4).indexOf('_') + 4;
			String base = strExp.substring(4, sign);
			String num = strExp.substring(sign + 1);
			return new Log(generate(base), generate(num));
		} else if (strExp.substring(0, 4).equals("ceil"))
			return new Ceiling(generate(strExp.substring(4)));
		else if (strExp.substring(0, 5).equals("floor"))
			return new Floor(generate(strExp.substring(5)));

		return null;
	}

	public double valueAt(double x) {
		if (root == null)
			throw new NullPointerException("The expression is empty.");
		return root.evaluate(x);
	}

	@Override
	public String toString() {
		if (root == null)
			throw new NullPointerException("The expression is empty.");
		return "Tree Expression: " + root.toString();
	}

	public String getExpression() {
		return expression;
	}

	@Override
	public String toLatex() {
		String latex = root.toLatex();
//		System.out.println(latex.substring(230));

		// create a formula
		TeXFormula formula = new TeXFormula(latex);

		// render the formla to an icon of the same size as the formula.
		TeXIcon icon = formula.createTeXIcon(TeXConstants.STYLE_DISPLAY, 20);

		JOptionPane.showMessageDialog(null, "", "LaTeX", JOptionPane.PLAIN_MESSAGE, icon);

		return latex;
	}

}