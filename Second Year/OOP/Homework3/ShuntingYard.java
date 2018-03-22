//package tema2POO;

import java.util.ArrayList;
import java.util.Deque;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

/**
 * Aceasta clasa prezinta doua metode folosite pentru a trece expresia primita
 * in expresie postfixata. 
 * 
 * @author alexpeti
 *
 */
public class ShuntingYard {

	private enum Operator {
		AND(1), OR(2);
		final int precedence;

		Operator(int p) {
			precedence = p;
		}
	}

	/**
	 * Hasmap in care pun cei doi operatori, AND si OR
	 * serialVersionUID e pus ca altfel imi dadea un warning.
	 */
	private static Map<String, Operator> ops = new HashMap<String, Operator>() {
		private static final long serialVersionUID = 1L;

		{
			put("&&", Operator.AND);
			put("||", Operator.OR);
		}
	};

	private static boolean isHigerPrec(String op, String sub) {
		return (ops.containsKey(sub) && ops.get(sub).precedence >= ops.get(op).precedence);
	}

	/**
	 * Am splitat stringul primit dupa spatiu si apoi am verificat fiecare element
	 * si in functie de rezultat am facut operatiile necesare.
	 * Daca elementul este o paranteza deschisa, o punem pe stiva. 
	 * Daca este paranteza inchisa, punem toate pin StringBuilder parantezele
	 * deschise pana la intalnirea unui alt element.
	 * Inainte insa verificam daca stiva este goala si ordinea operatorilor
	 * cu ajutorul metodei definite tot in aceasta clasa si in functie de rezultat
	 * punem sau nu elementul in output. 
	 * Apoi punem toate elementele care raman pe stiva in output si il convertim 
	 * la string, dupa care il returnam
	 * @param infix
	 *            expresia citita de la tastatura
	 * @return expresia postfixata prelucrata conform algoritmuluide pe wikipedia
	 */
	public String postfix(String infix) {
		StringBuilder output = new StringBuilder();
		Deque<String> stack = new LinkedList<>();

		for (String token : infix.split("\\s")) {
			// operator
			if (ops.containsKey(token)) {
				while (!stack.isEmpty() && isHigerPrec(token, stack.peek()))
					output.append(stack.pop()).append(' ');
				stack.push(token);

				// left parenthesis
			} else if (token.equals("(")) {
				stack.push(token);

				// right parenthesis
			} else if (token.equals(")")) {
				while (!stack.peek().equals("("))
					output.append(stack.pop()).append(' ');
				stack.pop();

				// expresion
			} else {
				output.append(token).append(' ');
			}
		}

		while (!stack.isEmpty())
			output.append(stack.pop()).append(' ');

		return output.toString();
	}

	/**
	 * Aceasta metoda primeste un string si mai intai il spliteaza dupa spatiu. Apoi
	 * verific elementul curent si in functie de el aleg operatia pe care o fac.
	 * Daca elementul este || sau && atunci pun elementul in lista. Daca nu, atunci
	 * folosesc un string auxiliar in care retin atat elementul curent cat si
	 * urmatoarele doua elememte din vectorul splitat, concatenandu-le si pun
	 * elementul rezultat in lista. Astfel, aceste ultime elemente vor fi folosite
	 * drept frunze in arborele de expresie.
	 * 
	 * @param input
	 *            expresia postfixata prelucrata cu ajutorul metodei de mai sus
	 * @return expresia postfixata sub forma unui ArrayList
	 */
	public ArrayList<String> changeStructure(String input) {
		ArrayList<String> exp = new ArrayList<String>();
		String[] split = input.split(" ");
		String aux;
		int i = 0;

		while (i < split.length) {
			if (split[i].equals("le") || split[i].equals("lt") || split[i].equals("ne") || split[i].equals("ge")
					|| split[i].equals("eq") || split[i].equals("gt")) {
				aux = split[i] + " " + split[i + 1] + " " + split[i + 2];
				i = i + 3;
				exp.add(aux);
				aux = "";
			} else {
				aux = split[i];
				exp.add(aux);
				aux = "";
				i++;
			}

		}
		return exp;
	}

}