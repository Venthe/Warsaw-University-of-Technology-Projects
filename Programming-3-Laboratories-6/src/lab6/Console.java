package lab6;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

public class Console {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		ReadZip rz = new ReadZip("novel.zip");
		rz.unzip();
		// rz.display();
		ArrayList<String> st = rz.parse();

		FileOutputStream fileOut = new FileOutputStream("new.txt");
		ObjectOutputStream out = new ObjectOutputStream(fileOut);
		for (int i = 0; i < st.size(); i++) {
			out.write(st.get(i)); //Wont print correctly
		}
		out.close();
		fileOut.close();
	}

}
