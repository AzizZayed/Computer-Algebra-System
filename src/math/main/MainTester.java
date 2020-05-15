package math.main;

import math.structure.MathTree;

public class MainTester {
	public static void main(String[] args) {
		double t;
		
		t = System.nanoTime();
		MathTree tree = new MathTree();
		System.out.println("Diff: " + (System.nanoTime() - t));
		
		t = System.nanoTime();
		double testVal = -0.9205d;
		System.out.println("Diff: " + (System.nanoTime() - t));
		
		t = System.nanoTime();
		System.out.println(tree + " |x = " + testVal + " -> " + tree.evaluate(testVal));
		System.out.println("Diff: " + (System.nanoTime() - t));
	}
}
