package math.structure;

/**
 * class that represents any elementary function like trigonometric functions,
 * absolute value, floor, ceiling ... etc. Notice all these function have fixed
 * amount of inputs. If a function has an arbitrary amount of inputs, it is a
 * subclass of
 * 
 * @author Abd-El-Aziz Zayed
 *
 */
public abstract class FixedInputFunction extends Expression implements IMath {

	protected Expression expr; // the input to the function

	public FixedInputFunction(ExpressionType type, Expression expr) {
		super(type);
		this.expr = expr;
	}
}