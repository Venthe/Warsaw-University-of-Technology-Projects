package Main;

import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.ArrayList;

public class TakeSomeFromTable implements Runnable{
	private SecureRandom random = new SecureRandom();

	  public String nextSessionId() {
	    return new BigInteger(130, random).toString(32);
	  }
	private Thread t;
	private String threadName = nextSessionId();
	ArrayList<String> arr;
	String input;
	int input2;
	int counter=0;
	TakeSomeFromTable(ArrayList<String> arr,String input, int input2){
		this.arr=arr;
		this.input=input;
		this.input2=input2;
	}
	@Override
	public void run() {
		System.out.println("Running " + threadName);
		try {
			while(true) {
				if(counter==input2||Main.Counter==Main.MaxCounter){
					break;
				}
				for(int i=0;i<this.arr.size();i++){
					if(input==this.arr.get(i)){
						System.out.println("String "+input+" has been replaced with \" \"");
						this.arr.set(i," ");
						Main.Counter++;
						counter++;
					}
				}
				Thread.sleep(0); //Faster than deleting trycatch copied from other class
			}
		} catch (InterruptedException e) {
			System.out.println("Thread " + threadName + " interrupted.");
		}
		System.out.println("String "+input+" has been replaced "+counter+" times.");
		System.out.println("Thread " + threadName + " exiting.");
	}

	public void start() {
		System.out.println("Starting " + threadName);
		if (t == null) {
			t = new Thread(this, threadName);
			t.start();
		}
	}
}
