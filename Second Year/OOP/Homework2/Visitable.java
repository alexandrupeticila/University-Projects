//package tema2POO;

/**
 * Interfata este implementata de nodurile din arborele de expresie.
 * 
 * @author alexpeti
 *
 */
interface Visitable {
	/**
	 * 
	 * @param visitor
	 * @param name
	 *            numele feedului
	 * @param value
	 *            valoare feedului
	 * @return valoare de adevar in urma verificarii conditiei.
	 */
	boolean accept(IVisitor visitor, String name, double value);
}
