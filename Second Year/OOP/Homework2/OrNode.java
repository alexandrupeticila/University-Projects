//package tema2POO;

/**
 * Clasa este folosita pentru a instantia noduri de tip Or
 * 
 * @author alexpeti
 *
 */
public class OrNode extends Node implements Visitable {
	/**
	 * 
	 * @param left
	 *            nodul din stanga
	 * @param right
	 *            nodul din dreapta
	 */
	public OrNode(Node left, Node right) {
		super(left, right);
	}

	@Override
	/**
	 * metoda viziteaza nodul curent
	 */
	public boolean accept(IVisitor visitor, String name, double value) {
		return visitor.visit(this, name, value);
	}
}
