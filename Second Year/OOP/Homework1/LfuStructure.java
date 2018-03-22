//package tema1;

/**
 * clasa folosita pentru a crearea de obiecte de tip lfu
 * 
 * @author alexpeti
 *
 */
class LfuStructure {

	String procesName;
	int inputNr;
	int nraparitii = 0; // de cate ori apare procesul.

	public LfuStructure() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * 
	 * @param procesName
	 *            = numele procesului
	 * @param in
	 *            = inputul pentru care este calculat procesului
	 */
	LfuStructure(String procesName, int in) {
		this.procesName = procesName;
		this.inputNr = in;
	}

}
