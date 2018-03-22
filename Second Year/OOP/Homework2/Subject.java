//package tema2POO;

import java.util.*;

/**
 * Clasa Subject din Observer Pattern. Aceasta contine o lista cu toti
 * observatorii dar si un TreeMap care contine ultimul feed intrat din fiecare
 * stoc, dar si informatii precum precedenta valoare afisata si numarul de
 * elemente din acel stoc. Aceasta clasa are metode specifice unei clase de tip
 * Subject.
 * 
 * @author alexpeti
 *
 */
class Subject {

	List<Observer> observers = new ArrayList<Observer>(); // lista de observatori
	TreeMap<String, FeedStructure> feeduri = new TreeMap<String, FeedStructure>(); // retin toate intrarile

	public Subject() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * Aceasta metoda introduce un feed definit de parametrii in treemap. Mai intai
	 * se face verificarea daca exista sau nu un element din acest stoc deja in
	 * treemap. Daca exista, atunci se modifica doar paramtrii in mod
	 * corespunzatori, adica se incrementeaza numarul de aparitii si se actualizeaza
	 * ultima valoare. Daca nu exista, atunci se introduce.
	 * 
	 * @param name
	 *            numele feedului
	 * @param value
	 *            valoarea feedului
	 */
	public void setState(String name, double value) {
		boolean apare = false;
		for (Map.Entry<String, FeedStructure> entry : feeduri.entrySet()) {
			if (entry.getKey().equals(name)) {
				entry.getValue().count++;
				entry.getValue().value = value;
				apare = true;
				break;
			}
		}

		if (!apare) {
			FeedStructure feed = new FeedStructure();
			feed.name = name;
			feed.value = value;
			feed.lastValue = 0.0;
			feeduri.put(name, feed);
		}
		notifyAllObservers(name, value);
	}

	/**
	 * Aceasta metoda primeste ca paramtru un observator pe care il adauga in lista.
	 * De asemenea, adaug ultimele aparitii din fiecare stoc si setez nr de aparitii
	 * la 0. Fac acest lucru pentru a putea folosi informatiile la printare cand
	 * trebuie sa afisez ultimele aparitii si inainte de crearea observatorului
	 * 
	 * @param observer
	 *            observatorul de adaugat in lisa de observatori
	 */
	public void attach(Observer observer) {
		observers.add(observer);
		for (Map.Entry<String, FeedStructure> entry : feeduri.entrySet()) {
			observer.update(entry.getValue().name, entry.getValue().value);
		}
		for (Map.Entry<String, FeedStructure> entry : observer.feeduri.entrySet()) {
			entry.getValue().count = 0;
			entry.getValue().lastValue = 0;
		}
	}

	/**
	 * Pentru fiecare observator actualizez informatiile
	 * 
	 * @param name
	 *            numele feedului
	 * @param value
	 *            valoare feedului
	 */
	public void notifyAllObservers(String name, double value) {
		for (Observer observer : observers) {
			observer.update(name, value);
		}
	}

	/**
	 * Metoda cauta observatorul in lista si afiseaza informatiile cuprinse in
	 * campul de tip TreeMap din acesta, resppectand conditiile din cerinta
	 * 
	 * @param id
	 *            numarul observatorului
	 */
	void printSub(int id) {
		for (int i = 0; i < observers.size(); i++) {
			if (observers.get(i).number == id) {
				observers.get(i).print();
				break;
			}
		}
	}

	/**
	 * Metoda folosita pentru a sterge un observator din lista
	 * 
	 * @param id
	 *            numarul observatorului
	 */
	public void remove(int id) {
		for (Observer a : observers) {
			if (a.number == id) {
				 observers.remove(observers.indexOf(a));
				observers.remove(a);
				break;
			}
		}

	}

}
