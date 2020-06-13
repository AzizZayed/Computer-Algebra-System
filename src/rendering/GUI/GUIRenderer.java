package rendering.GUI;

import static org.lwjgl.glfw.GLFW.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;

import imgui.ImBool;
import imgui.ImDouble;
import imgui.ImFloat;
import imgui.ImGui;
import imgui.ImGuiIO;
import imgui.ImGuiStyle;
import imgui.ImString;
import imgui.ImVec2;
import imgui.callbacks.ImStrConsumer;
import imgui.callbacks.ImStrSupplier;
import imgui.enums.ImGuiBackendFlags;
import imgui.enums.ImGuiColorEditFlags;
import imgui.enums.ImGuiCond;
import imgui.enums.ImGuiConfigFlags;
import imgui.enums.ImGuiDataType;
import imgui.enums.ImGuiKey;
import imgui.enums.ImGuiMouseButton;
import imgui.enums.ImGuiMouseCursor;
import imgui.enums.ImGuiTreeNodeFlags;
import imgui.enums.ImGuiWindowFlags;
import imgui.gl3.ImGuiImplGl3;
import math.structure.Equation;
import rendering.data.Curve;
import rendering.data.GraphableEquation;
import rendering.data.Texture;
import rendering.plotting.Display;

/**
 * class to render ImGui using the java bindings. Most of the setup code is
 * taken from the example here:
 * https://github.com/SpaiR/imgui-java/tree/master/imgui-lwjgl3/src/test/java
 * 
 * Since ImGui has no documentation, I used the demo file to find the functions
 * I need: https://github.com/ocornut/imgui/blob/master/imgui_demo.cpp
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class GUIRenderer {

	private final long[] mouseCursors = new long[ImGuiMouseCursor.COUNT]; // Mouse cursors provided by GLFW
	private ImString strFunction = new ImString("a*x^2", 500); // string object to record input

	private final ImGuiImplGl3 imGui = new ImGuiImplGl3(); // OpenGL ImGui context

	private HashMap<Character, Float> sliderSteps = new HashMap<>(); // the incrementation values for each slider

	private ImVec2 mouseDrag = new ImVec2(0f, 0f); // the vector describing the mouse drag
	private float scroll = 0f; // mouse wheel scroll delta

	private static GUIRenderer instance = new GUIRenderer(); // singleton instance

	/**
	 * @return the only GUIRenderer instance
	 */
	public static GUIRenderer getContext() {
		return instance;
	}

	/**
	 * make constructor private for singleton
	 */
	private GUIRenderer() {
	}

	/**
	 * initialize ImGui
	 */
	public void initialize() {
		long windowPtr = Display.ID;

		ImGui.createContext();

		// Initialize ImGuiIO config
		final ImGuiIO io = ImGui.getIO();

		io.setIniFilename(null); // We don't want to save .ini file
		io.setConfigFlags(ImGuiConfigFlags.NavEnableKeyboard); // Navigation with keyboard
		io.setBackendFlags(ImGuiBackendFlags.HasMouseCursors); // Mouse cursors to display while resizing windows etc.
		io.setBackendPlatformName("imgui_java_impl_glfw");

		// ------------------------------------------------------------
		// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[]
		// array.
		final int[] keyMap = new int[ImGuiKey.COUNT];
		keyMap[ImGuiKey.Tab] = GLFW_KEY_TAB;
		keyMap[ImGuiKey.LeftArrow] = GLFW_KEY_LEFT;
		keyMap[ImGuiKey.RightArrow] = GLFW_KEY_RIGHT;
		keyMap[ImGuiKey.UpArrow] = GLFW_KEY_UP;
		keyMap[ImGuiKey.DownArrow] = GLFW_KEY_DOWN;
		keyMap[ImGuiKey.PageUp] = GLFW_KEY_PAGE_UP;
		keyMap[ImGuiKey.PageDown] = GLFW_KEY_PAGE_DOWN;
		keyMap[ImGuiKey.Home] = GLFW_KEY_HOME;
		keyMap[ImGuiKey.End] = GLFW_KEY_END;
		keyMap[ImGuiKey.Insert] = GLFW_KEY_INSERT;
		keyMap[ImGuiKey.Delete] = GLFW_KEY_DELETE;
		keyMap[ImGuiKey.Backspace] = GLFW_KEY_BACKSPACE;
		keyMap[ImGuiKey.Space] = GLFW_KEY_SPACE;
		keyMap[ImGuiKey.Enter] = GLFW_KEY_ENTER;
		keyMap[ImGuiKey.Escape] = GLFW_KEY_ESCAPE;
		keyMap[ImGuiKey.KeyPadEnter] = GLFW_KEY_KP_ENTER;
		keyMap[ImGuiKey.A] = GLFW_KEY_A;
		keyMap[ImGuiKey.C] = GLFW_KEY_C;
		keyMap[ImGuiKey.V] = GLFW_KEY_V;
		keyMap[ImGuiKey.X] = GLFW_KEY_X;
		keyMap[ImGuiKey.Y] = GLFW_KEY_Y;
		keyMap[ImGuiKey.Z] = GLFW_KEY_Z;
		io.setKeyMap(keyMap);

		// ------------------------------------------------------------
		// Mouse cursors mapping
		mouseCursors[ImGuiMouseCursor.Arrow] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		mouseCursors[ImGuiMouseCursor.TextInput] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		mouseCursors[ImGuiMouseCursor.ResizeAll] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		mouseCursors[ImGuiMouseCursor.ResizeNS] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		mouseCursors[ImGuiMouseCursor.ResizeEW] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
		mouseCursors[ImGuiMouseCursor.ResizeNESW] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		mouseCursors[ImGuiMouseCursor.ResizeNWSE] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		mouseCursors[ImGuiMouseCursor.Hand] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
		mouseCursors[ImGuiMouseCursor.NotAllowed] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);

		// ------------------------------------------------------------
		// GLFW callbacks to handle user input

		glfwSetKeyCallback(windowPtr, (w, key, scancode, action, mods) -> {
			if (action == GLFW_PRESS) {
				io.setKeysDown(key, true);
			} else if (action == GLFW_RELEASE) {
				io.setKeysDown(key, false);
			}

			io.setKeyCtrl(io.getKeysDown(GLFW_KEY_LEFT_CONTROL) || io.getKeysDown(GLFW_KEY_RIGHT_CONTROL));
			io.setKeyShift(io.getKeysDown(GLFW_KEY_LEFT_SHIFT) || io.getKeysDown(GLFW_KEY_RIGHT_SHIFT));
			io.setKeyAlt(io.getKeysDown(GLFW_KEY_LEFT_ALT) || io.getKeysDown(GLFW_KEY_RIGHT_ALT));
			io.setKeySuper(io.getKeysDown(GLFW_KEY_LEFT_SUPER) || io.getKeysDown(GLFW_KEY_RIGHT_SUPER));
		});

		glfwSetCharCallback(windowPtr, (w, c) -> {
			if (c != GLFW_KEY_DELETE) {
				io.addInputCharacter(c);
			}
		});

		glfwSetMouseButtonCallback(windowPtr, (w, button, action, mods) -> {
			final boolean[] mouseDown = new boolean[5];

			mouseDown[0] = button == GLFW_MOUSE_BUTTON_1 && action != GLFW_RELEASE;
			mouseDown[1] = button == GLFW_MOUSE_BUTTON_2 && action != GLFW_RELEASE;
			mouseDown[2] = button == GLFW_MOUSE_BUTTON_3 && action != GLFW_RELEASE;
			mouseDown[3] = button == GLFW_MOUSE_BUTTON_4 && action != GLFW_RELEASE;
			mouseDown[4] = button == GLFW_MOUSE_BUTTON_5 && action != GLFW_RELEASE;

			io.setMouseDown(mouseDown);

			if (!io.getWantCaptureMouse() && mouseDown[1]) {
				ImGui.setWindowFocus(null);
			}
		});

		glfwSetScrollCallback(windowPtr, (w, xOffset, yOffset) -> {
			io.setMouseWheelH(io.getMouseWheelH() + (float) xOffset);
			io.setMouseWheel(io.getMouseWheel() + (float) yOffset);
		});

		io.setSetClipboardTextFn(new ImStrConsumer() {
			@Override
			public void accept(final String s) {
				glfwSetClipboardString(windowPtr, s);
			}
		});

		io.setGetClipboardTextFn(new ImStrSupplier() {
			@Override
			public String get() {
				final String clipboardString = glfwGetClipboardString(windowPtr);
				if (clipboardString != null) {
					return clipboardString;
				} else {
					return "";
				}
			}
		});

		imGui.init("#version 330");
		ImGuiStyle style = ImGui.getStyle();
		style.setFrameRounding(0f);
		style.setWindowRounding(0f);
		style.setChildRounding(0f);
		style.setScrollbarRounding(0f);
		style.setGrabRounding(0f);
		style.setTabRounding(0f);
		ImGui.styleColorsDark();
		io.setFontGlobalScale(1.25f);
	}

	/**
	 * setup the beginning of an ImGui frame
	 * 
	 * @param deltaTime - time between frames
	 */
	private void startFrame(final float deltaTime) {
		long windowPtr = Display.ID;
		// For application window properties
		final int[] winWidth = new int[1];
		final int[] winHeight = new int[1];
		final int[] fbWidth = new int[1];
		final int[] fbHeight = new int[1];

		// For mouse tracking
		final double[] mousePosX = new double[1];
		final double[] mousePosY = new double[1];

		// Get window properties and mouse position
		glfwGetWindowSize(windowPtr, winWidth, winHeight);
		glfwGetFramebufferSize(windowPtr, fbWidth, fbHeight);
		glfwGetCursorPos(windowPtr, mousePosX, mousePosY);

		final float scaleX = (float) fbWidth[0] / winWidth[0];
		final float scaleY = (float) fbHeight[0] / winHeight[0];

		// We SHOULD call those methods to update Dear ImGui state for the current frame
		final ImGuiIO io = ImGui.getIO();
		io.setDisplaySize(fbWidth[0], fbHeight[0]);
		io.setDisplayFramebufferScale(scaleX, scaleY);
		io.setMousePos((float) mousePosX[0] * scaleX, (float) mousePosY[0] * scaleY);
		io.setDeltaTime(deltaTime);

		// Update the mouse cursor
		final int imguiCursor = ImGui.getMouseCursor();
		glfwSetCursor(windowPtr, mouseCursors[imguiCursor]);
		glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	/**
	 * render main GUI elements
	 * 
	 * @param dt        - delta time
	 * @param curves    - list with all the curves to draw
	 * @param varValues - map with all the variables and they're corresponding
	 *                  values for the sliders
	 */
	public void render(double dt, ArrayList<Curve> curves, HashMap<Character, Double> varValues) {
		startFrame((float) dt);

		ImGui.newFrame();
		ImGui.setNextWindowPos(2, 2, ImGuiCond.FirstUseEver);
		ImGui.setNextWindowSize(Display.x, Display.height - 4, ImGuiCond.FirstUseEver);
		ImGui.begin("Functions", ImGuiWindowFlags.NoBackground | ImGuiWindowFlags.NoMove | ImGuiWindowFlags.NoResize);

		boolean modification = false; // if any modifications were done

		/*
		 * Render sliders
		 */
		ImGui.text("Sliders");
		for (Map.Entry<Character, Double> entry : varValues.entrySet()) {
			char key = entry.getKey();
			double value = entry.getValue();
			if (validKey(key)) {
				float s = sliderSteps.get(key);
				ImDouble val = new ImDouble(value);
				boolean mod;

				// value slider
				mod = ImGui.dragScalar(Character.toString(key), ImGuiDataType.Double, val, s);
				modification = modification || mod;
				varValues.put(key, val.get());

//				ImGui.sameLine();

				// step / incrementation slider
				ImFloat step = new ImFloat(s);
				mod = ImGui.dragScalar("Step " + key, ImGuiDataType.Float, step, 0.001f);
				modification = modification || mod;
				sliderSteps.put(key, step.get());

				ImGui.separator();
			}
		}

		ImGui.separator();

		/*
		 * Render functions
		 */
		ImGui.inputText("Input here", strFunction);
		ImGui.sameLine();
		ImGuiHelp("Input your function here. Example: x^2 + 2");
		if (ImGui.button("Add Function")) {
			String func = strFunction.get();
			HashSet<Character> variables = new HashSet<>();
			curves.add(new Curve(new Equation(func, variables)));
			variables.forEach(key -> {
				if (validKey(key)) {
					varValues.putIfAbsent(key, 1d);
					sliderSteps.putIfAbsent(key, 0.01f);
				}
			});
		}

		for (int i = 0; i < curves.size(); i++) {
			Curve curve = curves.get(i);
			GraphableEquation func = curve.getFunction();
			GraphableEquation der = curve.getDerivative();
			if (ImGui.collapsingHeader("Function " + i, ImGuiTreeNodeFlags.DefaultOpen)) {
				ImBool visible;
				Texture tex;
				boolean mod;

				// Function
				visible = new ImBool(func.isVisible());
				ImGui.checkbox("Plot function " + i, visible);
				func.setVisible(visible.get());
				mod = ImGui.colorEdit4("FColor " + i, func.getColor(), ImGuiColorEditFlags.Float);
				modification = modification || mod;
				tex = func.getTexture();
				ImGui.image(tex.getID(), tex.getWidth(), tex.getHeight());

				// Derivative
				visible = new ImBool(der.isVisible());
				ImGui.checkbox("Plot derivative " + i, visible);
				der.setVisible(visible.get());
				mod = ImGui.colorEdit4("DColor " + i, der.getColor(), ImGuiColorEditFlags.Float);
				modification = modification || mod;
				tex = der.getTexture();
				ImGui.image(tex.getID(), tex.getWidth(), tex.getHeight());
			}
		}

		collectInput(!modification);

//		ImGui.showDemoWindow();

		ImGui.end();
		ImGui.render();

		imGui.render(ImGui.getDrawData());

	}

	/**
	 * @param key
	 * @return true if the given key is valid to be a slider
	 */
	private boolean validKey(char key) {
		return key != 'x' && key != 'y' && key != 'z';
	}

	/**
	 * create a help tooltip with ImGui and the given message
	 * 
	 * @param message - help message
	 */
	private void ImGuiHelp(String message) {
		ImGui.textDisabled("(?)");
		if (ImGui.isItemHovered()) {
			ImGui.beginTooltip();
			ImGui.pushTextWrapPos(ImGui.getFontSize() * 35.0f);
			ImGui.textUnformatted(message);
			ImGui.popTextWrapPos();
			ImGui.endTooltip();
		}
	}

	/**
	 * save and update the input properties
	 * 
	 * @param recordMouseMove - if we should record mouse movement
	 */
	private void collectInput(boolean recordMouseMove) {
		ImGuiIO io = ImGui.getIO();
		mouseDrag = new ImVec2(0f, 0f);
		if (io.getMouseDown(ImGuiMouseButton.Left) && recordMouseMove)
			io.getMouseDelta(mouseDrag);
		scroll = io.getMouseWheel();
	}

	/**
	 * @return 
	 */
	public float getDragX() {
		return mouseDrag.x;
	}

	public float getDragY() {
		return mouseDrag.y;
	}

	public float getMouseScroll() {
		return scroll;
	}

	public void destroy() {
		imGui.dispose();
		ImGui.destroyContext();

		for (long mouseCursor : mouseCursors) {
			glfwDestroyCursor(mouseCursor);
		}
	}
}