package math.wrapper;

import java.util.ArrayList;
import java.util.HashMap;

import math.structure.IMath;

public class EquationSet implements IMath {

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
//		System.out.println(varValues);
	}

	public void calculate() {
		equations.forEach(equation -> System.out.println(equation.valueAt(varValues)));
	}

	public void setValue(char c, double value) {
		varValues.replace(c, value);
	}

	@Override
	public String toString() {
		return null;
	}
	
	@Override
	public String toLatex() {
		return null;
	}
}
