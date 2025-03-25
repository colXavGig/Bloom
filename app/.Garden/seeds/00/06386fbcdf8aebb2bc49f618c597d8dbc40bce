package main;
import calculatrice.calculatrice;
import java.util.Scanner;
public class Main {

	public static void main(String[] args) {
	calculatrice calc;
	Scanner scanner=new Scanner(System.in);
	int session=1;
	while (session==1) {
		System.out.print("calculatrice William\n");
		System.out.print("premier chiffre: \n");
		double x=scanner.nextDouble();
		System.out.print("deuximeme chiffre:\n");
		double y=scanner.nextDouble();
		
		calc= new calculatrice(x,y);
		
		System.out.print("choisir operation:\n");
		try {
			System.out.print(calc.ChooseOperation(scanner.next())+"\n");
		} catch (Exception e) {
			System.out.print("invalide operation:\n");
		}
		System.out.print("voulez-vous continuer?:\n");
		String input=scanner.next();
		if(input=="no")session=0;
		else {session=1;}
	}
	scanner.close();
	}
	
}
