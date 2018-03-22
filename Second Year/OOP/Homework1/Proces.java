//package tema1;

/**
 * Clasa este folosita pentru a construi cele 7 tipuri de procese ea contine un
 * camp ce semnifica numele proceselui
 * 
 * @author alexpeti
 *
 */
abstract class Proces {
	String name;

	/**
	 * 
	 * @param number
	 *            = numarul care urmeaza a fi prelucrat de proces
	 * @return rezultatul procesului pe inputul primit
	 */
	abstract int work(int number);

}
