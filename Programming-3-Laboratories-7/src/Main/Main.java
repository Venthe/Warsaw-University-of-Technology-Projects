package Main;

import java.util.ArrayList;

public class Main {
	public static int Counter = 0;
	public static int MaxCounter = 300;

	public static void main(String[] args) {
		ArrayList<String> sa_table = new ArrayList<String>();
		for (int i = 0; i < 10; i++) {
			sa_table.add(" ");
		}
		//Last minutes, faster than creating table of AddTo... and TakeSome...
		AddToTable a1 = new AddToTable(sa_table);
		AddToTable a2 = new AddToTable(sa_table);
		AddToTable a3 = new AddToTable(sa_table);
		AddToTable a4 = new AddToTable(sa_table);
		TakeSomeFromTable b1 = new TakeSomeFromTable(sa_table,"Ala",3);
		TakeSomeFromTable b2 = new TakeSomeFromTable(sa_table,"Xce",2);
		TakeSomeFromTable b3 = new TakeSomeFromTable(sa_table,"Ufo",5);
		a1.run();
		b1.run();
		a2.run();
		b2.run();
		a3.run();
		b3.run();
		a4.run();
	}

}
