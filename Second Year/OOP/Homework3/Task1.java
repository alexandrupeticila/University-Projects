import java.util.List;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;

/**
 * In aceasta clasa rezolv taskul1.
 * 
 * @author alexpeti
 *
 */
class Task1 {
	/**
	 * Aceasta metoda este folosita pentru a gasi celula initiala
	 * 
	 * @param maze
	 *            labirintul
	 * @return celula initiala
	 */
	private static ICell findICell(Cell[][] maze) {
		for (int i = 1; i < maze.length; i++) {
			for (int j = 1; j < maze[i].length; j++) {
				if (maze[i][j].getTip().equals("I")) {
					return (ICell) maze[i][j];
				}

			}
		}
		return null;
	}

	/**
	 * Aceasta metoda scrie in fisierul specific taskului 1 pozitiile prin care
	 * trece eroul in primul sau antrenament pentru a ajunge la portal
	 * 
	 * @param linii
	 *            lista liniilor prin care a trecut eroul
	 * @param coloane
	 *            lista coloanelor prin care a trecut eroul
	 * @param writer
	 *            bufferedWriterul folosit pentru a scrrie in fisier
	 * @throws IOException
	 */
	static void printare1(List<Integer> linii, List<Integer> coloane, BufferedWriter writer) throws IOException {
		writer.write(linii.size() + "");
		writer.newLine();
		for (int i = 0; i < linii.size(); i++) {
			writer.write(linii.get(i) + " " + coloane.get(i));
			writer.newLine();
		}
	}

	/**
	 * Aceasta metoda se ocupa de primul antrenament. Caut mai intai celula de
	 * plecare, dupa care introduc linia si coloana acesteia in cele doua liste cu
	 * ajutorul carora voi pastra pozitiile prin care trece eroul, valori cu care
	 * initializez si linia si coloana curenta. Cat timp nu gasesc portalul, voi
	 * vizita cei 4 vecini ai celulei curente. In functie de directia acesteia, voi
	 * seta fiecarui vecin pozitia. Apoi voi introduce intr-o lista doar celule
	 * valabile, generand exceptii acolo unde este cazul. Dupa accea, cu ajutorul
	 * comparatorului ordonez lista de vecini in ordinea ceruta de task si mut eroul
	 * in prima celula din lista. Nu verific cazul in care nu exitsa nici o celula
	 * in lista deoarece cerinta asigura ca va exista cel putin un drum. Dupa accea
	 * voi actualiza directia celulei pe care mut eroul in functie de directie
	 * celulei precedenta si de pozitia celei noi. Ma opresc cand voi gasi portalul
	 * de iesire, cand voi scrie in fisier toate pozitiile prin care a trecut eroul.
	 * De fiecare data incrementez nr de pietre si adaug in liste pozitia.
	 * 
	 * @param maze
	 *            labirintul
	 * @param writer
	 *            BufferedWriterul folosit pentru a scrie in fisier
	 * @throws IOException
	 */
	void task1(Cell[][] maze, BufferedWriter writer) throws IOException {

		ICell iCell = findICell(maze);

		List<Integer> linii = new ArrayList<Integer>();
		List<Integer> coloane = new ArrayList<Integer>();

		linii.add(iCell.getLinie() - 1);
		coloane.add(iCell.getColoana() - 1);

		int currentLine = iCell.getLinie();
		int currentColumn = iCell.getColoana();

		boolean portalGasit = false;

		while (!portalGasit) {
			List<Cell> celule = new ArrayList<Cell>();

			int nrVeciniVizitati = 0;
			int linieVec = currentLine;
			int coloanaVec = currentColumn;

			while (nrVeciniVizitati < 4) {

				if (nrVeciniVizitati == 0) {
					coloanaVec--;

					switch (maze[currentLine][currentColumn].getDirectie()) {
					case "UP":
						maze[linieVec][coloanaVec].setPozitie("L");
						break;
					case "DOWN":
						maze[linieVec][coloanaVec].setPozitie("R");
						break;
					case "LEFT":
						maze[linieVec][coloanaVec].setPozitie("F");
						break;
					case "RIGHT":
						maze[linieVec][coloanaVec].setPozitie("B");
						break;
					}
				} else if (nrVeciniVizitati == 1) {

					coloanaVec++;
					linieVec--;
					switch (maze[currentLine][currentColumn].getDirectie()) {
					case "UP":
						maze[linieVec][coloanaVec].setPozitie("F");
						break;
					case "DOWN":
						maze[linieVec][coloanaVec].setPozitie("B");
						break;
					case "LEFT":
						maze[linieVec][coloanaVec].setPozitie("R");
						break;
					case "RIGHT":
						maze[linieVec][coloanaVec].setPozitie("L");
						break;
					}

				} else if (nrVeciniVizitati == 2) {

					coloanaVec++;
					linieVec++;
					switch (maze[currentLine][currentColumn].getDirectie()) {
					case "UP":
						maze[linieVec][coloanaVec].setPozitie("R");
						break;
					case "DOWN":
						maze[linieVec][coloanaVec].setPozitie("L");
						break;
					case "LEFT":
						maze[linieVec][coloanaVec].setPozitie("B");
						break;
					case "RIGHT":
						maze[linieVec][coloanaVec].setPozitie("F");
						break;
					}
				} else {

					coloanaVec--;
					linieVec++;
					switch (maze[currentLine][currentColumn].getDirectie()) {
					case "UP":
						maze[linieVec][coloanaVec].setPozitie("B");
						break;
					case "DOWN":
						maze[linieVec][coloanaVec].setPozitie("F");
						break;
					case "LEFT":
						maze[linieVec][coloanaVec].setPozitie("L");
						break;
					case "RIGHT":
						maze[linieVec][coloanaVec].setPozitie("R");
						break;
					}
				}
				nrVeciniVizitati++;
				try {
					if (coloanaVec < 1 || coloanaVec > maze[0].length - 2 || linieVec < 1 || linieVec > maze.length - 2)
						throw new HeroOutOfGroundException();
					if (maze[linieVec][coloanaVec].getTip().equals("#"))
						throw new CannotMoveIntoWallsException();
					if (maze[linieVec][coloanaVec].getTip().equals("O")) {
						portalGasit = true;
						break;
					}

					celule.add(maze[linieVec][coloanaVec]);
				} catch (CannotMoveIntoWallsException e) {

				} catch (HeroOutOfGroundException e) {

				}

			}

			if (portalGasit) {

				linii.add(linieVec - 1);
				coloane.add(coloanaVec - 1);

				printare1(linii, coloane, writer);
				break;
			} else {

				Collections.sort(celule, new CellComparator());
				maze[currentLine][currentColumn].setNrPietre();

				linii.add(celule.get(0).getLinie() - 1);
				coloane.add(celule.get(0).getColoana() - 1);
				seteazaDirectia(celule.get(0), maze[currentLine][currentColumn].getDirectie());

				currentColumn = celule.get(0).getColoana();
				currentLine = celule.get(0).getLinie();

				celule.clear();
			}

		}
	}

	/**
	 * Setez directie celulei curente in functie de directia celei anterioare dar si
	 * de pozitia celei pe care ma aflu, pozitie setata anterior
	 * 
	 * @param cell
	 *            celula pe care urmeaza sa ma mut
	 * @param directie
	 *            directia celulei precedente
	 */
	private void seteazaDirectia(Cell cell, String directie) {
		String dir = null;
		switch (directie) {
		case "UP":
			switch (cell.getPozitie()) {
			case "R":
				dir = "RIGHT";
				break;
			case "L":
				dir = "LEFT";
				break;
			case "F":
				dir = "UP";
				break;
			case "B":
				dir = "DOWN";
				break;
			}
			break;
		case "DOWN":
			switch (cell.getPozitie()) {
			case "R":
				dir = "LEFT";
				break;
			case "L":
				dir = "RIGHT";
				break;
			case "F":
				dir = "DOWN";
				break;
			case "B":
				dir = "UP";
				break;
			}
			break;
		case "LEFT":
			switch (cell.getPozitie()) {
			case "R":
				dir = "UP";
				break;
			case "L":
				dir = "DOWN";
				break;
			case "F":
				dir = "LEFT";
				break;
			case "B":
				dir = "RIGHT";
				break;
			}
			break;
		case "RIGHT":
			switch (cell.getPozitie()) {
			case "R":
				dir = "DOWN";
				break;
			case "L":
				dir = "UP";
				break;
			case "F":
				dir = "RIGHT";
				break;
			case "B":
				dir = "LEFT";
				break;
			}
			break;
		}
		cell.setDirectie(dir);
	}
}
