//package tema1;

/**
 * clasa ce extinde un proces si implementeaza metoda work in mod corespunzator
 * 
 * @author alexpeti
 *
 */
class Factorial extends Proces {

	public Factorial() {
		name = new String("Factorial");
	}

	/**
	 * intoarce factorialul inputului
	 */
	int work(int number) {
		int i, rez = 1;
		if (number < 0) {
			return 0;
		}
		if (number == 0 || number == 1)
			return 1;

		for (i = 1; i <= number; i++) {
			rez = rez % 9973;
			rez = rez * i % 9973;
		}

		return rez;
	}

}
