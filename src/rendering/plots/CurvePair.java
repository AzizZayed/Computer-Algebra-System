package rendering.plots;

import java.util.HashMap;

import math.structure.Equation;
import rendering.GUI.LatexRenderer;
import rendering.tools.Grid;

public class CurvePair {

	private Curve function, derivative;
//	private boolean numericalDerivative = false;

	public CurvePair(Equation eq) {
		String latex = "y = " + eq.toLatex();
		Equation simplified = eq.simplified();
		function = new Curve(simplified, LatexRenderer.toImage(latex));
		Equation der = simplified.derivative('x');
		latex = "y_x = " + der.toLatex();
		derivative = new Curve(der, LatexRenderer.toImage(latex));
	}

	public void update(Grid grid, HashMap<Character, Double> varValues) {
		function.update(grid, varValues);
		derivative.update(grid, varValues);
	}

	/**
	 * @return the function
	 */
	public Curve getFunction() {
		return function;
	}

	/**
	 * @return the derivative
	 */
	public Curve getDerivative() {
		return derivative;
	}
	
	public void cleanup() {
		function.cleanup();
		derivative.cleanup();
	}
}