import java.io.BufferedWriter;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

class Task2 {
	/**
	 * gasesc celula de plecare
	 * 
	 * @param maze
	 *            labirintul
	 * @return celula de plecare
	 */
	private static ICell findICell(Cell[][] maze) {
		for (int i = 0; i < maze.length; i++) {
			for (int j = 0; j < maze[i].length; j++) {
				if (maze[i][j].getTip().equals("I")) {
					return (ICell) maze[i][j];
				}

			}
		}
		return null;
	}

	/**
	 * gasesc portalul de iesire
	 * 
	 * @param maze
	 *            labirintul
	 * @return celula de iesire
	 */
	private static OCell findOCell(Cell[][] maze) {
		for (int i = 0; i < maze.length; i++) {
			for (int j = 0; j < maze[i].length; j++) {
				if (maze[i][j].getTip().equals("O")) {
					return (OCell) maze[i][j];
				}

			}
		}
		return null;
	}

	/**
	 * verific daca celula este in labirint si daca este una libera(Space sau O) si
	 * in acest caz returnez true, altfel returnez false;
	 * 
	 * @param maze
	 *            labirintul
	 * @param linie
	 *            linia curenta
	 * @param coloana
	 *            coloana curenta
	 * @return valoarea conform careia celula se poate sau nu parcurge
	 */
	private static boolean isSpaceCell(Cell[][] maze, int linie, int coloana) {

		boolean ok = false;
		try {
			if (linie < 0 || coloana < 0 || linie >= maze.length || coloana >= maze[linie].length)
				throw new HeroOutOfGroundException();
			if (maze[linie][coloana] instanceof WallCell)
				throw new CannotMoveIntoWallsException();

			if (maze[linie][coloana] instanceof SpaceCell || maze[linie][coloana] instanceof OCell)
				ok = true;
		} catch (CannotMoveIntoWallsException e) {

		} catch (HeroOutOfGroundException e) {

		}
		return ok;

	}

	/**
	 * In cazul in care vor exista mai multe drumuri la fel de scurte, cel prioritar
	 * va fi dat de ordinea data in actualizarea enuntului(forum), cei doi vectori
	 * folosindu-i pentru a respecta aceasta ordine de vizitare
	 */
	private static int[] veciniLinie = { 0, -1, 0, 1 };
	private static int[] VeciniColoana = { 1, 0, -1, 0 };

	/**
	 * Incep prin a cauta mai intai cele doua celule importante, cea de intrare si
	 * cea de iesire. Voi folosi o coada cu elemente de tip celula in care introduc
	 * celulele vizitate(cele care pot fi vizitate, verificand de fiecare data asest
	 * lucru cu ajutorul metodei isSpaceCell), actualizand pozitia cu ajutorul celor
	 * doi vectori de vecini. In plus, parcurg fiecare celula o singura data, de
	 * accea voi actualiza valoarea campului "parcurs" cu true dupa ce o parcurg. De
	 * asemenea, legatura cu parintele e facuta tot aici. Repet acest lucru pana
	 * gasesc portalul. Conditia de a repeta pana coada nu mai are elemente nu se va
	 * atinge aici deoarece cerinta asigura exista unui drum intre portalul de
	 * intare si cel de iesire.Nu am folosit distanta in aceasta implementare a
	 * algoritumului lui Lee deoarece prin facerea legaturii dintre celula actuala
	 * si parinte voi retine ce elemente sa inserez in stiva, iar dimensiunea
	 * drumului va fi chiar dimensiunea listei. La sfarsit voi apela functia care
	 * imi printeaza drumul.
	 * 
	 * @param maze
	 *            labirintul
	 * @param writer
	 *            BufferedWriterul cu ajutorul caruia scriu in fisiere.
	 * @throws IOException
	 */
	void leeAlg(Cell[][] maze, BufferedWriter writer) throws IOException {

		ICell iCell = findICell(maze);
		OCell oCell = findOCell(maze);

		Queue<Cell> coadaCelule = new LinkedList<Cell>();
		coadaCelule.add(iCell);

		while (!coadaCelule.isEmpty()) {
			Cell curenta = coadaCelule.remove();

			if (curenta == oCell) {
				break;
			}
			for (int i = 0; i < 4; i++) {
				int linie = curenta.getLinie() + veciniLinie[i];
				int coloana = curenta.getColoana() + VeciniColoana[i];

				if (isSpaceCell(maze, linie, coloana)) {

					if (maze[linie][coloana].parcurs == false) {
						maze[linie][coloana].parcurs = true;
						maze[linie][coloana].setParinte(curenta);
						coadaCelule.add(maze[linie][coloana]);
					}
				}
			}

		}

		printare(iCell, oCell, writer);

	}

	/**
	 * Plecand de la celula de iesire, cu ajutorul campului parinte, voi pune in
	 * stiva toate celulele pana ajung la celula de intrare, pe care o voi introduce
	 * la sfarsit. Folosesc stiva pentru ca apoi sa scot fiecare element si sa ii
	 * printez pozitia pana cand golosesc stiva
	 * 
	 * @param iCell
	 *            celula de intrare
	 * @param oCell
	 *            celula de iesire
	 * @param writer
	 *            scriu in fisierul de out
	 * @throws IOException
	 */
	static void printare(ICell iCell, OCell oCell, BufferedWriter writer) throws IOException {
		Stack<Cell> drum = new Stack<Cell>();
		Cell pas = oCell;
		while (pas != iCell) {
			drum.push(pas);
			pas = pas.getParinte();
		}
		drum.push(iCell);

		writer.write(drum.size() + "");
		writer.newLine();
		while (!drum.isEmpty()) {
			Cell c = drum.pop();
			writer.write(c.getLinie() + " " + c.getColoana());
			writer.newLine();
		}

	}

}
