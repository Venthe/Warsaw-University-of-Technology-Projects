package console;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Scanner;

public class ReadPupils {
	private final Path fileName;
	public ArrayList<Pupil> pupils = new ArrayList<Pupil>();
	
	public void display(){
		for(int i=0;i<pupils.size();i++){
			System.out.println(pupils.get(i).toString());
		}
	}

	public ReadPupils(String aFileName) {
		fileName = Paths.get(aFileName);
	}

	public final void processLineByLine() throws IOException {
		try (Scanner scanner = new Scanner(fileName, "UTF-8")) {
			while (scanner.hasNextLine()) {
				processLine(scanner.nextLine());
			}
		}
	}
	public void dumpByStartingLetter() throws FileNotFoundException, UnsupportedEncodingException{
		//Make a copy of ArrayList pupils
		//first sort by first letter, then open and close by letters. Coming too late took it's toll :)
		//Sort with custom comparator as in previous assignments.
		for(int i=0;i<pupils.size();i++){
			if(true){ //Not enough time. Also, there would be an append here, with another loop giving i++
				PrintWriter writer = new PrintWriter(pupils.get(i).getFirstLetter()+".txt", "UTF-8");
				writer.println(pupils.get(i).dump());
				writer.close();
			}
		}
	}

	protected void processLine(String line) {
		Scanner scanner = new Scanner(line);
		scanner.useDelimiter(",");
		if (scanner.hasNext()) {
			String name = scanner.next();
			String inputValue = scanner.next();
			int value = Integer.parseInt(inputValue);
			pupils.add(new Pupil(name, value));
			System.out.println(name + " " + value);
		} else {
		}
		scanner.close();
	}
}