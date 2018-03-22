//package tema1;

import java.util.Random;

/**
 * 
 * @author alexpeti
 *
 */
class RandomSheduler extends Scheduler {

	public RandomSheduler() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * populez vectorul,aleg tipul de cache, si apoi aleg un proces random.
	 */
	void cache(ProblemData obiect, HomeworkWriter out) {
		Proces[] proces = new Proces[obiect.getProcesses().length];
		umpleVectorul(proces, obiect.getProcesses());
		FactoryCache fact = new FactoryCache();
		Cache ch = fact.create(obiect.getCacheType());
		ch.genereaza(obiect.getCacheCapacity());
		for (int i = 0; i < obiect.getNumbersToBeProcessed().length; i++) {
			Random random = new Random();
			int index = random.nextInt(obiect.getProcesses().length);
			ch.prelucreaza(obiect, proces, i, index, out);
		}
	}

}
