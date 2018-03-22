//package tema2POO;

/**
 * Clasa folosita pentru a instantia noduri de tip AND
 * 
 * @author alexpeti
 *
 */
class AndNode extends Node implements Visitable {
	/**
	 * 
	 * @param left
	 *            fiul din stanga
	 * @param right
	 *            fiul din dreapta
	 */
	AndNode(Node left, Node right) {
		super(left, right);
	}

	@Override
	/**
	 * Metoda care viziteaza nodul curent
	 */
	public boolean accept(IVisitor visitor, String name, double value) {
		return visitor.visit(this, name, value);
	}
}