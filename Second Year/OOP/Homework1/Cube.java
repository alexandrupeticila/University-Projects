//package tema1;
/**
 * clasa ce extinde un proces si implementeaza metoda work in mod corespunzator
 * @author alexpeti
 *
 */
class Cube extends Proces {
	
	
	public Cube() {
		name = "Cube";
	}
	/**
	 * intoarce cubul inputului
	 */
	int work(int number) {
		return number*number*number;
	}

}
