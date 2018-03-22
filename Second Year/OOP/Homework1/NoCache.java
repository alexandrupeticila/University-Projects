//package tema1;

/**
 * Clasa este folosita pentru NoCache
 * 
 * @author alexpeti
 *
 */
class NoCache extends Cache {

	public NoCache() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * nu generez niciun tip de cache
	 */
	void genereaza(int nr) {

	};

	/**
	 * Metoda calculeaza pentru fiecare input procesul dat de sheduler si afiseaza
	 * 
	 * @param obiect
	 *            = structura in care retin inputul primit
	 * @param proces=
	 *            vectorul in care retin obiecte ale proceselor citite pentru a le
	 *            putea folosi
	 * @param i
	 *            = contorul cu care ma plimb prin inputurile primite pentru care
	 *            trebuie sa aplic unul dintre procese
	 * @param index
	 *            = pozitia din vectorul de procese
	 * @param out
	 *            = fisierul in care scriu
	 */
	void prelucreaza(ProblemData obiect, Proces[] proces, int i, int index, HomeworkWriter out) {
		out.println(obiect.getNumbersToBeProcessed()[i] + " " + proces[index].name + " "
				+ proces[index].work(obiect.getNumbersToBeProcessed()[i]) + " Computed");
	};

}
