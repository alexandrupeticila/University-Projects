//package tema2POO;
/**
 * Clasa pentru operatorul Ge
 * @author alexpeti
 *
 */
public class GtOp implements Operator {

	@Override
	/**
	 * Verificam conditia specifica
	 */
	public boolean check(double value, double comparedValue) {
		if (value > comparedValue)
			return true;
		return false;
	}

	@Override
	public boolean check(String name, String comparedName) {
		// TODO Auto-generated method stub
		return false;
	}

}