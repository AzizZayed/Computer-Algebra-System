package rendering.tools;

import static org.lwjgl.opengl.GL11.GL_LINES;
import static org.lwjgl.opengl.GL11.glBegin;
import static org.lwjgl.opengl.GL11.glColor3f;
import static org.lwjgl.opengl.GL11.glEnd;
import static org.lwjgl.opengl.GL11.glVertex3d;

public class Grid {

	private static final double DRAG_DAMPENER = 1000d;
	private static final double ZOOM_DAMPENER = 300d;

	private Range x, y, z; // range in x and y direction
	private double xRotation = 0, yRotation = 0;

	public Grid(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax) {
		x = new Range(xmin, xmax);
		y = new Range(ymin, ymax);
		z = new Range(zmin, zmax);
	}

	public Grid(Grid grid) {
		x = new Range(grid.getXMin(), grid.getXMax());
		y = new Range(grid.getYMin(), grid.getYMax());
		z = new Range(grid.getZMin(), grid.getZMax());
	}

	public Grid(Range x, Range y, Range z) {
		this.x = x;
		this.y = y;
		this.z = z;
	}

	/**
	 * @return the x
	 */
	public Range getX() {
		return x;
	}

	/**
	 * @return the x min
	 */
	public double getXMin() {
		return x.getMin();
	}

	/**
	 * @return the x max
	 */
	public double getXMax() {
		return x.getMax();
	}

	/**
	 * @param x the x to set
	 */
	public void setRangeX(double xmin, double xmax) {
		this.x.setMin(xmin);
		this.x.setMax(xmax);
	}

	/**
	 * @return the y
	 */
	public Range getY() {
		return y;
	}

	/**
	 * @return the y min
	 */
	public double getYMin() {
		return y.getMin();
	}

	/**
	 * @return the y max
	 */
	public double getYMax() {
		return y.getMax();
	}

	/**
	 * @param y the y to set
	 */
	public void setRangeY(double ymin, double ymax) {
		this.y.setMin(ymin);
		this.y.setMax(ymax);
	}

	/**
	 * @return the z
	 */
	public Range getZ() {
		return z;
	}

	/**
	 * @return the z min
	 */
	public double getZMin() {
		return z.getMin();
	}

	/**
	 * @return the y max
	 */
	public double getZMax() {
		return z.getMax();
	}

	/**
	 * @param y the y to set
	 */
	public void setRangeZ(double zmin, double zmax) {
		z.setMin(zmin);
		z.setMax(zmax);
	}

	public boolean isEqualsTo(Grid grid) {
		return x.getMin() == grid.getXMin() && x.getMax() == grid.getXMax() && y.getMin() == grid.getYMin()
				&& y.getMax() == grid.getYMax() && z.getMin() == grid.getZMin() && z.getMax() == grid.getZMax();
	}

	/**
	 * translate the grid
	 * 
	 * @param dx - change in mouse x
	 * @param dy = change in mouse y
	 */
	public void drag(double dx, double dy) {
		dx = dx / DRAG_DAMPENER * x.getLength();
		dy = dy / DRAG_DAMPENER * y.getLength();

		x.set(x.getMin() - dx, x.getMax() - dx);
		y.set(y.getMin() + dy, y.getMax() + dy);
	}

	/**
	 * zoom into the grid
	 * 
	 * @param ds - mouse scroll change
	 */
	public void zoom(double ds) {
		ds = ds / ZOOM_DAMPENER * (x.getLength() + y.getLength());

		double xmin = x.getMin() + ds;
		double xmax = x.getMax() - ds;

		if (xmin < xmax) {
			x.set(xmin, xmax);
			y.set(y.getMin() + ds, y.getMax() - ds);
			z.set(z.getMin() + ds, z.getMax() - ds);
		}
	}
	
	public void rotate(double rx, double ry) {
		xRotation += rx;
		yRotation += ry;
	}

	/**
	 * @return the xRotation
	 */
	public double getxRotation() {
		return xRotation;
	}

	/**
	 * @return the yRotation
	 */
	public double getyRotation() {
		return yRotation;
	}
	
	public void render() {
		float scale = 1.25f;

		glColor3f(1f, 0f, 0f);
		glBegin(GL_LINES);
		glVertex3d(0d, 0d, 0d);
		glVertex3d(x.getMax() * scale, 0d, 0d);
		glEnd();

		// Draw y-axis in green
		glColor3f(0f, 1f, 0f);
		glBegin(GL_LINES);
		glVertex3d(0d, 0d, 0d);
		glVertex3d(0d, y.getMax() * scale, 0d);
		glEnd();

		// Draw z-axis in blue
		glColor3f(0f, 0f, 1f);
		glBegin(GL_LINES);
		glVertex3d(0d, 0d, 0d);
		glVertex3d(0d, 0d, z.getMax() * scale);
		glEnd();
	}
}