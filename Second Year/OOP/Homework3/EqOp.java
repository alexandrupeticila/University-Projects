//package tema2POO;

/**
 * Operator Eq
 * 
 * @author alexpeti
 *
 */
public class EqOp implements Operator {

	@Override
	/**
	 * verificam daca cele doua valori sunt sau nu egale
	 */
	public boolean check(double value, double comparedValue) {
		if (value == comparedValue)
			return true;
		return false;
	}

	/**
	 * verificam daca cele doua stringuri sunt identice
	 */
	public boolean check(String name, String comparedName) {
		if (name.equals(comparedName))
			return true;
		return false;
	}

}
