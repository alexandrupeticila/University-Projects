//package tema1;

/**
 * clasa pentru a genera obiecte de tip lru
 * 
 * @author alexpeti
 *
 */
class LruStructure {

	String procesName;
	int inputNr;

	public LruStructure() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * 
	 * @param procesName
	 *            = numele procesului
	 * @param in
	 *            = inputul pentru care este calculat procesului
	 */
	LruStructure(String procesName, int in) {
		this.procesName = procesName;
		this.inputNr = in;
	}

}
