package rendering.core;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL15.*;

import java.util.ArrayList;
import java.util.HashMap;

import net.jafama.FastMath;
import rendering.GUI.GUIRenderer;
import rendering.plots.CurvePair;
import rendering.plots.SurfaceTrio;
import rendering.tools.Grid;

/**
 * This is the core of the application, where everything meets. This class is in
 * charge of rendering everything.
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Renderer {

	/*
	 * properties for perspective view
	 */
	private static final double FOV = 60d, ASPECT = 1d, NEAR_PLANE = 11d, FAR_PLANE = 26d;

	private static Mode mode = Mode.RENDER_3D;

	/**
	 * the rendering mode, 3D or 2D
	 * 
	 * @author Abd-El-Aziz Zayed
	 *
	 */
	private enum Mode {
		RENDER_2D, RENDER_3D;
	}

	public Renderer() {
		Display.initialize();
		start();
		Display.destroy();
	}

	/**
	 * switch between 2D and 3D
	 */
	public static void switchMode() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		switch (mode) {
		case RENDER_2D:
			mode = Mode.RENDER_3D;
			perspective(FOV, ASPECT, NEAR_PLANE, FAR_PLANE);
			break;
		case RENDER_3D:
			mode = Mode.RENDER_2D;
			glOrtho(0, 1, 0, 1, -1, 1);
			break;
		}
		glMatrixMode(GL_MODELVIEW);
	}

	/**
	 * start the rendering and the main loop
	 */
	public void start() {

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		perspective(FOV, ASPECT, NEAR_PLANE, FAR_PLANE);
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_MULTISAMPLE);

//		glEnable(GL_LINE_SMOOTH);
//		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glLineWidth(3f);
		glEnable(GL_ALPHA_TEST);

		

		ArrayList<CurvePair> curves = new ArrayList<>();
		ArrayList<SurfaceTrio> surfaces = new ArrayList<>();
		HashMap<Character, Double> varValues = new HashMap<>();

		Grid grid2D = new Grid(-1d, 1d, -1d, 1d, 0d, 0d);
		Grid grid3D = new Grid(-1d, 1d, -1d, 1d, -1d, 1d);

		GUIRenderer gui = GUIRenderer.getContext();

		gui.initialize();

		// Run the rendering loop until the user has attempted to close the window
		double time = 0;
		while (!Display.isCloseRequested()) {
			double currentTime = Display.getTime();
			double deltaTime = (time > 0) ? (currentTime - time) : 1f / 60f;
			time = currentTime;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the framebuffer

			glPushMatrix();
			if (mode == Mode.RENDER_3D) {
				input3D(gui, grid3D);
				render3D(surfaces, grid3D, varValues);
				gui.render3D(deltaTime, surfaces, varValues);
			} else {
				input2D(gui, grid2D);
				render2D(curves, grid2D, varValues);
				gui.render2D(deltaTime, curves, varValues);
			}
			glPopMatrix();

			double dt = Display.getTime() - time;
			System.out.println("Frame Time: " + dt + " s");
			System.out.println("FPS: " + 1d / dt);
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
		glTranslatef(0.0f, 0.0f, -18.0f);
		glRotatef(-75f, 1f, 0f, 0f);

		glRotated(grid.getXRotation(), 1d, 0d, 0d);
		glRotated(grid.getZRotation(), 0d, 0d, 1d);

		float scale = 8.0f;
		glScaled(scale / grid.getX().getLength(), scale / grid.getY().getLength(), scale / grid.getZ().getLength());
	}

	private void transform2D(Grid grid) {
		glScaled(1.0d / grid.getX().getLength(), 1.0d / grid.getY().getLength(), 1.0d);
		glTranslated(-grid.getXMin(), -grid.getYMin(), 0.0d);
	}

	private void input2D(GUIRenderer gui, Grid grid) {
		grid.drag(gui.getDragX(), gui.getDragY());
		grid.zoom(gui.getMouseScroll());
	}

	private void input3D(GUIRenderer gui, Grid grid) {
		grid.rotate(gui.getDragY(), gui.getDragX());
		grid.zoom(gui.getMouseScroll());
	}

	/**
	 * Generate perspective view. Took this from the description here:
	 * https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml
	 * 
	 * @param fovy   - field of view angle, in degrees, in the y direction.
	 * @param aspect - aspect ratio of window
	 * @param zNear  -distance from the viewer to the near clipping plane
	 * @param zFar   - distance from the viewer to the far clipping plane
	 */
	private static void perspective(double fovy, double aspect, double zNear, double zFar) {
		double f = 1.0 / FastMath.tan(fovy * Math.PI / 360);
		double transformation[] = { //
				f / aspect, 0, 0, 0, //
				0, f, 0, 0, //
				0, 0, (zFar + zNear) / (zNear - zFar), -1, //
				0, 0, 2 * zFar * zNear / (zNear - zFar), 0 //
		};
		glMultMatrixd(transformation);
	}

}