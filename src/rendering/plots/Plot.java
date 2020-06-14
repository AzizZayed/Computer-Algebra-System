package rendering.plots;

import static org.lwjgl.opengl.GL15.glDeleteBuffers;
import static org.lwjgl.opengl.GL15.glGenBuffers;

import java.awt.image.BufferedImage;
import java.util.HashMap;

import math.structure.Equation;
import net.jafama.FastMath;
import rendering.GUI.Texture;
import rendering.tools.Grid;

public abstract class Plot {

	protected Equation function;
	protected float[] color;
	private Texture texture;
	protected boolean visible;
	protected int vbo;

	public Plot(Equation eq, BufferedImage image) {
		function = eq;
		color = new float[] { (float) FastMath.random(), (float) FastMath.random(), (float) FastMath.random(), 1f };
		texture = new Texture(image);
		visible = true;
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
	public Equation getFunction() {
		return function;
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
