//package tema1;

//import tema1.CheckPrime;

/**
 * clasa ce extinde un proces si implementeaza metoda work in mod corespunzator
 * 
 * @author alexpeti
 *
 */
public class NextPrime extends Proces {

	public NextPrime() {
		name = "NextPrime";
	}

	/**
	 * intoarce urmatorul numar prim
	 */
	int work(int number) {
		int aux = number + 1;
		while (true) {
			Proces prim = new CheckPrime();
			if (prim.work(aux) == 1)
				break;
			aux++;
		}
		return aux;
	}

}
