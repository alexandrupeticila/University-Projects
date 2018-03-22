//package tema1;

/**
 * clasa genereaza un obiect de tip Scheduler
 * 
 * @author alexpeti
 *
 */

abstract class Scheduler {

	public Scheduler() {
	}

	static FactoryProcess f = new FactoryProcess();

	/**
	 * pentru fiecare element din vector,ne folosim de variabila f pentru a genera
	 * procesul corespunzator.
	 * 
	 * @param proces
	 *            = vectorul de procese ce urmeaza a fi populat
	 * @param proc
	 *            = structura de unde luam informatiile
	 */
	static void umpleVectorul(Proces[] proces, ProcessStructure[] proc) {
		for (int i = 0; i < proc.length; i++) {
			String name = proc[i].getType();
			proces[i] = f.create(name);
		}

	}

	/**
	 * 
	 * @param obiect
	 *            = inputul primit, citit din fisier
	 * @param out
	 *            = fisierul in care scriem
	 */
	abstract void cache(ProblemData obiect, HomeworkWriter out);

}
