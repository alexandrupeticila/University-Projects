//package tema1;

/**
 * clasa folosita pentru a crea pe baza unui string, un obiect proces
 * corespunzator
 * 
 * @author alexpeti
 *
 */
class FactoryProcess {
	Proces ch;

	public FactoryProcess() {
		// TODO Auto-generated constructor stub
	}

	public Proces create(String name) {
		if (name.equals("CheckPrime")) {
			ch = new CheckPrime();
		}

		if (name.equals("NextPrime")) {
			ch = new NextPrime();
		}

		if (name.equals("Fibonacci")) {
			ch = new Fibonacci();
		}

		if (name.equals("Sqrt")) {
			ch = new Sqrt();
		}

		if (name.equals("Square")) {
			ch = new Square();
		}

		if (name.equals("Cube")) {
			ch = new Cube();
		}

		if (name.equals("Factorial")) {
			ch = new Factorial();
		}
		return ch;
	}

}
