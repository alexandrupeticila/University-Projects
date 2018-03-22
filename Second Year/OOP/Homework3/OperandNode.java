//package tema2POO;

/**
 * Clasa folosita pentru a instantia noduri de tip frunza. Aceste noduri contin
 * o expresie de tip String alcatuita din 3 elemente Primul reprezinta tipul
 * operatorului Al doilea campul feedului care urmeaza a fi comparat. Al treilea
 * valoarea cu care urmeaza sa se compare
 * 
 * @author alexpeti
 *
 */
class OperandNode extends Node implements Visitable {

	public String exp;

	/**
	 * 
	 * @param current
	 *            stringul care va fi atribuit expresiei ce reprezinta campul
	 *            nodului curent
	 */
	public OperandNode(String current) {
		super(null, null);
		exp = current;
	}

	@Override
	/**
	 * metoda care viziteaza nodul curent
	 */
	public boolean accept(IVisitor visitor, String name, double value) {
		return visitor.visit(this, name, value);
	}

	/**
	 * Metoda verifica daca parametrii primiti, care constituie elementele unui feed
	 * respecta sau nu conditia prezenta ce se afla in expresia aferenta nodului
	 * curent pe care o atribuim cu ajutorul constructorului. Astfel, splitam
	 * expresia dupa spatiu si vom obtine astfel un vector de 3 stringuri. Vom lua
	 * primul string si folosind clasa OperatorFactory vom obtine o instanta
	 * corespunzatoare. Apoi vom folosi metoda specifica acestei instanta in functie
	 * de stringul doi (pentru nume sau pentru valoare), care va lua al treilea
	 * string si paramtrul corespunzator si ne va spune daca feedul respecta sau nu
	 * conditia.
	 * 
	 * @param feedName
	 *            numele feedului
	 * @param feedValue
	 *            valoarea feedului
	 * @return valoarea de adevar care arata respectarea sau nu a conditiei de catre
	 *         feed
	 */
	public boolean check(String feedName, double feedValue) {
		String[] expresie = exp.split(" ");
		OperatorFactory opFactory = OperatorFactory.getInstance();
		Operator operator = opFactory.getOperator(expresie[0]);
		if (expresie[1].equals("name")) {
			return operator.check(feedName, expresie[2]);
		} else
			return operator.check(feedValue, Double.parseDouble(expresie[2]));
	}
}
