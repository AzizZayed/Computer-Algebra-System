package rendering.plots;

import java.util.HashMap;

import math.structure.Equation;
import rendering.GUI.LatexRenderer;
import rendering.tools.Grid;

/**
 * A wrapper class to hold a function of x and y and its derivatives with
 * respect to x and y
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class SurfaceTrio {

	private Surface function, xDerivative, yDerivative; // the function and its derivatives

	public SurfaceTrio(Equation eq) {
		String latex = "z = " + eq.toLatex();
		Equation simplified = eq.simplified();

		function = new Surface(simplified, LatexRenderer.toImage(latex), true);

		try {
			Equation xDer = simplified.derivative('x');
			latex = "z_x = " + xDer.toLatex();
			xDerivative = new Surface(xDer, LatexRenderer.toImage(latex), false);
		} catch (Exception e) {
			e.printStackTrace();
			xDerivative = null;
		}

		try {
			Equation yDer = simplified.derivative('y');
			latex = "z_y = " + yDer.toLatex();
			yDerivative = new Surface(yDer, LatexRenderer.toImage(latex), false);
		} catch (Exception e) {
			e.printStackTrace();
			yDerivative = null;
		}

	}

	/**
	 * update the surfaces
	 * 
	 * @param grid      - coordinate system to render according to
	 * @param varValues - value of all the parameters
	 */
	public void update(Grid grid, HashMap<Character, Double> varValues) {
		function.update(grid, varValues);
		if (xDerivative != null)
			xDerivative.update(grid, varValues);
		if (yDerivative != null)
			yDerivative.update(grid, varValues);
	}

	/**
	 * @return the function
	 */
	public Surface getFunction() {
		return function;
	}

	/**
	 * @return the xDerivative
	 */
	public Surface getxDerivative() {
		return xDerivative;
	}

	/**
	 * @return the yDerivative
	 */
	public Surface getyDerivative() {
		return yDerivative;
	}

	/**
	 * cleanup the GPU memory when not needed anymore
	 */
	public void cleanup() {
		function.cleanup();
		if (xDerivative != null)
			xDerivative.cleanup();
		if (yDerivative != null)
			yDerivative.cleanup();
	}
}