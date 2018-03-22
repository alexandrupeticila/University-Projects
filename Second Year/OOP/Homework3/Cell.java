/**
 * Clasa abstracta Cell defineste o celula din labirint, in care retin mai multe
 * informatii, unele utile pentru taskul 1, altele pentru cel de-al doilea.
 * Pentru toate aceste informatii am folosit gettere pentru a le accesa si
 * settere pentru a obtine valoarea. Aceasta este o clasa abstracta, iar toate 
 * metodele au fost definite in fiecare celula, unele dintre ele depinzand de tipul
 * celulei, insa dunctionalitatea este cea explicata in aceasta clasa.
 * 
 * @author alexpeti
 *
 */
abstract class Cell {
	/**
	 * TASK 1
	 * linie = linia din matrice;
	 * coloana = coloana din matrice;
	 * nrPietre = intuitiv,nr de pietre de pe celula, de cate ori a fost vizitata;
	 * tip = tipul celulei, zid "#", celula libera ".", etc.
	 * pozitie = folosita pentru a seta pozitia(RIGHT, LEFT, FRONT, BACK) vecinilor
	 * 			 in functie de celula pe care ne aflam si de directia(>,<,UP, DOWN )
	 * 			 acesteia.
	 * directia = directia eroului cand se afla pe aceasta celula
	 * 
	 * 
	 * TASK2
	 * parcurs = daca celula a fost sau nu vizitata
	 * parinte = pastram legatura pentru refacerea drumului
	 */
	private int linie;
	private int coloana;
	private int nrPietre = 0;
	private String tip;
	private String pozitie;
	private String directie;


	boolean parcurs;
	private Cell parinte;

	/**
	 * seteaza celula parinte
	 * 
	 * @param parent
	 *            celula parinte, anterior vizitata
	 */
	public abstract void setParinte(Cell parent);

	/**
	 * 
	 * @return celula parinte
	 */
	public abstract Cell getParinte();

	/**
	 * incrementeaza nr de pietre
	 */
	public abstract void setNrPietre();

	/**
	 * 
	 * @return nr de pietre
	 */
	public abstract int getNrPietre();

	/**
	 * seteaza orientarea eroului
	 * 
	 * @param directie
	 *            directia de orientare a eroului
	 */
	public abstract void setDirectie(String directie);

	/**
	 * 
	 * @return directia de orientare a eroului
	 */
	public abstract String getDirectie();

	/**
	 * 
	 * @return tipul celului, zid "#", libera ".", etc
	 */
	public abstract String getTip();

	/**
	 * seteaza pozitia fata de celula pe care se afla eroul, in functie de
	 * orientarea acestuia
	 * 
	 * @param pos
	 *            pozitia celului
	 */
	public abstract void setPozitie(String pos);

	/**
	 * 
	 * @return pozitia celului
	 */
	public abstract String getPozitie();

	/**
	 * seteaza linia si coloana celulei din labirint
	 * 
	 * @param linie
	 *            linia
	 * @param coloana
	 *            coloana
	 */
	public abstract void setLinieColoana(int linie, int coloana);

	/**
	 * 
	 * @return linia
	 */
	public abstract int getLinie();

	/**
	 * 
	 * @return coloana
	 */
	public abstract int getColoana();

}
