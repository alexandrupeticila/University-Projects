/**
 * Clasa folosita pentru construirea labirintului
 * 
 * @author alexpeti
 *
 */
class CellFactory {

	public CellFactory() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * 
	 * @param name
	 *            tipul celulei
	 * @return celula de tipul primit
	 */
	public Cell getCell(String name) {

		if (name.equals(".")) {
			return new SpaceCell(".");
		} else if (name.equals("#")) {
			return new WallCell("#");
		} else if (name.equals("I")) {
			return new ICell("I");
		} else if (name.equals("O")) {
			return new OCell("O");
		} else
			return null;
	}

}
