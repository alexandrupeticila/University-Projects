//package tema1;

/**
 * clasa folosita pentru a crea pe baza unui string, un obiect scheduler
 * corespunzator
 * 
 * @author alexpeti
 *
 */
public class FactoryScheduler {
	Scheduler sh;

	public FactoryScheduler() {
		// TODO Auto-generated constructor stub
	}

	public Scheduler create(String s) {
		if (s.equals("RandomScheduler")) {
			sh = new RandomSheduler();
		} else {
			if (s.equals("RoundRobinScheduler")) {
				sh = new RoundRobinScheduler();
			} else {
				sh = new WeightedScheduler();
			}
		}

		return sh;

	}

}
