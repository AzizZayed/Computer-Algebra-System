package math.main;

import math.structure.MathTree;

public class MainTester {
	public static void main(String[] args) {
		MathTree tree = new MathTree();
		double testVal = -0.9205d;
		System.out.println(tree + "|x = " + testVal + " -> " + tree.evaluate(testVal));
	}
}
