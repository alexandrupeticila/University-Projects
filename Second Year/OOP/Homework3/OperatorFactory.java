//package tema2POO;

/**
 * Clasa Factory folosita impreuna cu patternul Singleton pentru a obtine o
 * anumita instanta in functie de un string primit ca parametru
 * 
 * @author alexpeti
 *
 */
public class OperatorFactory {

	private static OperatorFactory instance = new OperatorFactory();

	private OperatorFactory() {
	}

	/**
	 * 
	 * @return singura instanta a clasei
	 */
	public static OperatorFactory getInstance() {
		return instance;
	}

	/**
	 * 
	 * @param name
	 *            numele operatorului
	 * @return o instanta a operatorului
	 */
	public Operator getOperator(String name) {
		if (name.equals("le")) {
			return new LeOp();
		} else if (name.equals("lt")) {
			return new LtOp();
		} else if (name.equals("ge")) {
			return new GeOp();
		} else if (name.equals("gt")) {
			return new GtOp();
		} else if (name.equals("ne")) {
			return new NeOp();
		} else
			return new EqOp();
	}
}
