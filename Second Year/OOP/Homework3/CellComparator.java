import java.util.Comparator;

/**
 * Comparatrul care imi pune celule in ordinea ceruta de exercitiu
 * 
 * @author alexpeti
 *
 */
class CellComparator implements Comparator<Cell> {

	 CellComparator() {

	}

	/**
	 * iau doua celule si le compar mai intai in functie de nr de
	 * pietre(prioritatea), si apoi de pozitia acestora
	 */
	@Override
	public int compare(Cell cel1, Cell cel2) {
		if (cel1.getNrPietre() == cel2.getNrPietre()) {
			if (cel1.getPozitie().equals("R")) {
				return -1;
			} else if (cel2.getPozitie().equals("R")) {
				return 1;
			} else if (cel1.getPozitie().equals("F")) {
				return -1;
			} else if (cel2.getPozitie().equals("F")) {
				return 1;
			} else if (cel1.getPozitie().equals("L")) {
				return -1;
			} else
				return 1;
		} else {
			return cel1.getNrPietre() - cel2.getNrPietre();
		}

	}

}
