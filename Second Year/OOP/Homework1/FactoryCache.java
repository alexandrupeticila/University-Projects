//package tema1;

/**
 * clasa folosita pentru a crea pe baza unui string primit, obiectul cache
 * corespunzator
 * 
 * @author alexpeti
 *
 */
class FactoryCache {

	public FactoryCache() {
		// TODO Auto-generated constructor stub
	}

	Cache ch;

	 Cache create(String s) {
		if (s.equals("NoCache")) {
			ch = new NoCache();
		} else {
			if (s.equals("LfuCache")) {
				ch = new LfuCache();
			} else {
				ch = new LruCache();
			}
		}

		return ch;

	}

}
