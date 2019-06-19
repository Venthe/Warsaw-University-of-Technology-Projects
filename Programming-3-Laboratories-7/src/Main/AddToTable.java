package Main;

import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.Random;

public class AddToTable implements Runnable {
	 private SecureRandom random = new SecureRandom();

	  public String nextSessionId() {
	    return new BigInteger(130, random).toString(32);
	  }
	private Thread t;
	private String threadName = nextSessionId();
	int length = 3;
	ArrayList<String> arr;

	AddToTable(ArrayList<String> arr) {
		this.arr=arr;
		System.out.println("Creating " + threadName);
	}

	String generateRandomString() {
		String internal = "";
		Random r = new Random();
		for (int i = 0; i < length; i++) {
			char c;
			if (r.nextInt(2) == 1) {
				c = (char) (r.nextInt(26) + 'a');
			} else {
				c = (char) (r.nextInt(26) + 'A');
			}
			internal += c;
		}
		return internal;
	}

	int compareTo(String arg0, String arg1) {
		return arg0.compareTo(arg1);
	}
	
	void swapMinimum(){
		String buff = this.generateRandomString();
		int iBuff = 0;
		String sBuff = this.arr.get(0);
		int i = 0;
		for(i=0;i<this.arr.size();i++){
			if(this.compareTo(this.arr.get(i), sBuff)<0){
				sBuff=this.arr.get(i);
				iBuff = i;
			}
		}
		System.out.println(" Swapped "+this.arr.get(iBuff)+" with "+buff);
		this.arr.set(iBuff, buff);
	}

	@Override
	public void run() {
		System.out.println("Running " + threadName);
		try {
			while(true) {
				if(Main.Counter==Main.MaxCounter){
					break;
				}
				swapMinimum();
				Main.Counter++;
				Thread.sleep(2000);
				for(int i=0;i<this.arr.size();i++){
					System.out.println(this.arr.get(i));
				}
			}
		} catch (InterruptedException e) {
			System.out.println("Thread " + threadName + " interrupted.");
		}
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
