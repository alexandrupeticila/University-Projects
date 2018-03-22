//package tema2POO;

/**
 * Clasa implementeaza interfata Ivistor si defineste cele trei metode de
 * vizitare pentru cele trei tipuri de noduri.
 * 
 * @author alexpeti
 *
 */

class CalculatorVisitor implements IVisitor {

	@Override
	/**
	 * metoda primeste ca parametru un nod de tip Or si verifica daca elementul
	 * (feedul) respecta una dintre conditiile din dreapta sau din stanga si in
	 * functie de rezultat intoarce true sau false.
	 */
	public boolean visit(OrNode operatorNode, String name, double value) {
		return operatorNode.left.accept(this, name, value) || operatorNode.right.accept(this, name, value);
	}

	@Override
	/**
	 * aceasta metoda primeste un nod de tip And si face aceleasi verificari dar de
	 * data aceasta feedul definit prin name si value trebuie sa respecte ambele
	 * conditii pentru ca valoarea rezultata sa fie TRUE.
	 */
	public boolean visit(AndNode operatorNode, String name, double value) {
		return operatorNode.left.accept(this, name, value) && operatorNode.right.accept(this, name, value);
	}

	@Override
	/**
	 * metoda visiteaza un nod de tip OperandNode, mai exact frunza in care tin o
	 * expresie alcatuita din trei stringuri, primul fiind unul dintre operatori
	 * pentru care am definit separat cate o clasa, al doilea campul care se doreste
	 * a fi verificat nume/valoare feed si al treilea elementul cu care se compara.
	 * Metoda imi returneaza valaoreade adevar obtinuta in urma comparatiei.
	 */
	public boolean visit(OperandNode operandNode, String name, double value) {
		return operandNode.check(name, value);
	}
}