package rendering.GUI;

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

	public static int textSize = 25;

	public static TeXIcon render(IMath math) {
		return new TeXFormula(math.toLatex()).createTeXIcon(TeXConstants.STYLE_DISPLAY, textSize);
	}

	public static TeXIcon render(String latex) {
		return new TeXFormula(latex).createTeXIcon(TeXConstants.STYLE_DISPLAY, textSize);
	}

	public static BufferedImage toImage(IMath math) {
		TeXIcon icon = render(math);
		BufferedImage image = new BufferedImage(icon.getIconWidth(), icon.getIconHeight(), BufferedImage.TYPE_INT_ARGB);
		Graphics2D g2 = image.createGraphics();
		icon.paintIcon(null, g2, 0, 0);
		g2.dispose();
		return image;
	}

	public static BufferedImage toImage(String latex) {
		TeXIcon icon = render(latex);
		BufferedImage image = new BufferedImage(icon.getIconWidth(), icon.getIconHeight(), BufferedImage.TYPE_INT_ARGB);
		Graphics2D g2 = image.createGraphics();
		icon.paintIcon(null, g2, 0, 0);
		g2.dispose();
		return image;
	}
}