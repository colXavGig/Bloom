package calculatrice;

public class calculatrice {
	//variable
	private double operande1;
	private double operande2;
	
	
	//constructeur
	//default constructor
	public calculatrice() {
		this.operande1=1;
		this.operande2=1;
	}
	public calculatrice(double x,double y) {
		this.setOperande1(x);
		this.setOperande2(y);
	}
	public calculatrice(calculatrice calc) {
		this.setOperande1(calc.getOperande1());
		this.setOperande2(calc.getOperande2());
	}
	
	
	
	//getter
	public double getOperande1() {
		return this.operande1;
	}
	public double getOperande2() {
		return this.operande2;
	}
	//setter
	private void setOperande1(double x) {
		this.operande1=x;
	}
	private void setOperande2(double x) {
		this.operande2=x;
	}
	
	
	//state
	@Override
	public String toString(){
		 return String.format("Operande1: %.2f  Operande2: %.2f ", this.operande1,this.operande2);
	}
	private double add() {
		return this.operande1+this.operande2;
	}
	private double sub() {
		return this.operande1-this.operande2;
	}
	private double div() {
		return this.operande1*this.operande2;
	}
	private double mult() {
		return this.operande1/this.operande2;
	}
	
	public Double ChooseOperation(String operateur) throws Exception {
		switch(operateur) {
		case"+":return add();
		case"-":return sub();
		case"*":return mult();
		case"/":return div();
		default:throw  new Exception("invalid argument pls try + = * /");
		}
	}
}
