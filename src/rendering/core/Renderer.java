package rendering.core;

import static org.lwjgl.glfw.GLFW.glfwGetTime;
import static org.lwjgl.opengl.GL11.GL_ALPHA_TEST;
import static org.lwjgl.opengl.GL11.GL_BLEND;
import static org.lwjgl.opengl.GL11.GL_COLOR_BUFFER_BIT;
import static org.lwjgl.opengl.GL11.GL_DEPTH_BUFFER_BIT;
import static org.lwjgl.opengl.GL11.GL_DEPTH_TEST;
import static org.lwjgl.opengl.GL11.GL_LEQUAL;
import static org.lwjgl.opengl.GL11.GL_MODELVIEW;
import static org.lwjgl.opengl.GL11.GL_ONE_MINUS_SRC_ALPHA;
import static org.lwjgl.opengl.GL11.GL_PROJECTION;
import static org.lwjgl.opengl.GL11.GL_SRC_ALPHA;
import static org.lwjgl.opengl.GL11.glBlendFunc;
import static org.lwjgl.opengl.GL11.glClear;
import static org.lwjgl.opengl.GL11.glClearColor;
import static org.lwjgl.opengl.GL11.glDepthFunc;
import static org.lwjgl.opengl.GL11.glDepthMask;
import static org.lwjgl.opengl.GL11.glEnable;
import static org.lwjgl.opengl.GL11.glLineWidth;
import static org.lwjgl.opengl.GL11.glLoadIdentity;
import static org.lwjgl.opengl.GL11.glMatrixMode;
import static org.lwjgl.opengl.GL11.glOrtho;
import static org.lwjgl.opengl.GL11.glPopMatrix;
import static org.lwjgl.opengl.GL11.glPushMatrix;
import static org.lwjgl.opengl.GL11.glRotated;
import static org.lwjgl.opengl.GL11.glRotatef;
import static org.lwjgl.opengl.GL11.glScaled;
import static org.lwjgl.opengl.GL11.glTranslated;
import static org.lwjgl.opengl.GL11.glTranslatef;
import static org.lwjgl.opengl.GL13.GL_MULTISAMPLE;

import java.util.ArrayList;
import java.util.HashMap;

import org.lwjgl.Version;
import org.lwjgl.opengl.GL11;

import rendering.GUI.GUIRenderer;
import rendering.plots.CurvePair;
import rendering.plots.SurfaceTrio;
import rendering.tools.Grid;

public class Renderer {

	private static Mode mode = Mode.RENDER_3D;
	private static Grid grid = new Grid(-1d, 1d, -1d, 1d, -1d, 1d);

	private enum Mode {
		RENDER_2D, RENDER_3D;
	}

	public Renderer() {
		System.out.println("Hello LWJGL " + Version.getVersion() + "!");
		Display.initialize();
		start();
		Display.destroy();
	}

	public static void switchMode() {
		switch (mode) {
		case RENDER_2D:
			
			glMatrixMode(GL11.GL_PROJECTION);
			glLoadIdentity();
			
			mode = Mode.RENDER_3D;
			Display.perspective(45.0d, 1d, 0.001d, 100.0d);
			glMatrixMode(GL_MODELVIEW);
			
			grid = new Grid(-1d, 1d, -1d, 1d, -1d, 1d);
			
			break;
			
		case RENDER_3D:

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			
			mode = Mode.RENDER_2D;
			glOrtho(0, 1, 0, 1, -1, 1);
			glMatrixMode(GL_MODELVIEW);
			
			grid = new Grid(-1d, 1d, -1d, 1d, -1d, 1d);
			
			break;
			
		default:
			break;
		}
	}

	public void start() {

		ArrayList<CurvePair> curves = new ArrayList<>();
		ArrayList<SurfaceTrio> surfaces = new ArrayList<>();
		HashMap<Character, Double> varValues = new HashMap<>();
		GUIRenderer gui = GUIRenderer.getContext();

		gui.initialize();

		// Set the clear color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_MULTISAMPLE);

//		glEnable(GL_LINE_SMOOTH);
//		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_ALPHA_TEST);
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
			glPushMatrix();
			if (mode == Mode.RENDER_3D) {
				render3D(surfaces, grid, varValues);
				gui.render3D(deltaTime, surfaces, varValues);
			} else {
				render2D(curves, grid, varValues);
				gui.render2D(deltaTime, curves, varValues);
			}
			glPopMatrix();

			Display.update();
		}
		gui.destroy();
		for (CurvePair pair : curves)
			pair.cleanup();
		for (SurfaceTrio trio : surfaces)
			trio.cleanup();
	}

	private void render3D(ArrayList<SurfaceTrio> surfaces, Grid grid, HashMap<Character, Double> varValues) {
		transform3D(grid);

		grid.render();

		/// Render surfaces ///
		glDepthMask(false);
		for (SurfaceTrio trio : surfaces)
			trio.update(grid, varValues);
		glDepthMask(true);
	}

	private void render2D(ArrayList<CurvePair> curves, Grid grid, HashMap<Character, Double> varValues) {
		transform2D(grid);

		grid.render();

		/// Render Curves ///
		for (CurvePair pair : curves)
			pair.update(grid, varValues);
	}

	private void transform3D(Grid grid) {
		glTranslatef(0.0f, -2.0f, -18.0f);
		glRotatef(-75f, 1f, 0f, 0f);

		glRotated(grid.getxRotation(), 1d, 0d, 0d);
		glRotated(grid.getyRotation(), 0d, 0d, 1d);

		float scale = 8.0f;
		glScaled(scale / grid.getX().getLength(), scale / grid.getY().getLength(), scale / grid.getZ().getLength());
	}

	private void transform2D(Grid grid) {
		glScaled(1.0d / grid.getX().getLength(), 1.0d / grid.getY().getLength(), 1.0d);
		glTranslated(-grid.getXMin(), -grid.getYMin(), 0.0d);
	}

	private void input(GUIRenderer gui, Grid grid) {
		if (mode == Mode.RENDER_3D) {
			grid.rotate(-gui.getDragY(), gui.getDragX());
		} else
			grid.drag(gui.getDragX(), gui.getDragY());
		grid.zoom(gui.getMouseScroll());
	}
}