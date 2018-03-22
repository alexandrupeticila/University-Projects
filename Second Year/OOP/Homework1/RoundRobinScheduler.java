//package tema1;
/**
 * 
 * @author alexpeti
 *
 */
class RoundRobinScheduler extends Scheduler {

	public RoundRobinScheduler() {
		// TODO Auto-generated constructor stub
	}
/**
 * pupulez vectrul, aleg tipul de cache, si ma folosesc de un vector circular pentru a pastra
 * diferenta dintre procese de maxim o unitate
 */
	protected void cache(ProblemData obiect, HomeworkWriter out) {
		Proces[] proces = new Proces[obiect.getProcesses().length];
		umpleVectorul(proces, obiect.getProcesses());
		FactoryCache fact = new FactoryCache();
		Cache ch = fact.create(obiect.getCacheType());
		ch.genereaza(obiect.getCacheCapacity());
		for (int i = 0; i < obiect.getNumbersToBeProcessed().length; i++) {
			ch.prelucreaza(obiect, proces, i, i % proces.length, out);
		}
	}

}
