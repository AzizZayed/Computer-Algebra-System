package math.structure;

/**
 * class to represent any constant/number
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public class Constant extends Expression implements IMath {

	public static final Constant PI = new Constant(3.141592653589793d);
	public static final Constant EXP = new Constant(2.718281828459045d);
	public static final Constant GOLDEN_RATIO = new Constant(1.618033988749895d);

	private double value;

	/**
	 * @return the value of the constant
	 */
	public double getValue() {
		return value;
	}

	public Constant(double val) {
		value = val;
	}

	@Override
	public double evaluate(double x) {
		return value;
	}

	@Override
	public String toString() {
		if (this == PI || value == PI.value)
			return "\u03C0";
		if (this == EXP || value == EXP.value)
			return "e";
		if (this == GOLDEN_RATIO || value == GOLDEN_RATIO.value)
			return "\u03D5";

		String strValue = Double.toString(value);
		if (value == Math.floor(value)) // check if integer and if so, display 2 instead of 2.0
			return strValue.substring(0, strValue.indexOf('.'));
		return strValue;
	}

	@Override
	public String toLatex() {
		return toString();
	}
}