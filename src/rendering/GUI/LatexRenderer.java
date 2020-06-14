package rendering.GUI;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

import org.scilab.forge.jlatexmath.TeXConstants;
import org.scilab.forge.jlatexmath.TeXFormula;
import org.scilab.forge.jlatexmath.TeXIcon;

/**
 * class to render expressions and equations in latex
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class LatexRenderer {

	public static int textSize = 30; // the size of the LaTeX text

	/**
	 * render the latex text to a TeXIcon
	 * 
	 * @param latex - the latex to render
	 * @return the TeXIcon
	 */
	public static TeXIcon render(String latex) {
		return new TeXFormula(latex).createTeXIcon(TeXConstants.STYLE_DISPLAY, textSize);
	}

	/**
	 * create a buffered image from the given latex string
	 * 
	 * @param latex - the latex to render
	 * @return the image
	 */
	public static BufferedImage toImage(String latex) {
		TeXIcon icon = render(latex);
		BufferedImage image = new BufferedImage(icon.getIconWidth(), icon.getIconHeight(), BufferedImage.TYPE_INT_ARGB);
		Graphics2D g = image.createGraphics();
		icon.setForeground(Color.WHITE);
		icon.paintIcon(null, g, 0, 0);
		g.dispose();
		return image;
	}
}