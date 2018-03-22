//package tema2POO;

/**
 * Interfata care prezinta pentru fiecare tip de nod o metoda specifica de
 * vizitare care este implementata in clasa CalculatorVisitor
 * 
 * @author alexpeti
 *
 */
public interface IVisitor {

	boolean visit(AndNode operatorNode, String name, double value);

	boolean visit(OrNode operatorNode, String name, double value);

	boolean visit(OperandNode operandNode, String name, double value);
}
