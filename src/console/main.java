package console;

import java.io.IOException;

public class main {

	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
		ReadPupils parser = new ReadPupils("./PupilsB.txt");
	    parser.processLineByLine();
	    parser.dumpByStartingLetter();
	}

}
