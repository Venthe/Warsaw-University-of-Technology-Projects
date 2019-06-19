package console;

public class Pupil {
	private String name;
	private int age;
	
	Pupil(String inputName, int inputAge){
		name = inputName;
		age = inputAge;
	}
	public String toString(){
		return name+" "+age;
	}
	public char getFirstLetter(){
		return name.charAt(0);
	}
	public String dump(){
		return name+","+age;
	}
}
