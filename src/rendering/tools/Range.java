package rendering.tools;

public class Range {

	private double min, max;

	public Range(double min, double max) {
		this.min = min;
		this.max = max;
	}

	/**
	 * @return the min
	 */
	public double getMin() {
		return min;
	}

	/**
	 * @param min the min to set
	 */
	public void setMin(double min) {
		this.min = min;
	}

	/**
	 * @return the max
	 */
	public double getMax() {
		return max;
	}

	/**
	 * @param max the max to set
	 */
	public void setMax(double max) {
		this.max = max;
	}

	public void set(double min, double max) {
		setMin(min);
		setMax(max);
	}

	/**
	 * @return the length of the range
	 */
	public double getLength() {
		return max - min;
	}

	/**
	 * checks if the given value is in the range described by this class
	 * 
	 * @param value - value to check
	 * @return true if the value is in range
	 */
	public boolean inRange(double value) {
		return value >= min && value < max;
	}
}