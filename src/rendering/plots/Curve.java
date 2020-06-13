package rendering.plots;

import static org.lwjgl.opengl.GL11.GL_FLOAT;
import static org.lwjgl.opengl.GL11.GL_LINE_STRIP;
import static org.lwjgl.opengl.GL11.GL_VERTEX_ARRAY;
import static org.lwjgl.opengl.GL11.glColor4d;
import static org.lwjgl.opengl.GL11.glDisableClientState;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL11.glEnableClientState;
import static org.lwjgl.opengl.GL11.glVertexPointer;
import static org.lwjgl.opengl.GL15.GL_ARRAY_BUFFER;
import static org.lwjgl.opengl.GL15.GL_STATIC_DRAW;
import static org.lwjgl.opengl.GL15.glBindBuffer;
import static org.lwjgl.opengl.GL15.glBufferData;
import static org.lwjgl.opengl.GL15.glDeleteBuffers;
import static org.lwjgl.opengl.GL15.glGenBuffers;

import java.awt.image.BufferedImage;
import java.nio.FloatBuffer;
import java.util.HashMap;

import org.lwjgl.BufferUtils;

import math.structure.Equation;
import rendering.GUI.Texture;
import rendering.tools.Grid;

public class Curve {

	public static final int MAX_RESOLUTION = 10000;

	private static int size = MAX_RESOLUTION * 2;
	private static FloatBuffer buffer = BufferUtils.createFloatBuffer(size);

	private Equation function;
	private float[] color;
	private Texture texture;
	private boolean visible;
	private int vbo;

	public Curve(Equation eq, float[] color, BufferedImage image) {
		function = eq;
		this.color = color;
		texture = new Texture(image);
		visible = true;
		vbo = glGenBuffers();
//		glBindBuffer(GL_ARRAY_BUFFER, vbo);
//		glBufferData(GL_ARRAY_BUFFER, MAX_RESOLUTION * 8, GL_DYNAMIC_DRAW);
//		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

	public void update(Grid grid, HashMap<Character, Double> varValues) {
		if (!visible)
			return;

//			buffer.clear();

		double dx = grid.getX().getLength() / MAX_RESOLUTION;
		double xmin = grid.getXMin();

		int i;
		double x;
		for (i = 0, x = xmin; i < size /* && x <= xmax */; i += 2, x += dx) {
			double y = eval(x, varValues);

//				Range yRange = grid.getY();
//				if (!yRange.inRange(eval(x - dx, varValues)) && !yRange.inRange(y)
//						&& !yRange.inRange(eval(x + dx, varValues)))
//					y = Float.NaN;

			buffer.put((float) x);
			buffer.put((float) y);
		}
		buffer.flip();

		render();
	}

	private void render() {
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, buffer, GL_STATIC_DRAW);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, buffer);
		glVertexPointer(2, GL_FLOAT, 0, 0);

		glColor4d(color[0], color[1], color[2], color[3]);
		glDrawArrays(GL_LINE_STRIP, 0, MAX_RESOLUTION);

//		glDrawArrays(GL_LINES, 0, MAX_RESOLUTION);
//		glDrawArrays(GL_LINES, 1, MAX_RESOLUTION - 1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	private double eval(double x, HashMap<Character, Double> varValues) {
		varValues.put('x', x);
		return function.valueAt(varValues);
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

	public void cleanup() {
		glDeleteBuffers(vbo);
		texture.cleanup();
	}

}
