import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

public class HomeworkReader {
	private static Scanner sc;
	private static int nrNoduri;
	private static int nrMuchii;
	private static int nrCulori;

	private static String formula1(int x[]) {
		String formula1 = "(";
		for (int i = 0; i < x.length; i++) {

			formula1 = formula1 + "x" + x[i] + "";
			if ((i + 1) % nrCulori == 0) {
				if (i == x.length - 1) {
					formula1 = formula1 + ")";
				} else {
					formula1 = formula1 + ")^(";
				}
			} else {
				formula1 = formula1 + "V";
			}
		}

		return formula1;
	}
	
	private static String formula2(int x[]) {
		String formula2 = "";
		
		for (int i = 0; i < x.length - 1; i++) {
			for (int j = 1; j <= (nrCulori - (i + 1) % nrCulori) % nrCulori; j++) {
				// System.out.println(x[i+j]);
				formula2 = formula2 + "^(~x" + x[i] + "V~x" + x[i + j] + ")";
			}
		}
		
		return formula2;
	}
	
	
	private static String formula3(int x[], File text) {
		String formula3 = "";
		;sc.nextLine();
		for (int i = 0; i < nrMuchii; i++) {
			int a = sc.nextInt();
			int b = sc.nextInt();

			for (int j = 0; j < nrCulori; j++) {
				formula3 = formula3 + "^(~x" + x[a * nrCulori + j] + "V~x" + x[b * nrCulori + j] + ")";
			}
		}
		
		return formula3;
	}
	public void genereaza(File text,BufferedWriter writer  ) throws IOException {
		 sc = new Scanner(text);
		nrNoduri = sc.nextInt();
		nrMuchii = sc.nextInt();
		nrCulori = sc.nextInt();

		int x[] = new int[nrNoduri * nrCulori];
		for (int i = 0; i < x.length; i++) {
			x[i] = i;
		}

		writer.write(formula1(x)+formula2(x)+formula3(x, text));
		
	}


}
