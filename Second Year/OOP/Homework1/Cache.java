//package tema1;

/**
 * Clasa cache este una abstracta si extinsa de cele doua tipuri de
 * cache+noCache ea imi genereaza structura folosita petru cache si prelucreaza
 * inputul primit
 * 
 * @author alexpeti
 *
 */

public abstract class Cache {
	/**
	 * obiect = structura in care retin inputul primit proces= vectorul in care
	 * retin obiecte ale proceselor citite pentru a le putea folosi i = contorul cu
	 * care ma plimb prin inputurile primite pentru care trebuie sa aplic unul
	 * dintre procese index = pozitia din vectorul de procese out = fisierul in care
	 * scriu
	 */

	ProblemData obiect;
	Proces[] proces;
	int i, index;
	HomeworkWriter out;

	public Cache() {
	}

	/**
	 * metoda imi genereaza structurile folosite pentru cache mai exact,un arrayList
	 * de lru/lfuStructure si un vector asociat acesteia in care pastrez rezultatele
	 * 
	 * @param nr
	 *            = dimensiunea cacheului
	 */
	abstract void genereaza(int nr);

	/**
	 * metoda prelucreaza in functie de tipul cache.ului
	 * 
	 * @param obiect
	 *            structura in care retin inputul primit
	 * @param proces=
	 *            vectorul in care retin obiecte ale proceselor citite pentru a le
	 *            putea folosi
	 * @param i
	 *            contorul cu care ma plimb prin inputurile primite pentru care
	 *            trebuie sa aplic unul dintre procese
	 * @param index
	 *            pozitia din vectorul de procese
	 * @param out
	 *            fisierul in care scriu
	 */
	abstract void prelucreaza(ProblemData obiect, Proces[] proces, int i, int index, HomeworkWriter out);

}
