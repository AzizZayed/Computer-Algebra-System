package main.wrapper;

import java.util.ArrayList;
import java.util.Stack;

import org.apache.commons.lang3.StringUtils;

public class ExpressionParser {

	private String exp;
	public int[] open = null, closed = null;

	public ExpressionParser(String exp) {
		exp = exp.trim();
		exp = exp.replace(" ", "");
		exp = exp.replace("[", "(");
		exp = exp.replace("]", ")");
		exp = exp.replace("{", "(");
		exp = exp.replace("}", ")");
		exp = exp.replace("()", "");
		exp = exp.replace("-", "+-1*");
		exp = exp.replace(")(", ")*(");
		this.exp = exp;
	}

	public boolean isValidExpression() {
		// test for unbalanced brackets
		if (exp == null || exp.isEmpty())
			return false;

		// test for balanced brackets
		if (!balancedBrackets())
			return false;

		// test undefined duplicates
		if (exp.contains("//") || exp.contains("^^") || exp.contains("**") || exp.contains("++") || exp.contains("--"))
			return false;

		return true;
	}

	private boolean balancedBrackets() {
		Stack<Character> stack = new Stack<Character>();

		for (int i = 0; i < exp.length(); i++) {
			if (exp.charAt(i) == '{' || exp.charAt(i) == '(' || exp.charAt(i) == '[')
				stack.push(exp.charAt(i));

			if (exp.charAt(i) == '}' || exp.charAt(i) == ')' || exp.charAt(i) == ']') {
				if (stack.isEmpty())
					return false;
				else {
					char c1 = stack.pop();
					char c2 = exp.charAt(i);
					if (!(c1 == '(' && c2 == ')' || c1 == '{' && c2 == '}' || c1 == '[' && c2 == ']'))
						return false;
				}
			}
		}
		return stack.isEmpty();
	}

	public String get() {
//		preClean();
		getBracketLocations();
		postClean();
		return exp;
	}

	private void getBracketLocations() {
//		System.out.println(exp.length());
		ArrayList<Integer> op = new ArrayList<Integer>();
		ArrayList<Integer> cl = new ArrayList<Integer>();
		Stack<Character> stack = new Stack<Character>();
		for (int i = 0; i < exp.length(); i++) {
			char c = exp.charAt(i);
			if (c == '(') {
				stack.add(c);
				op.add(i);
				int j;
				for (j = i + 1; j < exp.length() && !stack.isEmpty(); j++) {
					c = exp.charAt(j);
					if (c == '(')
						stack.add(c);
					else if (c == ')')
						stack.pop();
				}
				cl.add(j - 1);
			}
		}
		open = new int[op.size()];
		for (int i = 0; i < op.size(); i++)
			open[i] = op.get(i);
		closed = new int[cl.size()];
		for (int i = 0; i < cl.size(); i++)
			closed[i] = cl.get(i);
	}

	public static int[][] getBracketLocations(String exp) {
		exp = exp.replace("()", "");
		if (exp == null || exp.isEmpty())
			return null;
		ArrayList<Integer> op = new ArrayList<Integer>();
		ArrayList<Integer> cl = new ArrayList<Integer>();
		Stack<Character> stack = new Stack<Character>();
		for (int i = 0; i < exp.length(); i++) {
			char c = exp.charAt(i);
			if (c == '(') {
				stack.add(c);
				op.add(i);
				int j;
				for (j = i + 1; j < exp.length() && !stack.isEmpty(); j++) {
					c = exp.charAt(j);
					if (c == '(')
						stack.add(c);
					else if (c == ')')
						stack.pop();
				}
				cl.add(j - 1);
			}
		}

		if (op.isEmpty())
			return null;

		int[] open = new int[op.size()];
		for (int i = 0; i < op.size(); i++)
			open[i] = op.get(i);
		int[] closed = new int[cl.size()];
		for (int i = 0; i < cl.size(); i++)
			closed[i] = cl.get(i);

		return new int[][] { open, closed };
	}

	public static int[] getBiggestBracket(String expr) {
		String exp = expr.replace("()", "");
		if (exp == null || exp.isEmpty())
			return null;
		ArrayList<Integer> op = new ArrayList<Integer>();
		ArrayList<Integer> cl = new ArrayList<Integer>();
		Stack<Character> stack = new Stack<Character>();
		for (int i = 0; i < exp.length(); i++) {
			char c = exp.charAt(i);
			if (c == '(') {
				stack.add(c);
				op.add(i);
				int j;
				for (j = i + 1; j < exp.length() && !stack.isEmpty(); j++) {
					c = exp.charAt(j);
					if (c == '(')
						stack.add(c);
					else if (c == ')')
						stack.pop();
				}
				cl.add(j - 1);
			}
		}

		if (op.isEmpty())
			return null;

		int bi = 0, bn;
		bn = cl.get(0) - op.get(0);
		for (int i = 1; i < op.size(); i++) {
			int nbn = cl.get(i) - op.get(i);
			if (nbn > bn) {
				bi = i;
				bn = nbn;
			}
		}

		int l = StringUtils.countMatches(expr, "()");
		return new int[] { op.get(0) + 2 * l, cl.get(0) + 2 * l };
	}

	private void preClean() {
		// clean up the string first
		exp = exp.replace("[", "(");
		exp = exp.replace("]", ")");
		exp = exp.replace("{", "(");
		exp = exp.replace("}", ")");
		exp = exp.replace("()", "");
		exp = exp.replace("-", "+-1*");
	}

	private void postClean() {
		if (open != null && open.length > 0 && open[0] == 0 && closed[0] == exp.length() - 1)
			exp = exp.substring(1, exp.length() - 1);

//		System.out.println(exp);
	}
}
