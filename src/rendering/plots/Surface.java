package rendering.plots;

import static org.lwjgl.opengl.GL11.GL_FLOAT;
import static org.lwjgl.opengl.GL11.GL_QUAD_STRIP;
import static org.lwjgl.opengl.GL11.GL_TRIANGLE_STRIP;
import static org.lwjgl.opengl.GL11.GL_VERTEX_ARRAY;
import static org.lwjgl.opengl.GL11.glColor4d;
import static org.lwjgl.opengl.GL11.glColor4f;
import static org.lwjgl.opengl.GL11.glDisableClientState;
import static org.lwjgl.opengl.GL11.glDrawArrays;
import static org.lwjgl.opengl.GL11.glEnableClientState;
import static org.lwjgl.opengl.GL11.glVertexPointer;
import static org.lwjgl.opengl.GL15.GL_ARRAY_BUFFER;
import static org.lwjgl.opengl.GL15.GL_STATIC_DRAW;
import static org.lwjgl.opengl.GL15.glBindBuffer;
import static org.lwjgl.opengl.GL15.glBufferData;

import java.awt.image.BufferedImage;
import java.nio.FloatBuffer;
import java.util.HashMap;

import org.lwjgl.BufferUtils;

import math.structure.Equation;
import rendering.tools.Grid;

/**
 * This class represents a surface: 3 dimensional function with z dependent on x
 * and y
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Surface extends Plot {

	public static final int MAX_RESOLUTION = 100; // the resolution of the mesh

	/*
	 * the number of floats needed to represent the data (size) and the buffer to
	 * store the data
	 */
	private static int size = (MAX_RESOLUTION + 1) * MAX_RESOLUTION * 6;
	private static FloatBuffer buffer = BufferUtils.createFloatBuffer(size);

	private boolean drawWire = false; // if we draw the wireframe

	public Surface(Equation eq, BufferedImage image) {
		super(eq, image);
		color[3] = .5f;
	}

	@Override
	public void update(Grid grid, HashMap<Character, Double> varValues) {
		if (!visible)
			return;

		double dx, dy;
		double xmin = grid.getX().getMin();
		double ymin = grid.getY().getMin();

		dx = grid.getX().getLength() / MAX_RESOLUTION;
		dy = grid.getY().getLength() / MAX_RESOLUTION;

		int i, j;
		double x, y;
		for (y = ymin, j = 0; j < MAX_RESOLUTION; j++, y += dy) {
			for (x = xmin, i = 0; i <= MAX_RESOLUTION; i++, x += dx) {
				double z = eval(x, y, varValues);

//				Range zRange = grid.getZ();
//				if (!zRange.inRange(eval(x - dx, y - dy)) && !zRange.inRange(eval(x - dx, y + dy))
//						&& !zRange.inRange(z) && !zRange.inRange(eval(x + dx, y + dy))
//						&& !zRange.inRange(eval(x + dx, y - dy)))
//					z = Float.NaN;

				buffer.put((float) x);
				buffer.put((float) y);
				buffer.put((float) z);

				double yNext = y + dy;

				buffer.put((float) x);
				buffer.put((float) yNext);
				buffer.put((float) eval(x, yNext, varValues));
			}
		}
		buffer.flip();

		render();
	}

	@Override
	protected void render() {
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, buffer, GL_STATIC_DRAW);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, buffer);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glColor4d(color[0], color[1], color[2], color[3]);

		int count = MAX_RESOLUTION * 2;
		for (int i = 0; i < MAX_RESOLUTION; i++) {
			glDrawArrays(GL_TRIANGLE_STRIP, count * i + 2 * i, count);
		}

		if (drawWire) {
			glColor4f(1 - color[0], 1 - color[1], 1 - color[2], 0.7f);

//			glPolygonMode(GL_FRONT, GL_LINE);
			int step = MAX_RESOLUTION / 5;
			for (int i = step; i < MAX_RESOLUTION; i += step) {
				glDrawArrays(GL_QUAD_STRIP, (count + 2) * i, count);
			}
//			glPolygonMode(GL_FRONT, GL_FILL);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	/**
	 * evaluate the value of the function at the following values
	 * 
	 * @param x         - value of x
	 * @param y         - value of y
	 * @param varValues - value for all parameters
	 * @return the value of z, or the evaluation of the function at the given values
	 */
	private double eval(double x, double y, HashMap<Character, Double> varValues) {
		varValues.put('x', x);
		varValues.put('y', y);
		return equation.valueAt(varValues);
	}
}