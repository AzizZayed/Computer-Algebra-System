package math.structure;

/**
 * interface for all math related structures
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public interface IMath {

	/**
	 * calculate the value of the expression
	 * 
	 * @param x - value of x
	 * @return the value of the expression
	 */
	public double evaluate(double x);

	@Override
	public String toString();
}
