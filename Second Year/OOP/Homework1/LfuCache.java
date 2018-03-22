//package tema1;

import java.util.ArrayList;
/**
 * clasa folosita pentru LFU in care imi generez structura pentru cacheul de tip lru
 * si apoi prelucrez informatia primita unitlizand si structurile  generate
 * @author alexpeti
 *
 */
class LfuCache extends Cache {

	public LfuCache() {
	
	}
	
	/**
	 * lfuResult = vector in care tin rezultatele proceselor deja calculate
	 * lfu = arrayList de structuri de tip Lfu in care introduc procesele pentru care calculez valorile
	 * 		si unde caut inainte de a calcula un nou proces care probabil a mai fost pe acelasi input
	 * obj = un obiect de tip lruStructure pe care il initializez cu procesul si inputul primit
	 * 		si verific daca exista deja in cache
	 */
	int lfuResult[];
	ArrayList<LfuStructure> lfu;
	LfuStructure obj2;
	
	
	/**
	 * 
	 * @param lf = lista de elemente de tip cache in care retin si nr de aparitii al fiecarui proces pe fiecare input
	 * @return pozitia pe care gasesc elementul ce apare de un numar minim de ori
	 */
	static int min(ArrayList<LfuStructure> lf) {
		int ret = lf.get(0).nraparitii;
		int index = 0;
		for(int i = 1; i < lf.size();i++ ) {
			if(lf.get(i).nraparitii < ret) {
				ret = lf.get(i).nraparitii;
				index = i;
			}
		}
		return index;
	}
	
	/**
	 * metoda genereaza un arrayList de structuri de tip lfu si un vector in care tin rezultatele
	 * @param number = dimensiunea cacheului
	 */

	void genereaza(int number) {
		lfu = new ArrayList<LfuStructure>(number);
		lfuResult = new int[number];
	}
	
	/**
	  * metoda imi cauta obiectul initiat cu proces[index] si i in cache.
	  * Daca il gaseste incrementez numarul de ori de care apare.
	  * Daca nu il gasesc si lista nu e plina il adaug la final
	  * altfel calculez minimul de aparitii si scot elementul de la pozitia respectiva din cache si il intrduc pe cel nou
	  * apoi actualizez nr de aparitii
	 * @param obiect = structura in care retin inputul primit
	 * @param proces= vectorul in care retin obiecte ale proceselor citite pentru a le putea folosi 
	 * @param i = contorul cu care ma plimb prin inputurile primite pentru care trebuie sa aplic unul dintre procese
	 * @param index = pozitia din vectorul de procese
	 * @param out = fisierul in care scriu
	 */
	void prelucreaza(ProblemData obiect, Proces[] proces, int i, int index, HomeworkWriter out) {
		obj2 = new LfuStructure(proces[index].name, obiect.getNumbersToBeProcessed()[i]);
		boolean apare = false;
		int j; // verificam daca apare
		for (j = 0; j < lfu.size() ; j++) {
			if (lfu.get(j).procesName.equals(obj2.procesName)) {
				if (lfu.get(j).inputNr == obj2.inputNr) {
					apare = true;
					break;
				}
			}
		}
		if (apare) { 
		lfu.get(j).nraparitii++;
			out.println(obiect.getNumbersToBeProcessed()[i] + " " + proces[index].name + " " + lfuResult[j]
					+ " FromCache");
		}
	 else {		//nu apare
		
		if (lfu.size() == obiect.getCacheCapacity()) { // e plina lista
			int poz = min(lfu);
			lfu.remove(poz);
			lfu.add(poz,obj2);
			lfu.get(poz).nraparitii = 1;
			lfuResult[poz] = proces[index].work(obiect.getNumbersToBeProcessed()[i]);
			out.println(obiect.getNumbersToBeProcessed()[i] + " " + proces[index].name + " " + lfuResult[poz]
					+ " Computed");

		} else { 
			
			lfu.add(obj2);
			lfuResult[lfu.size() -1 ] = proces[index].work(obiect.getNumbersToBeProcessed()[i]);
			out.println(obiect.getNumbersToBeProcessed()[i] + " " + proces[index].name + " " + lfuResult[lfu.size()-1]
					+ " Computed");
			}

	}

	
	}

}
