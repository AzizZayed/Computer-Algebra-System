package math.structure;

/**
 * class for an arbitrary mathematical expression
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class Expression implements IMath {

	/**
	 * calculate the value of the mathematical expression
	 * 
	 * @param x - value of x
	 * @return the value of the expression
	 */
	public abstract double evaluate(double x);
}
