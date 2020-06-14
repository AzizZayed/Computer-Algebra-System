package rendering.core;

import static org.lwjgl.glfw.Callbacks.glfwFreeCallbacks;
import static org.lwjgl.glfw.GLFW.GLFW_FALSE;
import static org.lwjgl.glfw.GLFW.GLFW_KEY_ESCAPE;
import static org.lwjgl.glfw.GLFW.GLFW_RELEASE;
import static org.lwjgl.glfw.GLFW.GLFW_RESIZABLE;
import static org.lwjgl.glfw.GLFW.GLFW_SAMPLES;
import static org.lwjgl.glfw.GLFW.GLFW_TRUE;
import static org.lwjgl.glfw.GLFW.GLFW_VISIBLE;
import static org.lwjgl.glfw.GLFW.glfwCreateWindow;
import static org.lwjgl.glfw.GLFW.glfwDefaultWindowHints;
import static org.lwjgl.glfw.GLFW.glfwDestroyWindow;
import static org.lwjgl.glfw.GLFW.glfwGetTime;
import static org.lwjgl.glfw.GLFW.glfwInit;
import static org.lwjgl.glfw.GLFW.glfwMakeContextCurrent;
import static org.lwjgl.glfw.GLFW.glfwPollEvents;
import static org.lwjgl.glfw.GLFW.glfwSetErrorCallback;
import static org.lwjgl.glfw.GLFW.glfwSetKeyCallback;
import static org.lwjgl.glfw.GLFW.glfwSetWindowShouldClose;
import static org.lwjgl.glfw.GLFW.glfwShowWindow;
import static org.lwjgl.glfw.GLFW.glfwSwapBuffers;
import static org.lwjgl.glfw.GLFW.glfwSwapInterval;
import static org.lwjgl.glfw.GLFW.glfwTerminate;
import static org.lwjgl.glfw.GLFW.glfwWindowHint;
import static org.lwjgl.glfw.GLFW.glfwWindowShouldClose;
import static org.lwjgl.opengl.GL11.glViewport;

import org.lwjgl.glfw.GLFWErrorCallback;
import org.lwjgl.opengl.GL;
import org.lwjgl.system.MemoryUtil;

/**
 * class to handle the GLFW window. Code from https://www.lwjgl.org/guide
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public final class Display {

	public static long ID; // the id of the window
	public static int xViewport = 400, yViewport = 0; // position of the viewport
	public static int width = 1000 + xViewport, height = 1000 + yViewport; // dimensions of the display

	/**
	 * initialize the window and show it
	 */
	public static void initialize() {
		GLFWErrorCallback.createPrint(System.err).set();

		if (!glfwInit())
			throw new IllegalStateException("Unable to initialize GLFW");

		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_SAMPLES, 16); // multi-sampling and anti-aliasing enabled

		// create the window for OpenGL
		ID = glfwCreateWindow(width, height, "Hello World!", MemoryUtil.NULL, MemoryUtil.NULL);
		if (ID == MemoryUtil.NULL)
			throw new RuntimeException("Failed to create the GLFW window");

		// setup keys
		glfwSetKeyCallback(ID, (window, key, scancode, action, mods) -> {
			if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
				glfwSetWindowShouldClose(window, true); // We will detect this in the rendering loop
		});

		glfwMakeContextCurrent(ID); // create context
		glfwSwapInterval(GLFW_TRUE); // enable v-sync
		glfwShowWindow(ID); // window visible

		GL.createCapabilities(); // make OpenGL bindings available

		glViewport(xViewport, yViewport, width - xViewport, height - yViewport);
	}

	/**
	 * @return the time since this display was initialized
	 */
	public static double getTime() {
		return glfwGetTime();
	}

	/**
	 * update the display every frame
	 */
	public static void update() {
		glfwSwapBuffers(ID); // swap the color buffers
		glfwPollEvents();
	}

	/**
	 * destroy the display when done
	 */
	public static void destroy() {
		// Free the window callbacks and destroy the window
		glfwFreeCallbacks(ID);
		glfwDestroyWindow(ID);

		// Terminate GLFW and free the error callback
		glfwTerminate();
		glfwSetErrorCallback(null).free();
	}

	/**
	 * @return if the user closed the display
	 */
	public static boolean isCloseRequested() {
		return glfwWindowShouldClose(ID);
	}
}