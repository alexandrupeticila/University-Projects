//package tema1;

/**
 * clasa ce extinde un proces si implementeaza metoda work in mod corespunzator
 * 
 * @author alexpeti
 *
 */
class Square extends Proces {

	Square() {
		name = "Square";
	}

	/**
	 * intoarce patratul inputului
	 */
	int work(int number) {
		return number * number;
	}

}
