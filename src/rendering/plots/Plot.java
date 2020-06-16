package rendering.plots;

import static org.lwjgl.opengl.GL15.glDeleteBuffers;
import static org.lwjgl.opengl.GL15.glGenBuffers;

import java.awt.image.BufferedImage;
import java.util.HashMap;

import math.structure.Equation;
import net.jafama.FastMath;
import rendering.GUI.Texture;
import rendering.tools.Grid;

/**
 * This class represents a plot and all the data common between all types of
 * plots
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class Plot {

	protected Equation equation; // the function of the plot
	protected float[] color; // the color of the plot
	private Texture texture; // the texture for the equation of the plot
	protected boolean visible; // if the plot is visible
	protected int vbo; // the GPU buffer to carry the data

	public Plot(Equation eq, BufferedImage image, boolean visible) {
		equation = eq;
		color = new float[] { (float) FastMath.random(), (float) FastMath.random(), (float) FastMath.random(), 1f };
		texture = new Texture(image);
		this.visible = visible;
		vbo = glGenBuffers();

//		glBindBuffer(GL_ARRAY_BUFFER, vbo);
//		glBufferData(GL_ARRAY_BUFFER, size * 4, GL_DYNAMIC_DRAW);
//		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

	/**
	 * @return the visible
	 */
	public boolean isVisible() {
		return visible;
	}

	/**
	 * @param visible the visible to set
	 */
	public void setVisible(boolean visible) {
		this.visible = visible;
	}

	/**
	 * @return the function
	 */
	public Equation getEquation() {
		return equation;
	}

	/**
	 * @return the color
	 */
	public float[] getColor() {
		return color;
	}

	/**
	 * @return the texture
	 */
	public Texture getTexture() {
		return texture;
	}

	/**
	 * cleanup the memory allocated by OpenGL
	 */
	public void cleanup() {
		glDeleteBuffers(vbo);
		texture.cleanup();
	}

	/**
	 * render the plot
	 */
	protected abstract void render();

	/**
	 * update the date for the plot
	 * 
	 * @param grid      - The coordinates system to generate data from
	 * @param varValues - the parameter values
	 */
	public abstract void update(Grid grid, HashMap<Character, Double> varValues);
}
