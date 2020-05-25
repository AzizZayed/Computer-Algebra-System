package math.structure;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Stack;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.math.NumberUtils;

import math.structure.BracketFunction.Abs;
import math.structure.BracketFunction.Ceiling;
import math.structure.BracketFunction.Floor;
import math.structure.Function.Max;
import math.structure.Function.Min;
import math.structure.InverseTrigonometricFunction.ArcCos;
import math.structure.InverseTrigonometricFunction.ArcSin;
import math.structure.InverseTrigonometricFunction.ArcTan;
import math.structure.Log.Ln;
import math.structure.TrigonometricFunction.Cos;
import math.structure.TrigonometricFunction.Cot;
import math.structure.TrigonometricFunction.Csc;
import math.structure.TrigonometricFunction.Sec;
import math.structure.TrigonometricFunction.Sin;
import math.structure.TrigonometricFunction.Tan;

/**
 * A class with static functions that help with parsing a mathematical
 * expression
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Parser {

	/**
	 * clean up the given expression to parse more efficiently
	 * 
	 * @param exp - given expression
	 * @return the clean expression
	 */
	public static String clean(String exp) {
		exp = exp.trim();
		exp = exp.replace(" ", "");
		exp = exp.replace("[", "(");
		exp = exp.replace("]", ")");
		exp = exp.replace("{", "(");
		exp = exp.replace("}", ")");
		exp = exp.replace("()", "");
		exp = exp.replace("-", "+-1*");
		exp = exp.replace(")(", ")*(");
		exp = removeUnnecessaryBracket(exp);
		return exp;
	}

	/**
	 * parse the given expression into an expression tree
	 * 
	 * @param exp - expression to parse
	 * @return expression tree
	 */
	public static Expression parseExpression(String exp, HashSet<Character> vars) {
//		exp = clean(exp);

		if (!isValidExpression(exp))
			throw new IllegalArgumentException("Invalid Expression");

		return generate(exp, vars);
	}

	/**
	 * remove the unnecessary brackets from an expression
	 * 
	 * @param exp - expression
	 * @return the clean expression
	 */
	private static String removeUnnecessaryBracket(String exp) {
		int[] firstBrackets = getFirstPairOfBrackets(exp);

		if (firstBrackets != null && firstBrackets.length > 0 && firstBrackets[0] == 0
				&& firstBrackets[1] == exp.length() - 1)
			exp = exp.substring(1, exp.length() - 1);

		return exp;
	}

	/**
	 * generate an expression tree from the given expression
	 * 
	 * @param strExp - given expression
	 * @return the expression tree
	 */
	private static Expression generate(String strExp, HashSet<Character> vars) {
		strExp = removeUnnecessaryBracket(strExp);

		if (strExp.contains("(")) {
			int[] firstBrackets = getFirstPairOfBrackets(strExp);

			String cut = strExp; // where we will cut out the inside of the brackets
			LinkedList<String> remove = new LinkedList<String>();
			while (firstBrackets != null) { // run until no more brackets to analyze
				String rem = cut.substring(firstBrackets[0] + 1, firstBrackets[1]);
				remove.add(rem);
				cut = StringUtils.replaceOnce(cut, '(' + rem + ')', "()");
				firstBrackets = getFirstPairOfBrackets(cut);
			}

			if (cut.contains("+")) { // parse addition
				String[] exps = StringUtils.split(cut, "+");

				// replace all the () with the respective expression
				for (int i = 0; i < exps.length; i++)
					while (exps[i].contains("()"))
						exps[i] = StringUtils.replaceOnce(exps[i], "()", "(" + remove.pop() + ")");

				return Sum.create(vars, exps); // finally create sum node with recursively generated children
			} else if (cut.contains("*")) { // parse multiplication
				String[] exps = StringUtils.split(cut, "*");

				// replace all the () with the respective expression
				for (int i = 0; i < exps.length; i++)
					while (exps[i].contains("()"))
						exps[i] = StringUtils.replaceOnce(exps[i], "()", "(" + remove.pop() + ")");

				return Product.create(vars, exps); // finally create product node with recursively generated children
			} else if (cut.contains("/")) { // parse division
				int sign = cut.indexOf('/');
				String num = cut.substring(0, sign);
				String denum = cut.substring(sign + 1);

				while (num.contains("()"))
					num = StringUtils.replaceOnce(num, "()", "(" + remove.pop() + ")");
				while (denum.contains("()"))
					denum = StringUtils.replaceOnce(denum, "()", "(" + remove.pop() + ")");

				return new Fraction(generate(num, vars), generate(denum, vars)); // create fraction with generated children
			} else if (cut.contains("^")) { // parse powers
				int sign = cut.indexOf('^');
				String base = cut.substring(0, sign);
				String power = cut.substring(sign + 1);

				while (base.contains("()"))
					base = StringUtils.replaceOnce(base, "()", "(" + remove.pop() + ")");
				while (power.contains("()"))
					power = StringUtils.replaceOnce(power, "()", "(" + remove.pop() + ")");

				return new Power(generate(base, vars), generate(power, vars));
			} else if (cut.equals("sqrt()")) // square root
				return new Power(generate(remove.pop(), vars), new Constant(0.5d));
			
			else if (cut.equals("sin()")) // sin
				return new Sin(generate(remove.pop(), vars));
			else if (cut.equals("cos()")) // cos
				return new Cos(generate(remove.pop(), vars));
			else if (cut.equals("tan()")) // tan
				return new Tan(generate(remove.pop(), vars));

			else if (cut.equals("csc()")) // csc
				return new Csc(generate(remove.pop(), vars));
			else if (cut.equals("sec()")) // sec
				return new Sec(generate(remove.pop(), vars));
			else if (cut.equals("cot()")) // cot
				return new Cot(generate(remove.pop(), vars));

			else if (cut.equals("arcsin()")) // arcsin
				return new ArcSin(generate(remove.pop(), vars));
			else if (cut.equals("arccos()")) // arccos
				return new ArcCos(generate(remove.pop(), vars));
			else if (cut.equals("arctan()")) // arctan
				return new ArcTan(generate(remove.pop(), vars));

			else if (cut.equals("abs()")) // absolute value
				return new Abs(generate(remove.pop(), vars));

			else if (cut.equals("floor()")) // floor function
				return new Floor(generate(remove.pop(), vars));
			else if (cut.equals("ceil()")) // ceiling function
				return new Ceiling(generate(remove.pop(), vars));

			else if (cut.equals("max()")) { // max function
				String in = remove.pop();
				int sign = in.indexOf(",");
				String in1 = in.substring(0, sign);
				String in2 = in.substring(sign + 1);
				return new Max(generate(in1, vars), generate(in2, vars));
			} else if (cut.equals("min()")) { // min function
				String in = remove.pop();
				int sign = in.indexOf(",");
				String in1 = in.substring(0, sign);
				String in2 = in.substring(sign + 1);
				return new Min(generate(in1, vars), generate(in2, vars));
				
			} else if (cut.equals("log()")) // logarithm
				return new Log(generate(remove.pop(), vars));
			else if (cut.equals("ln()")) // natural logarithm
				return new Ln(generate(remove.pop(), vars));
			else if (cut.substring(0, 4).equals("log_")) { // log with specified base
				String log = cut.substring(4);
				int sign = log.indexOf('_');
				String base = log.substring(0, sign);
				String num = log.substring(sign + 1);

				while (base.contains("()"))
					base = StringUtils.replaceOnce(base, "()", "(" + remove.pop() + ")");
				while (num.contains("()"))
					num = StringUtils.replaceOnce(num, "()", "(" + remove.pop() + ")");
				
				return new Log(generate(base, vars), generate(num, vars));
			}

//		} else if (strExp.equals("x")) // x variable
//			return new Variable();	
		} else if (strExp.equals("e")) // letter e
			return new Constant(Constant.EXP.getValue());
		else if (strExp.length() == 1 && (Character.isAlphabetic(strExp.charAt(0)))) {
			char c = strExp.charAt(0);
			vars.add(c);
			return new Variable(c);
		} else if (NumberUtils.isParsable(strExp)) // numbers
			return new Constant(NumberUtils.createDouble(strExp));
		
		else if (strExp.contains("+")) { // parse addition
			String[] exps = StringUtils.split(strExp, "+");
			return Sum.create(vars, exps);
			
		} else if (strExp.contains("*")) { // parse multiplication
			String[] exps = StringUtils.split(strExp, "*");
			return Product.create(vars, exps);
			
		} else if (strExp.contains("/")) { // parse divisions
			int sign = strExp.indexOf('/');
			String num = strExp.substring(0, sign);
			String denum = strExp.substring(sign + 1);
			return new Fraction(generate(num, vars), generate(denum, vars));
			
		} else if (strExp.contains("^")) { // parse powers
			int sign = strExp.indexOf('^');
			String base = strExp.substring(0, sign);
			String power = strExp.substring(sign + 1);
			return new Power(generate(base, vars), generate(power, vars));
		} else if (strExp.substring(0, 2).equals("ln")) // natural log
			return new Ln(generate(strExp.substring(2), vars));

		else if (strExp.substring(0, 3).equals("sin")) // sin
			return new Sin(generate(strExp.substring(3), vars));
		else if (strExp.substring(0, 3).equals("cos")) // cos
			return new Cos(generate(strExp.substring(3), vars));
		else if (strExp.substring(0, 3).equals("tan")) // tan
			return new Tan(generate(strExp.substring(3), vars));

		else if (strExp.substring(0, 3).equals("csc")) // csc
			return new Csc(generate(strExp.substring(3), vars));
		else if (strExp.substring(0, 3).equals("sec")) // sec
			return new Sec(generate(strExp.substring(3), vars));
		else if (strExp.substring(0, 3).equals("cot")) // cot
			return new Cot(generate(strExp.substring(3), vars));

		else if (strExp.substring(0, 3).equals("abs")) // absolute value
			return new Abs(generate(strExp.substring(3), vars));

		else if (strExp.substring(0, 3).equals("log") && strExp.length() < 4) // log
			return new Log(generate(strExp.substring(3), vars));
		else if (strExp.substring(0, 4).equals("log_")) { // log with specific single expression base where brackets are
															// not needed
			int sign = strExp.substring(4).indexOf('_') + 4;
			String base = strExp.substring(4, sign);
			String num = strExp.substring(sign + 1);
			return new Log(generate(base, vars), generate(num, vars));

		} else if (strExp.substring(0, 4).equals("ceil")) // ceiling function
			return new Ceiling(generate(strExp.substring(4), vars));
		else if (strExp.substring(0, 4).equals("sqrt")) // sqrt function
			return new Power(generate(strExp.substring(4), vars), new Constant(0.5d));
		else if (strExp.substring(0, 5).equals("floor")) // floor function
			return new Floor(generate(strExp.substring(5), vars));

		else if (strExp.substring(0, 6).equals("arcsin")) // arcsin
			return new ArcSin(generate(strExp.substring(6), vars));
		else if (strExp.substring(0, 6).equals("arccos")) // arccos
			return new ArcCos(generate(strExp.substring(6), vars));
		else if (strExp.substring(0, 6).equals("arctan")) // arctan
			return new ArcTan(generate(strExp.substring(6), vars));

		return null;
	}

	/**
	 * determine the indices of the first pair of brackets in the given expression
	 * 
	 * @param expr - the given expression
	 * @return an array of 2 with the indices to the pair of brackets
	 */
	private static int[] getFirstPairOfBrackets(String expr) {
		String exp = expr.replace("()", "");
		if (exp == null || exp.isEmpty())
			return null;
		ArrayList<Integer> open = new ArrayList<Integer>();
		ArrayList<Integer> closed = new ArrayList<Integer>();
		Stack<Character> stack = new Stack<Character>();
		for (int i = 0; i < exp.length(); i++) {
			char c = exp.charAt(i);
			if (c == '(') {
				stack.add(c);
				open.add(i);
				int j;
				for (j = i + 1; j < exp.length() && !stack.isEmpty(); j++) {
					c = exp.charAt(j);
					if (c == '(')
						stack.add(c);
					else if (c == ')')
						stack.pop();
				}
				closed.add(j - 1);
			}
		}

		if (open.isEmpty())
			return null;

		int l = StringUtils.countMatches(expr, "()");
		return new int[] { open.get(0) + 2 * l, closed.get(0) + 2 * l };
	}

	/**
	 * check if a given expression is mathematically valid
	 * 
	 * @param exp - given expression to check
	 * @return true if valid, false otherwise
	 */
	private static boolean isValidExpression(String exp) {
		// test for unbalanced brackets
		if (exp == null || exp.isEmpty())
			return false;

		// test for balanced brackets
		if (!balancedBrackets(exp))
			return false;

		// test undefined duplicates
		if (exp.contains("//") || exp.contains("^^") || exp.contains("**") || exp.contains("++") || exp.contains("--"))
			return false;

		return true;
	}

	/**
	 * check if the brackets in an expression are balanced
	 * 
	 * @param exp - given expression to run check on
	 * @return true if balanced, false if otherwise
	 */
	private static boolean balancedBrackets(String exp) {
		Stack<Character> stack = new Stack<Character>();

		for (int i = 0; i < exp.length(); i++) {
			if (exp.charAt(i) == '(')
				stack.push(exp.charAt(i));
			else if (exp.charAt(i) == ')') {
				if (stack.isEmpty())
					return false;
				else {
					char c1 = stack.pop();
					char c2 = exp.charAt(i);
					if (!(c1 == '(' && c2 == ')'))
						return false;
				}
			}
		}
		return stack.isEmpty();
	}
}