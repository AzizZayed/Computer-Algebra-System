package rendering.latex;

import javax.swing.JOptionPane;

import org.scilab.forge.jlatexmath.TeXConstants;
import org.scilab.forge.jlatexmath.TeXFormula;
import org.scilab.forge.jlatexmath.TeXIcon;

import math.structure.IMath;

/**
 * class to render expressions and equations in latex
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class LatexRenderer {

	public static TeXIcon render(IMath math) {
		String latex = math.toLatex();

		TeXFormula formula = new TeXFormula(latex);
		TeXIcon icon = formula.createTeXIcon(TeXConstants.STYLE_DISPLAY, 20);
		JOptionPane.showMessageDialog(null, "", "LaTeX", JOptionPane.PLAIN_MESSAGE, icon);

		return icon;
	}
}