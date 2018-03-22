//package tema2POO;

/**
 * Aceasta clasa este folosita pentru a construi nodurile in arborele de
 * expresie. Astfel, clasa prezinta doua campuri de tip nod, numite left si
 * right care, usor de dedus, reprezinta nodurile fii.
 * 
 * @author alexpeti
 *
 */
class Node implements Visitable {

	public Node left;
	public Node right;

	/**
	 * constructor care primeste doua noduri si actualizeaza cei doi parametrii.
	 * 
	 * @param left
	 *            nodul stanga
	 * @param right
	 *            nodul dreapta
	 */
	public Node(Node left, Node right) {
		this.left = left;
		this.right = right;
	}

	/**
	 * aceasta metoda va fi suprasrissa in clasele care o extind, in functie de
	 * tipul nodului.
	 */
	public boolean accept(IVisitor visitor, String name, double value) {
		return true;
	}
}