import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;		

public class MainClass {

	public static void main(String[] args) throws IOException {

		String inFile = "test.in";
		String fileName = "test.out";
		File text = new File(inFile);
		BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));

		HomeworkReader input = new HomeworkReader();
		input.genereaza(text, writer);
		writer.close();

	}

}
