/**
 * Clasa care implementeaza o celula de tip portal, de iesire
 * 
 * @author alexpeti
 *
 */
class OCell extends Cell {
	private int linie;
	private int coloana;
	private int nrPietre = 0;
	private String tip = "";
	private String pozitie = "";
	private String directie = "";

	private Cell parinte;

	public OCell(String el) {
		tip = el;
	}

	@Override
	public void setNrPietre() {
		nrPietre++;
	}

	@Override
	public int getNrPietre() {
		return nrPietre;
	}

	@Override
	public void setDirectie(String directie) {
		this.directie = directie;
	}

	@Override
	public String getDirectie() {
		return this.directie;
	}

	@Override
	public String getTip() {
		return this.tip;
	}

	@Override
	public void setPozitie(String pos) {
		this.pozitie = pos;
	}

	@Override
	public String getPozitie() {
		return this.pozitie;
	}

	@Override
	public void setLinieColoana(int linie, int coloana) {
		this.linie = linie;
		this.coloana = coloana;
	}

	@Override
	public int getLinie() {
		return this.linie;
	}

	@Override
	public int getColoana() {
		return this.coloana;
	}

	@Override
	public void setParinte(Cell parinte) {
		this.parinte = parinte;
	}

	@Override
	public Cell getParinte() {
		return parinte;
	}
}