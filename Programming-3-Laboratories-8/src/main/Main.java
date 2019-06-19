package main;

import javax.swing.SwingUtilities;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Window wnd = new Window();
		
        SwingUtilities.invokeLater(new Runnable()
        {
            @Override
            public void run()
            {
            	wnd.display();
            }
        });
	}

}
