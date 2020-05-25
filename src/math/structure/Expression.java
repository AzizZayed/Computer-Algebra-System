package math.structure;

import java.util.HashMap;

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
	 * @param varValues - map with all the values of each variable in the expression
	 * @return the value of the expression
	 */
	public abstract double evaluate(HashMap<Character, Double> varValues);
}
