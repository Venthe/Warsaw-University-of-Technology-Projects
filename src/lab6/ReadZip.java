package lab6;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class ReadZip {
	String filename;
	ArrayList<String> fileContent = new ArrayList<String>();

	public ReadZip(String filename) {
		this.filename = filename;
	}

	public void unzip() {
		try {
			ZipInputStream file = new ZipInputStream(new BufferedInputStream(
					new FileInputStream(filename)));
			ZipEntry entry;
			while ((entry = file.getNextEntry()) != null) {
				byte[] bytes = new byte[(int) entry.getSize()];
				file.read(bytes, 0, bytes.length);
				String strUnzipped = new String(bytes, "UTF-8");
				fileContent.add(strUnzipped);
			}
			file.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void display() {
		for (int i = 0; i < fileContent.size(); i++) {
			System.out.println(fileContent.get(i));
		}
	}

	public ArrayList<String> parse() {
		ArrayList<String> sent = new ArrayList<String>();
		for (int i = 0; i < fileContent.size(); i++) {
			String[] result = fileContent.get(i).split("\n|\\.(?!\\d)|(?<!\\d)\\.");
			for(int j=0;j<result.length;j++){
				if(result[j].contains("mind")){
					sent.add(result[j]);
				}
			}
		}
		return sent;
	}
}
