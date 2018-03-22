//package tema1;

/**
 * 
 * @author alexpeti
 *
 */
class WeightedScheduler extends Scheduler {

	WeightedScheduler() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * 
	 * @param s
	 *            = structura in care se pastreaza procesele si cotele acestora
	 * @return un vector de inturi in care sunt tinute cotele proceselor
	 */
	int[] umpleCote(ProcessStructure[] s) {
		int n = s.length;
		int[] cote = new int[n];
		for (int i = 0; i < n; i++) {
			cote[i] = s[i].getWeight();
		}

		return cote;
	}

	/**
	 * 
	 * @param numbers
	 *            vector de numere
	 * @return cel mai mare divizor comun al lor
	 */
	static int gcd(int[] numbers) {
		int gcd = numbers[0];
		for (int i = 1; i < numbers.length; i++) {
			gcd = euclidGcd(gcd, numbers[i]);
		}
		return gcd;
	}

	/**
	 * 
	 * @param num1
	 *            = primul numar
	 * @param num2
	 *            = al doilea numar
	 * @return cel mai mare divizor comun al lor
	 */
	static int euclidGcd(int num1, int num2) {
		if (num2 == 0) {
			return num1;
		} else {
			return euclidGcd(num2, num1 % num2);
		}
	}

	/**
	 * populez vectorul, aleg tipul de cache, populez vectorul in care imi mentin
	 * cotele calculez ccmd pentru cote. Rulez fiecare proces de numarul indicat de
	 * cote
	 */

	void cache(ProblemData obiect, HomeworkWriter out) {
		Proces[] proces = new Proces[obiect.getProcesses().length];
		umpleVectorul(proces, obiect.getProcesses());
		FactoryCache fact = new FactoryCache();
		Cache ch = fact.create(obiect.getCacheType());
		int[] cote = umpleCote(obiect.getProcesses());
		int gcd = gcd(cote);
		ch.genereaza(obiect.getCacheCapacity());
		int j = 0, contor, i = 0;

		while (true) {
			contor = 0;
			while (contor < cote[j] / gcd) {
				if (i < obiect.getNumbersToBeProcessed().length) {
					ch.prelucreaza(obiect, proces, i, j, out);
					i++;
					contor++;

				} else {
					return;
				}

			}
			j = (j + 1) % cote.length;
		}

	}

}
