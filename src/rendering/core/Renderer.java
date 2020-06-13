package rendering.core;

import static org.lwjgl.glfw.GLFW.glfwGetTime;
import static org.lwjgl.opengl.GL11.GL_ALPHA_TEST;
import static org.lwjgl.opengl.GL11.GL_BLEND;
import static org.lwjgl.opengl.GL11.GL_COLOR_BUFFER_BIT;
import static org.lwjgl.opengl.GL11.GL_DEPTH_BUFFER_BIT;
import static org.lwjgl.opengl.GL11.GL_DEPTH_TEST;
import static org.lwjgl.opengl.GL11.GL_LINE_SMOOTH;
import static org.lwjgl.opengl.GL11.GL_LINE_SMOOTH_HINT;
import static org.lwjgl.opengl.GL11.GL_MODELVIEW;
import static org.lwjgl.opengl.GL11.GL_NICEST;
import static org.lwjgl.opengl.GL11.GL_ONE_MINUS_SRC_ALPHA;
import static org.lwjgl.opengl.GL11.GL_SCISSOR_TEST;
import static org.lwjgl.opengl.GL11.GL_SRC_ALPHA;
import static org.lwjgl.opengl.GL11.glBlendFunc;
import static org.lwjgl.opengl.GL11.glClear;
import static org.lwjgl.opengl.GL11.glClearColor;
import static org.lwjgl.opengl.GL11.glEnable;
import static org.lwjgl.opengl.GL11.glHint;
import static org.lwjgl.opengl.GL11.glLineWidth;
import static org.lwjgl.opengl.GL11.glLoadIdentity;
import static org.lwjgl.opengl.GL11.glMatrixMode;
import static org.lwjgl.opengl.GL11.glPopMatrix;
import static org.lwjgl.opengl.GL11.glPushMatrix;
import static org.lwjgl.opengl.GL11.glScaled;
import static org.lwjgl.opengl.GL11.glTranslated;
import static org.lwjgl.opengl.GL13.GL_MULTISAMPLE;

import java.util.ArrayList;
import java.util.HashMap;

import org.lwjgl.Version;

import rendering.GUI.GUIRenderer;
import rendering.plots.CurvePair;
import rendering.tools.Grid;

public class Renderer {

	public Renderer() {
		System.out.println("Hello LWJGL " + Version.getVersion() + "!");
		Display.initialize();
		start();
		Display.destroy();
	}

	public void start() {

		Grid grid = new Grid(-1d, 1d, -1d, 1d, -1d, 1d);
		ArrayList<CurvePair> curves = new ArrayList<>();
		HashMap<Character, Double> varValues = new HashMap<>();
		GUIRenderer gui = GUIRenderer.getContext();

		gui.initialize();

		// Set the clear color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_SCISSOR_TEST);
		glEnable(GL_ALPHA_TEST);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glLineWidth(3f);

		// Run the rendering loop until the user has attempted to close the window
		double time = 0;
		while (!Display.isCloseRequested()) {
			final double currentTime = glfwGetTime();
			final double deltaTime = (time > 0) ? (currentTime - time) : 1f / 60f;
			time = currentTime;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the framebuffer

			/*
			 * handle input
			 */
			input(gui, grid);

			/*
			 * rendering
			 */
			render(curves, grid, varValues);
			gui.render(deltaTime, curves, varValues);

			Display.update();
		}
		gui.destroy();
		for (CurvePair pair : curves)
			pair.cleanup();
	}

	private void render(ArrayList<CurvePair> curves, Grid grid, HashMap<Character, Double> varValues) {
		glPushMatrix();

		transform(grid);

		/// Render Curves ///
		for (CurvePair pair : curves)
			pair.update(grid, varValues);

		glPopMatrix();
	}

	private void transform(Grid grid) {
		glScaled(1.0d / grid.getX().getLength(), 1.0d / grid.getY().getLength(), 1.0d);
		glTranslated(-grid.getXMin(), -grid.getYMin(), 0.0d);
	}

	private void input(GUIRenderer gui, Grid grid) {
		grid.drag(gui.getDragX(), gui.getDragY());
		grid.zoom(gui.getMouseScroll());
	}
}