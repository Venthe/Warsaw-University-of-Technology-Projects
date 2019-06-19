package eu.venthe.project;

import eu.venthe.project.gui.Window;
import java.awt.EventQueue;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class Main {

  public static void main(String[] args)
      throws ClassNotFoundException, UnsupportedLookAndFeelException, InstantiationException, IllegalAccessException {
    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    EventQueue.invokeLater(Window::new);
  }
}
