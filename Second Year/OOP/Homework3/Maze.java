import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * Aceasta clasa imi construieste labirintul dar in functie de task. Astfel, la
 * primul task voi folosi o bordura pentru a verifica daca eroul depaseste sau
 * nu labirintul. Pentru al doilea task, aceasta bordura nu mai este necesara
 * 
 * @author alexpeti
 *
 */
class Maze {

	private Scanner sc;

	/**
	 * aceasta metoda imi inconjoara labirintul primut cu celule de tip OutCell
	 * 
	 * @param mazetask1
	 *            labirintul de la task1
	 */
	static void fence(Cell[][] mazetask1) {
		for (int i = 0; i < mazetask1.length; i++) {
			mazetask1[i][0] = new OutCell("Out");
			mazetask1[i][mazetask1[0].length - 1] = new OutCell("Out");
		}

		for (int j = 0; j < mazetask1[0].length; j++) {
			mazetask1[0][j] = new OutCell("Out");
			mazetask1[mazetask1.length - 1][j] = new OutCell("Out");
		}

	}

	/**
	 * Setez mai intai nr de linii si de coloane, apoi construiesc un labirint
	 * suficient de mare pentru a putea fi inconjurat de celule de tip Out, lucru pe
	 * care il fac ulterior. Apoi cu ajutorul unei instante de CellFactory
	 * construiesc partea interioara a labirintului.
	 * 
	 * @param text
	 *            fisierul de intare
	 * @return labirinttul
	 * @throws FileNotFoundException
	 *             daca fisiereul de input nu e gasit
	 */
	Cell[][] getMaze(File text) throws FileNotFoundException {
		sc = new Scanner(text);
		int lineNumber = sc.nextInt();
		int columnNumber = sc.nextInt();

		sc.nextLine();

		Cell[][] mazetask1 = new Cell[lineNumber + 2][columnNumber + 2];

		CellFactory factory = new CellFactory();
		int lineIterator = 1;
		int columnIterator = 1;

		fence(mazetask1);

		while (sc.hasNextLine()) {

			String line = sc.nextLine();
			while (columnIterator < line.length() + 1) {
				mazetask1[lineIterator][columnIterator] = factory
						.getCell(line.substring(columnIterator - 1, columnIterator));

				mazetask1[lineIterator][columnIterator].setLinieColoana(lineIterator, columnIterator);
				columnIterator++;
			}

			columnIterator = 1;
			lineIterator++;
		}
		return mazetask1;
	}

	/**
	 * Acelasi lucru ca la metoda anterioara insa de data aceasta nu mai inconjor
	 * labirintul;
	 * 
	 * @param text
	 *            fisierul de intare
	 * @return labirinttul
	 * @throws FileNotFoundException
	 *             daca fisiereul de input nu e gasit
	 */

	Cell[][] getMaze2(File text) throws FileNotFoundException {
		sc = new Scanner(text);
		int lineNumber = sc.nextInt();
		int columnNumber = sc.nextInt();

		sc.nextLine();

		Cell[][] mazetask2 = new Cell[lineNumber][columnNumber];

		CellFactory factory = new CellFactory();
		int lineIterator = 0;
		int columnIterator = 0;

		while (sc.hasNextLine()) {

			String line = sc.nextLine();
			while (columnIterator < line.length()) {
				mazetask2[lineIterator][columnIterator] = factory
						.getCell(line.substring(columnIterator, columnIterator + 1));

				mazetask2[lineIterator][columnIterator].setLinieColoana(lineIterator, columnIterator);
				columnIterator++;
			}

			columnIterator = 0;
			lineIterator++;
		}
		return mazetask2;
	}

}
