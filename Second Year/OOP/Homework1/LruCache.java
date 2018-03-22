//package tema1;

import java.util.ArrayList;

/**
 * clasa folosita pentru LRU in care imi generez structura pentru cacheul de tip
 * lru si apoi prelucrez informatia primita unitlizand si structurile generate
 * 
 * @author alexpeti
 *
 */
class LruCache extends Cache {

	public LruCache() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * lruResult = vector in care tin rezultatele proceselor deja calculate lru =
	 * arrayList de structuri de tip Lru in care introduc procesele pentru care
	 * calculez valorile si unde caut inainte de a calcula un nou proces care
	 * probabil a mai fost pe acelasi input obj = un obiect de tip lruStructure pe
	 * care il initializez cu procesul si inputul primit si verific daca exista deja
	 * in cache
	 */
	int lruResult[];
	ArrayList<LruStructure> lru;
	LruStructure obj;

	/**
	 * metoda genereaza un arrayList de structuri de tip lru si un vector in care
	 * tin rezultatele
	 * 
	 * @param number
	 *            = dimensiunea cacheului
	 */
	void genereaza(int number) {
		lru = new ArrayList<LruStructure>(number);
		lruResult = new int[number];
	}

	/**
	 * metoda imi cauta obiectul initiat cu proces[index] si i in cache. Daca il
	 * gaseste verific pozitia. Daca este ultimul element din lista doar nu afiseza
	 * valoare din vectorul de rezultate. Daca este pe alta pozitie,retin
	 * rezultutatul in aux, shiftez vectorul si arrayListul de structuri la stanga
	 * cu 1 pornind de la pozitia unde il gasesc(pastrata in variabila j. Daca nu il
	 * gasesc si lista nu e plina il adaug la final, altfel shiftez totul cu o
	 * unitate la stanga si il adaug la final.
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
		obj = new LruStructure(proces[index].name, obiect.getNumbersToBeProcessed()[i]);
		boolean apare = false;
		int j; // verificam daca apare
		for (j = 0; j < lru.size(); j++) {
			if (lru.get(j).procesName.equals(obj.procesName)) {
				if (lru.get(j).inputNr == obj.inputNr) {
					apare = true;
					break;
				}
			}
		}
		if (apare) {

			if (j == lru.size() - 1) { // pe ultima poz
				out.println(obiect.getNumbersToBeProcessed()[i] + " " + proces[index].name + " " + lruResult[j]
						+ " FromCache");
			} else {

				int aux = lruResult[j];
				for (int k = j; k < lru.size() - 1; k++) {
					lru.set(k, lru.get(k + 1));
					lruResult[k] = lruResult[k + 1];

				}
				lru.set(lru.size() - 1, obj);
				lruResult[lru.size() - 1] = aux;
				out.println(obiect.getNumbersToBeProcessed()[i] + " " + proces[index].name + " "
						+ lruResult[lru.size() - 1] + " FromCache");
			}
		} else {

			if (lru.size() == obiect.getCacheCapacity()) { // e plina lista
				for (int k = 1; k < lru.size(); k++) {
					lruResult[k - 1] = lruResult[k];
				}
				lru.remove(0);
				lru.add(obj);

				lruResult[lru.size() - 1] = proces[index].work(obiect.getNumbersToBeProcessed()[i]);
				out.println(obiect.getNumbersToBeProcessed()[i] + " " + proces[index].name + " "
						+ lruResult[lru.size() - 1] + " Computed");

			} else { // nu e plina

				lru.add(obj);
				lruResult[lru.size() - 1] = proces[index].work(obiect.getNumbersToBeProcessed()[i]);
				out.println(obiect.getNumbersToBeProcessed()[i] + " " + proces[index].name + " "
						+ lruResult[lru.size() - 1] + " Computed");

			}

		}
	}

}
