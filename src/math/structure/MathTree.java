package math.structure;

import math.structure.Expression.Constant;
import math.structure.Expression.Fraction;
import math.structure.Expression.Term;
import math.structure.Function.Ceil;
import math.structure.Function.Floor;
import math.structure.Log.Ln;
import math.structure.Operator.Product;
import math.structure.Operator.Sum;
import math.structure.Power.Exp;
import math.structure.Trigonometry.Cos;
import math.structure.Trigonometry.Sin;
import math.structure.Trigonometry.Tan;

public class MathTree implements IMath {

	private Expression root;

	public MathTree() {
		root = new Sum(
					new Power(
						new Sum(
								new Fraction(
										new Sum(
												new Exp(new Term()),
												Constant.GOLDEN_RATIO,
												new Log(new Constant(2),new Constant(1)),
												new Ln(new Constant(1)),
												new Floor(new Constant(0.123)),
												new Ceil(new Constant(-0.123))
												),
										new Term()
										),
								new Constant(9)
								),
						new Power(
								new Sum(
										new Product(
												new Constant(19),
												new Power(new Term(), new Constant(2))
												),
										new Fraction(new Constant(7), new Term()),
										new Product(new Constant(5), new Term())
										),
								Constant.PI
								)
					), 
					new Cos(new Constant(0)),
					new Sin(new Constant(0)),
					new Tan(new Constant(0))
				);
	}

	@Override
	public double evaluate(double x) {
		return root.evaluate(x);
	}

	@Override
	public String toString() {
		return root.toString();
	}
}