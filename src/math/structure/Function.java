package math.structure;

/**
 * class that represents any elementary function like trigonometric functions,
 * absolute value, floor, ceiling ... etc
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class Function extends Expression implements IMath {

	Expression expr;

	public Function(Expression expr) {
		this.expr = expr;
	}

}