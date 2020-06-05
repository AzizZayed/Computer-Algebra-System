package rendering.GUI;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

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
		latex = "y=" + latex;

		TeXFormula formula = new TeXFormula(latex);
		TeXIcon icon = formula.createTeXIcon(TeXConstants.STYLE_DISPLAY, 20);
//		JOptionPane.showMessageDialog(null, "", "LaTeX", JOptionPane.PLAIN_MESSAGE, icon);
//		icon.setForeground(Color.RED);

		return icon;
	}

	public static BufferedImage toImage(IMath math) {
		TeXIcon icon = render(math);
		int w = icon.getIconWidth(), h = icon.getIconHeight();
		BufferedImage image = new BufferedImage(w, h, BufferedImage.TYPE_INT_ARGB);
		Graphics2D g2 = image.createGraphics();
//		icon.setForeground(Color.WHITE);
		icon.paintIcon(null, g2, 0, 0);
		g2.dispose();
		return image;
	}
}