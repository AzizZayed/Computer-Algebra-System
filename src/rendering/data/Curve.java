package rendering.data;

import java.util.HashMap;

import math.structure.Equation;
import rendering.GUI.LatexRenderer;

public class Curve {

	private GraphableEquation function, derivative;
//	private boolean numericalDerivative = false;

	public Curve(Equation eq) {
		String latex = "y = " + eq.toLatex();
		function = new GraphableEquation(eq.simplified(), new float[] { 0, 0, 0, 1 }, LatexRenderer.toImage(latex));
		Equation der = eq.derivative('x');
		latex = "y_x = " + der.toLatex();
		derivative = new GraphableEquation(der, new float[] { 0, 0, 0, 1 }, LatexRenderer.toImage(latex));
	}

	public void update(Grid grid, boolean updateData, HashMap<Character, Double> varValues) {
		function.update(grid, updateData, varValues);
		derivative.update(grid, updateData, varValues);
		varValues.remove('x');
	}

	/**
	 * @return the function
	 */
	public GraphableEquation getFunction() {
		return function;
	}

	/**
	 * @return the derivative
	 */
	public GraphableEquation getDerivative() {
		return derivative;
	}
}