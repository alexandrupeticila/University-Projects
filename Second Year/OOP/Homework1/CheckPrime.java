//package tema1;
/**
 * clasa ce extinde un proces si implementeaza metoda work in mod corespunzator
 * @author alexpeti
 *
 */
class CheckPrime extends Proces {
	/**
	 * constructorul seteaza numele proceselui
	 */
	public CheckPrime() {
		name = "CheckPrime";
	}
	
	/**
	 * @param number = numarul care urmeaza a fi prelucrat de proces
	 * @return rezultatul procesului pe inputul primit
	 * metoda verifica daca numarul primit este sau nu prim
	 */
	int work(int number) {
		if( number < 2) return 0;
	    for(int i = 2; i < number/2 + 1;i++) {
	        if(number%i == 0)
	            return 0;
	    }
	    return 1;
	}
		
}
