//package tema1;

/**
 * 
 * @author alexpeti
 *
 */

class MainClass {

	public static void main(String[] args) {
		/**
		 * citesc fisierul,deschid fisierul de output. Se alege Schedulerul, se apeleaza
		 * metoda care prelucreaza datele,apoi se inchid cele doua fisiere.
		 */
		HomeworkReader in = new HomeworkReader(args[0]);
		HomeworkWriter out = new HomeworkWriter(args[1]);
		ProblemData first = in.readData();
		FactoryScheduler f = new FactoryScheduler();
		Scheduler sh = f.create(first.getSchedulerType());
		sh.cache(first, out);
		in.close();
		out.close();
	}
}
