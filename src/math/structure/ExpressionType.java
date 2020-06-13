package math.structure;

/**
 * this is an Enum type class to identify expressions: give them a name and an
 * order value to be sorted by. This can be used instead of the instanceof
 * operator when it is more practical than overridden methods.
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public enum ExpressionType {

	CONSTANT(0, "constant"), // type constant/number
	VARIABLE(1, "variable"), // type variable like x, y, z, a, b, c

	POWER(2, "power"), // type power: e^f and f^g
	FRACTION(3, "fraction"), // type fraction: f / g
	LOGARITHM(4, "logarithm"), // type logarithm: ln(f) or log_f(g)

	ABSOLUTE_VALUE(5, "abs"), // absolute value of a function: abs(f)
	FLOOR(6, "floor"), // floor function, truncates decimal: floor(f)
	CEILING(7, "ceil"), // ceiling function, rounds up to nearest ones: ceil(f)

	SIN(8, "sin"), COS(9, "cos"), TAN(10, "tan"), // basic trig functions
	CSC(11, "csc"), SEC(12, "sec"), COT(13, "cot"), // reciprocal trig functions
	ARCSIN(14, "arcsin"), ARCCOS(15, "arccos"), ARCTAN(16, "arctan"), // inverse trig

	MAX(17, "max"), MIN(18, "min"), // max and min functions

	PRODUCT(19, "product"), // type product with *
	SUM(20, "sum"); // type sum with +

	protected final String name; // name of the function
	protected final int order; // order in which to sort the functions, smaller number shows precedence

	/*
	 * constructor with all fields
	 */
	ExpressionType(int order, String name) {
		this.name = name;
		this.order = order;
	}

	@Override
	public String toString() {
		return name;
	}
}