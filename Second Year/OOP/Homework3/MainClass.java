import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

/**
 * construiesc pentru fiecare task labirintul si apoi instantiez in functie de
 * task, clasa specifica
 * 
 * @author alexpeti
 *
 */
class MainClass {
	public static void main(String[] args) throws IOException {

		String inFile = args[1];
		String fileName = args[2];
		File text = new File(inFile);
		BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));

		Maze labirint = new Maze();

		if (args[0].equals("1")) {
			Task1 task1 = new Task1();
			task1.task1(labirint.getMaze(text), writer);
		} else {
			Task2 task2 = new Task2();
			task2.leeAlg(labirint.getMaze2(text), writer);
		}

		writer.close();
	}
}
