package main.testing;

import java.util.ArrayList;

import math.wrapper.EquationSet;

/**
 * Tester/main class
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class MainTester {
	public static void main(String[] args) {

		ArrayList<String> expressions = new ArrayList<>();
		
		expressions.add("(e^x + 200)^2");
		expressions.add("e^(a*pi) - x*phi");
		
		EquationSet set = new EquationSet();
		expressions.forEach(exp -> set.addEquation(exp));
		set.set('x', 15);
		set.calculate();
	}
}
