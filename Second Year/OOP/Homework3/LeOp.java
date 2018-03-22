//package tema2POO;
/**
 * Clasa  pentru operatorul Le
 * @author alexpeti
 *
 */
public class LeOp implements Operator {

	@Override
	/**
	 * verificam conditia
	 */
	public boolean check(double value, double comparedValue) {
		if (value <= comparedValue)
			return true;
		return false;
	}

	@Override
	public boolean check(String name, String comparedName) {
		// TODO Auto-generated method stub
		return false;
	}

}