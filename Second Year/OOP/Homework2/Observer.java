//package tema2POO;

import java.text.DecimalFormat;
import java.util.*;

/**
 * Clasa care are rolul de a defini instante pentru fiecare observator
 * 
 * @author alexpeti
 *
 */
public class Observer {

	private Subject subject;
	int number; // nr observatorului
	private static DecimalFormat df = new DecimalFormat("#.00"); // formatul in care afisez
	String expresie;
	TreeMap<String, FeedStructure> feeduri = new TreeMap<String, FeedStructure>(); // tin ultima valoare pentru fiecare

	/**
	 * Constructorul seteaza campurile subject si number cu parametrii primiti
	 * 
	 * @param subject
	 *            subiectul de care apartine
	 * @param number
	 *            idul observatorlui
	 */
	Observer(Subject subject, int number) {
		this.subject = subject;
		this.number = number;
		this.subject.attach(this); // adaug obs in lista de observeri

	}

	/**
	 * Adaug un nou feed in Treemapul feeduri sau actualizez informatiile acestuia,
	 * daca exista deja un element din acel stoc
	 * 
	 * @param name
	 *            numele feedului
	 * @param value
	 *            valoarea feedului
	 */
	void update(String name, double value) {
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
			feed.lastValue = 0.00;
			feeduri.put(name, feed);
		}

	}

	/**
	 * Metoda imi construieste urmand algoritmul arborele de expresie. Astfel, mai
	 * intai iau cate un nod din cele trei tipuri posibile si noua noduri pe care le
	 * voi folosi ca noduri copii. Pentru fiecare element din lista fac o compratie
	 * si creez un nod corespunzator apoi, daca este nod frunza il pun pe stiva,
	 * daca nu scot ultimele doua noduri de pe stiva si le folosesc pentru a face
	 * legaturile cu nodul curent. La final scot nodul ultimul nod din stiva si il
	 * returnez
	 * 
	 * @param s
	 *            expresia postfixata sub forma de ArrayList
	 * @return nodul root din arborele de expresie
	 */
	static Node constructTree(ArrayList<String> s) {
		Stack<Node> stack = new Stack<>();
		AndNode and;
		OrNode or;
		OperandNode op;
		Node n1, n2;

		for (int i = 0; i < s.size(); i++) {
			String current = s.get(i);
			if (!current.equals("||") && !current.equals("&&")) {
				op = new OperandNode(current);
				stack.push(op);
			} else if (current.equals("&&")) {
				n1 = stack.pop();
				n2 = stack.pop();

				and = new AndNode(n2, n1);
				stack.push(and);
			} else if (current.equals("||")) {
				n1 = stack.pop();
				n2 = stack.pop();

				or = new OrNode(n2, n1);
				stack.push(or);
			}
		}
		n1 = stack.pop();

		return n1;
	}

	/**
	 * Metoda print imi afiseaza informatii despre toate stocurile unui observator
	 * conform cerintei. Astfel, am ales sa folosesc doua cazuri, atunci cand am
	 * expresie si atunci cand nu am.Cand nu am, verific campul lastValue care este
	 * setata cu valoare de la ultima afisare. Daca este 0, este prima afisare si
	 * fluctuatia este 0. Daca nu, o calulez folosind formula, iar apoi afisez
	 * informatiile pentru fiecare stoc in forma ceruta. Daca avem expresi, creez
	 * mai intai expresia postfixata, apoi fac mici modificari (aduag, sterg
	 * spatii), dupa care creez arborele de expresie, mai exact nodul root folosindu
	 * ma de expresia sub forma de lista. Dupa accea, pentru fiecare stoc vizitez
	 * nodul root si verific astfel daca respecta sau nu conditia, iar daca o
	 * respecta afisez informatiile in mod simular cazului fara expresie.
	 */
	public void print() {

		if (expresie.equals(" nil")) {
			for (Map.Entry<String, FeedStructure> entry : feeduri.entrySet()) {
				double procent;
				if (entry.getValue().lastValue == 0) {
					procent = 0;
				} else {
					procent = -(100 - 100 * entry.getValue().value / entry.getValue().lastValue);

				}
				if (procent == -0)
					procent = 0;

				System.out.println("obs " + number + ": " + entry.getKey() + " " + df.format(entry.getValue().value)
						+ " " + String.format("%.2f", procent) + "% " + entry.getValue().count / 2);

				entry.getValue().count = 0;
				entry.getValue().lastValue = entry.getValue().value;
			}
			return;
		}

		ShuntingYard exp = new ShuntingYard();
		expresie = expresie.replace(")", " ) ");
		expresie = expresie.replace("(", " ( ");
		expresie = expresie.replaceAll("\\s{2,}", " ");
		expresie = expresie.replaceFirst("^ *", "");
		ArrayList<String> arr = exp.changeStructure(exp.postfix(expresie));
		Node root = constructTree(arr);
		CalculatorVisitor visitor = new CalculatorVisitor();

		for (Map.Entry<String, FeedStructure> entry : feeduri.entrySet()) {
			boolean respecta = false;

			// verific ce tip de nod este si il vizitez
			if (root instanceof OperandNode) {
				respecta = visitor.visit((OperandNode) (root), entry.getValue().name, entry.getValue().value);
			} else if (root instanceof OrNode) {
				respecta = visitor.visit((OrNode) root, entry.getValue().name, entry.getValue().value);
			} else if (root instanceof AndNode) {
				respecta = visitor.visit((AndNode) root, entry.getValue().name, entry.getValue().value);
			}

			if (respecta) {
				double procent;
				if (entry.getValue().lastValue == 0) {
					procent = 0;
				} else {
					procent = -(100 - 100 * entry.getValue().value / entry.getValue().lastValue);
				}

				if (procent == -0)
					procent = 0;
				System.out.println("obs " + number + ": " + entry.getKey() + " " + df.format(entry.getValue().value)
						+ " " + String.format("%.2f", procent) + "% " + entry.getValue().count / 2);

				entry.getValue().count = 0;
				entry.getValue().lastValue = entry.getValue().value;
			}
		}
	}
}