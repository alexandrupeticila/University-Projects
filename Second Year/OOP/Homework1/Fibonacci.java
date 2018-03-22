//package tema1;
/**
 * clasa ce extinde un proces si implementeaza metoda work in mod corespunzator
 * @author alexpeti
 *
 */

public class Fibonacci extends Proces {

	
	public Fibonacci() {
		name = new String("Fibonacci");
	}
	/**
	 * intoarce elementul de pe pozitia number din sirul lui fibonacci
	 */
	int work(int number) {
		if(number < 0) return -1;
		int first = 0,second = 1,rez = 0;
		if(number == 0 || number == 1) return number;
		else {
				for(int i = 2; i <= number; i++) {
				rez = first+second;
				first = second;
				second = rez%9973;
				rez = rez%9973 ;
				}
			}
	
		
		return rez;
	}

}
