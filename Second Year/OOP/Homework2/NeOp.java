//package tema2POO;

/**
 * Clasa pentru operatorul Ne
 * 
 * @author alexpeti
 *
 */
public class NeOp implements Operator {

	@Override
	/**
	 * verificam daca cele doua valori sunt diferite
	 */
	public boolean check(double value, double comparedValue) {
		if (value != comparedValue)
			return true;
		return false;
	}

	/**
	 * verificam daca cele dooua nume sunt diferite
	 */
	public boolean check(String name, String comaparedName) {
		if (!name.equals(comaparedName))
			return true;
		return false;
	}

}
