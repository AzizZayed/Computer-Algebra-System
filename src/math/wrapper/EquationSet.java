package math.wrapper;

import java.util.ArrayList;
import java.util.HashMap;

public class EquationSet {

	private ArrayList<Equation> equations = new ArrayList<Equation>();
	private HashMap<Character, Double> varValues = new HashMap<>();

	public EquationSet() {
		add(new Equation());
	}

	public void addEquation(String eq) {
		add(new Equation(eq));
	}
	
	private void add(Equation equation) {
		equations.add(equation);
		equation.variables.forEach(key -> varValues.putIfAbsent(key, 1d));
		System.out.println(varValues);
	}

	public void calculate() {
		equations.forEach(equation -> System.out.println(equation.valueAt(varValues)));
	}
	
	public void set(char c, double value) {
		varValues.replace(c, value);
	}
}
