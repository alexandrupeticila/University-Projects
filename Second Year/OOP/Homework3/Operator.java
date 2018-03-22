//package tema2POO;

/**
 * interfata care defineste metodele continute de cei 6 operatori
 * 
 * @author alexpeti
 *
 */
public interface Operator {
	/**
	 * 
	 * @param value
	 *            valoare feedului
	 * @param comparedValue
	 *            valoarea cu care se compara valoarea feedului
	 * @return valoare de adevar in functie de reepectare conditiei de catre feed
	 */
	boolean check(double value, double comparedValue);

	/**
	 * Aceasta metoda este implementata doar de coperatorii eq si ne
	 * 
	 * @param name
	 *            numele feedului
	 * @param comparedName
	 *            numele cu care se compara feedul
	 * @return valoare de adevar a respectarii conditiei
	 */
	boolean check(String name, String comparedName);
}
