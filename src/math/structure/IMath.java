package math.structure;

/**
 * Interface for all math related structures
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public interface IMath {

	/**
	 * @return the latex code for the mathematical expression
	 */
	public String toLatex();

	@Override
	public String toString();
}
