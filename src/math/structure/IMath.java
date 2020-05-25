package math.structure;

/**
 * interface for all math related structures
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public interface IMath {

	/**
	 * @return the latex code of the mathematical expression
	 */
	public String toLatex();

	@Override
	public String toString();
}
