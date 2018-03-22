//package tema1;
/**
 * clasa ce extinde un proces si implementeaza metoda work in mod corespunzator
 * 
 * @author alexpeti
 *
 */
public class Sqrt extends Proces {

	public Sqrt() {
		name = "Sqrt";
	}
	/**
	 * intoarce partea intreaga a radicalului
	 */
	int work(int number){
		number = Math.abs(number);
		return (int)Math.sqrt(number);
	}

}
