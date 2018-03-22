//package tema2POO;

import java.util.*;

/**
 * 
 * @author alexpeti
 *
 */
public class MainClass {
	/**
	 * citesc de la tastatura pana ajung la "end" si in functie de stringul citit
	 * fac operatiile necesare. Si anume, creez, sterg un observator, afisez
	 * informatii despre aceste sau introduc un feed in Subject.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		String curent = sc.next();
		Subject subject = new Subject();

		while (!curent.equals("end")) {

			if (curent.equals("create_obs")) {
				Observer obs = new Observer(subject, sc.nextInt());
				subject.attach(obs);
				String aux = sc.nextLine();
				obs.expresie = aux;
			}

			if (curent.equals("feed")) {
				String name = sc.next();
				Double id = sc.nextDouble();
				subject.setState(name, id);
			}

			if (curent.equals("delete_obs")) {
				subject.remove(sc.nextInt());
			}

			if (curent.equals("print")) {
				subject.printSub(sc.nextInt());
			}

			curent = sc.next();

		}

		sc.close();
	}
}
