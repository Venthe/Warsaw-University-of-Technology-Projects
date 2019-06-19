package main;

import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;

public class Window {
	private static JFrame frame = new JFrame("Frame");
	private static JPanel startPanel = new JPanel(new GridBagLayout());
	private static JPanel questionPanel = new JPanel(new GridBagLayout());
	private static JPanel answerPanel = new JPanel(new GridBagLayout());
	int x = 500;
	int y = 400;
	
	private void Start() {
		GridBagConstraints c = new GridBagConstraints();
		startPanel.setPreferredSize(new Dimension(x, y));
		Repaint();
		JButton start = new JButton("Start");
		c.fill = GridBagConstraints.NONE;
		start.addActionListener(new ActionListener() {
        	 
            public void actionPerformed(ActionEvent e)
            {
            	Question();
            }
        }); 
		
		startPanel.add(start, c);
	}
	
	private void Repaint(){
		frame.getContentPane().removeAll();
        frame.repaint();
		
	}
    private BufferedImage resize(BufferedImage img, int newW, int newH) {  
        int w = img.getWidth();  
        int h = img.getHeight();  
        BufferedImage dimg = new BufferedImage(newW, newH, img.getType());  
        Graphics2D g = dimg.createGraphics();  
        g.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);  
        g.drawImage(img, 0, 0, newW, newH, 0, 0, w, h, null);  
        g.dispose();  
        return dimg;  
    }  
	private void Question(){
		GridBagConstraints c = new GridBagConstraints();
		questionPanel.setPreferredSize(new Dimension(x, y));
		
    	Repaint();
    	
    	BufferedImage img = null;
    	try {
    	    img = ImageIO.read(new File("mapa.png"));
    	} catch (IOException e) {
    	    e.printStackTrace();
    	}
    	
    	ImageIcon image = new ImageIcon(resize(img,400,300));
    	
    	JLabel imageLabel = new JLabel(image);
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridwidth = 3;
    	c.gridx = 0;
        c.gridy = 0;
    	
    	questionPanel.add(imageLabel,c);
    	
    	JRadioButton btn1 = new JRadioButton("Poland");
    	JRadioButton btn2 = new JRadioButton("Germany");
    	JRadioButton btn3 = new JRadioButton("USA");
    	ButtonGroup group = new ButtonGroup();
        group.add(btn1);
        group.add(btn2);
        group.add(btn3);
        JLabel que = new JLabel("Which country is highlighted in red?");
        
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridwidth = 3;
    	c.gridx = 0;
        c.gridy = 1;

        questionPanel.add(que,c);
        c.gridwidth = 1;
    	c.gridx = 0;
        c.gridy = 2;
    	questionPanel.add(btn1,c);
    	c.gridx = 1;
    	questionPanel.add(btn2,c);
    	c.gridx = 2;
    	questionPanel.add(btn3,c);
    	btn1.addActionListener(new ActionListener() {
    	    @Override
    	    public void actionPerformed(ActionEvent event) {
    	        Answer("Congratulations!");
    	    }
    	});
    	btn2.addActionListener(new ActionListener() {
    	    @Override
    	    public void actionPerformed(ActionEvent event) {
    	    	Answer("Wrong answer");
    	    }
    	});
    	btn3.addActionListener(new ActionListener() {
    	    @Override
    	    public void actionPerformed(ActionEvent event) {
    	    	Answer("Wrong answer");
    	    }
    	});
    	
    	
        frame.setContentPane(questionPanel);
        frame.validate();
		frame.pack();
	}
	
	private void Answer(String strlabel){
		
		GridBagConstraints c = new GridBagConstraints();
		answerPanel.setPreferredSize(new Dimension(x, y));
    	Repaint();
		JLabel que = new JLabel(strlabel);
    	c.gridx = 0;
        c.gridy = 0;
		answerPanel.add(que,c);
		
		JButton start = new JButton("Again?");
		c.fill = GridBagConstraints.NONE;
		start.addActionListener(new ActionListener() {
        	 
            public void actionPerformed(ActionEvent e)
            {
            	Repaint();
                frame.getContentPane().add(startPanel);
                frame.validate();
        		frame.pack();
            }
        }); 
    	c.gridx = 0;
        c.gridy = 1;
		answerPanel.add(start, c);
        frame.setContentPane(answerPanel);
        frame.validate();
		frame.pack();
    	
	}

	public void display() {
		Start();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().add(startPanel);
		frame.pack();
		frame.setVisible(true);
	}
}
