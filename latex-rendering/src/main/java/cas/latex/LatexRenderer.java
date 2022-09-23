package cas.latex;

import java.awt.Color;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import javax.imageio.ImageIO;
import org.scilab.forge.jlatexmath.TeXConstants;
import org.scilab.forge.jlatexmath.TeXFormula;

public class LatexRenderer {
    public static int textSize = 30; // the size of the LaTeX text

    public static void render(String latex, String fileName) throws IOException {
        TeXFormula formula = new TeXFormula(latex);
        Image image = formula.createBufferedImage(TeXConstants.STYLE_DISPLAY, textSize, Color.WHITE, Color.BLACK);
        BufferedImage bufferedImage = (BufferedImage) image;
        ImageIO.write(bufferedImage, "png", new File("../res/" + fileName + ".png"));
    }

    public static void main(String[] args) throws IOException {
        String fileName = args[args.length - 1];
        StringBuilder latex = new StringBuilder(args[0]);
        for (int i = 1; i < args.length - 1; i++) {
            latex.append(" ").append(args[i]);
        }

        String latexStr = latex.toString();
        System.out.println("[JAVA]: Inputs " + Arrays.toString(args));
        System.out.println("[JAVA]: Rendering latex " + latexStr);
        System.out.println("[JAVA]: Saving to " + fileName + ".png in ../res/");

        render(latexStr, fileName);
    }
}
