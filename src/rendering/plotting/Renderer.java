package rendering.plotting;

import static org.lwjgl.glfw.GLFW.glfwGetTime;
import static org.lwjgl.opengl.GL11.GL_BLEND;
import static org.lwjgl.opengl.GL11.GL_COLOR_BUFFER_BIT;
import static org.lwjgl.opengl.GL11.GL_DEPTH_BUFFER_BIT;
import static org.lwjgl.opengl.GL11.GL_LINE_SMOOTH;
import static org.lwjgl.opengl.GL11.GL_ONE_MINUS_SRC_ALPHA;
import static org.lwjgl.opengl.GL11.GL_SRC_ALPHA;
import static org.lwjgl.opengl.GL11.glBlendFunc;
import static org.lwjgl.opengl.GL11.glClear;
import static org.lwjgl.opengl.GL11.glClearColor;
import static org.lwjgl.opengl.GL11.glEnable;
import static org.lwjgl.opengl.GL13.GL_MULTISAMPLE;

import org.lwjgl.Version;

import rendering.GUI.GUIRenderer;

public class Renderer {

	public Renderer() {
		System.out.println("Hello LWJGL " + Version.getVersion() + "!");
		Display.initialize();
		GUIRenderer.initialize();
		start();
	}

	public void start() {
		// Set the clear color
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

		// Run the rendering loop until the user has attempted to close the window
		double time = 0;
		while (!Display.isCloseRequested()) {
			final double currentTime = glfwGetTime();
			final double deltaTime = (time > 0) ? (currentTime - time) : 1f / 60f;
			time = currentTime;
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the framebuffer
			
			//////
			
			//////
			
			GUIRenderer.render(deltaTime);

			Display.update();
		}
		GUIRenderer.destroy();
		Display.destroy();
	}

}
