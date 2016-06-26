package lab3Project;

import java.awt.Dimension;
import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.JTabbedPane;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.GroupLayout;
import javax.swing.GroupLayout.Alignment;
import javax.swing.LayoutStyle.ComponentPlacement;
import javax.swing.WindowConstants;

import java.awt.event.ActionEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.Color;

import javax.swing.UIManager;

import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FilenameFilter;
import java.util.ArrayList;

import javax.swing.JComboBox;
import javax.swing.DefaultComboBoxModel;
import javax.swing.ImageIcon;
import javax.swing.JScrollPane;
import javax.swing.JEditorPane;
import javax.swing.border.SoftBevelBorder;
import javax.swing.border.BevelBorder;
import javax.swing.BoxLayout;

import java.awt.Component;

import javax.swing.Box;

import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

// Notes
// All images will be grayscale
// You will use library-based functionalities to handle images, you do not need to code your own image processing libraries.

// Merging
// Merging shall be recursive. (((1&2)&3)&4)
// Pairs of files from folders
// Precision of better formats

//rotation
//Before we do the merge let the user optionally rotate images from one selected directory in a following way: 
//Let the user point out if the image is black ink on white paper or white ink on black paper. 
//Let the user select the degree of the rotation. 
//Rotate the image. The result could be an image of bigger size. Fill the extra space that appeared after the rotation with the color of the paper. Let the user decide if he w ants 5 the image to be of the size as image after the rotation (possibly bigger) or if he wants to cut proportionally the image so that it has the size as before the rotation. 
//Let the user view and browse through modified images (could be in Image Viewing area). 
//Let the user save modified images. 
//Let the user discard modified images and load another directory .

// Saving.
// Code 2 options.
// Option 1: Names of the output files are the name as names of files in one of source directories.
// Let the user decide which one. 
// Option 2:Output files names are composed of a string repeated in all names and a counter.
// User determines the string, after which element of the string we put the counter and how the counter works:
// start value of the counter, counter step and number of digits in the counter.
// Default values are: string = “image”, appearance of counter = 5 (which is after “e”), start = 0, step = 1, digits = 3,
// what gives the following names : image000, image001, image002, and so on.

public class Window {
	
	// Finals
	private final String STRING_PROGRAM_TITLE = "[LAB3.B.7] Image processor";
	private final String STRING_DEFAULT_DIR_NUMBERS = "0/0 images loaded after merge";
	private final String STRING_BROWSE = "Browse...";
	private final String STRING_DEFAULT_DIRECTORY_LIST_ITEM = "Browse for directories from right panel";
	private final String STRING_DEFAULT_DIRECTORY_CONTENT_ITEM = "No folder selected";
	private final String STRING_DIRECTORIES = "Directories";
	private final String[] STRING_ARRAY_METHOD = new String[]{"Center images", "Resize (enlarge)", "Resize (shrink)", "Cut out"};
	private final String[] STRING_ARRAY_TYPE = new String[]{"AND", "OR", "XOR"};
	private final String[] STRING_ARRAY_FILE_FORMATS = new String[] {".bmp", ".png", ".jpg", ".jpeg", ".tiff", ".tif"};
	private final String[] STRING_ARRAY_DIALOG_BUTTONS = new String[]{"Yes","No"};
	private final ImageIcon IMAGEICON_DELETE =  new ImageIcon(Window.class.getResource("/lab3Project/delete.png"));
	private final ImageIcon IMAGEICON_REFRESH =  new ImageIcon(Window.class.getResource("/lab3Project/refresh.png"));
	private final ImageIcon IMAGEICON_PREVIEW_DEFAULT =  new ImageIcon(Window.class.getResource("/lab3Project/null-image.jpg"));
	
	private final int NUMBER_OF_DIRECTORIES = 5;
	private final int THUMBNAIL_HEIGHT = 200;
	private int currentPreview = 1;
	
	private ArrayList<ArrayList<BufferedImage>> cachedImagesFromDirectories = new ArrayList<ArrayList<BufferedImage>>();
	private ArrayList<BufferedImage> cachedMergeResult = new ArrayList<BufferedImage>();
	private BufferedImage cachedImagePreview = ImageManipulation.bufferedImageFromImageIcon(IMAGEICON_PREVIEW_DEFAULT);

	//private ArrayList<ArrayList<BufferedImage>> cachedThumbnails = new ArrayList<ArrayList<BufferedImage>>();	//TODO: Cache thumbnails for faster runtime
	
	private String cachedSelectedThumbnailDirectory = "";
	private ArrayList<JLabel> thumbnailImages = new ArrayList<JLabel>();
	
	//private int multiplier = THUMBNAIL_HEIGHT; // Assign initial value to width multiplier
	//private String bufferedComboBoxSelection="";
	//private String[] cachedDirectories = new String[NUMBER_OF_DIRECTORIES];
	//private Path[] cachedDirectories = new Path[NUMBER_OF_DIRECTORIES];
	//private ArrayList<String> currentDirectoryListing = new ArrayList<String>();

	
	//TODO: last location he opened,where was the last location he saved his last generated images.
	//private String lastLocationOpened = null;
	//private String lastLocationSaved = null;
	
	private JFrame Lab3ImageProcessor;
	private final JLabel directorySelectionJLabel = new JLabel(STRING_DIRECTORIES);
	private final JTabbedPane tabbedJPanel = new JTabbedPane(JTabbedPane.TOP);
	private final JMenuBar JMenuBar = new JMenuBar();
	private final JMenu menuBarFile = new JMenu("File");
	private final JPanel directoriesJTabbedPane = new JPanel();
	private final JPanel operationsJPanel = new JPanel();
	
	private final JButton directorySelection1BrowseJButton = new JButton(STRING_BROWSE);
	private final JButton directorySelection2BrowseJButton = new JButton(STRING_BROWSE);
	private final JButton directorySelection3BrowseJButton = new JButton(STRING_BROWSE);
	private final JButton directorySelection4BrowseJButton = new JButton(STRING_BROWSE);
	private final JButton directorySelection5BrowseJButton = new JButton(STRING_BROWSE);
	private final JTextField directorySelection1JTextField = new JTextField();
	private final JTextField directorySelection2JTextField = new JTextField();
	private final JTextField directorySelection3JTextField = new JTextField();
	private final JTextField directorySelection4JTextField = new JTextField();
	private final JTextField directorySelection5JTextField = new JTextField();
	private final JButton directorySelection1ClearJButton = new JButton("");
	private final JButton directorySelection2ClearJButton = new JButton("");
	private final JButton directorySelection3ClearJButton = new JButton("");
	private final JButton directorySelection4ClearJButton = new JButton("");
	private final JButton directorySelection5ClearJButton = new JButton("");
	private String cachedDirectories[] = new String[NUMBER_OF_DIRECTORIES];
	
	private final JMenuItem mntmExit = new JMenuItem("Exit");
	private final JLabel operationsJLabel = new JLabel("Operations");
	private final JLabel directoryJLabel = new JLabel("Directory:");
	private final JButton operationsMergeJButton = new JButton("Merge");
	private final JButton operationsSaveJButton = new JButton("Save");
	private final JButton operationsDisposeJButton = new JButton("Dispose");
	private final JComboBox<String> directoryListingJComboBox = new JComboBox<String>();
	
	private final JEditorPane directoryListingJEditorPane = new JEditorPane();
	private final JScrollPane thumbnailJScrollPane = new JScrollPane();
	private final JPanel thumbnailJPanel = new JPanel();
	private final JScrollPane directoryListingJScrollPane = new JScrollPane();
	
	private final JComboBox<String> operationsMergeTypeJComboBox = new JComboBox<String>();
	private final JComboBox<String> operationsMergeMethodJComboBox = new JComboBox<String>();
	private final JComboBox<String> operationsSaveExtensionJComboBox = new JComboBox<String>();
	private final JButton operationsRotateJButton = new JButton("Rotate");
	private final JButton refreshDirectoryListingJButton = new JButton("");
	private final JPanel previewJTabbedPane = new JPanel();
	private final Component imagePreviewGlueL = Box.createGlue();
	private final JLabel imagePreviewJLabel = new JLabel("");
	private final Component imagePreviewGlueR = Box.createGlue();
	private final JButton btnLeft = new JButton("left");
	private final JButton btnRight = new JButton("Right");
	private final JLabel lblImagesLoaded = new JLabel(STRING_DEFAULT_DIR_NUMBERS);
	
	
	
	/**
	 * Create the application.
	 */

	public static void main(String[] args) {
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (Throwable e) {
			e.printStackTrace();
		}
		EventQueue.invokeLater(new Runnable() {
			@Override
			public void run() {
				try {
					Window window = new Window();
					window.Lab3ImageProcessor.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}
		);
		
	}
	public Window() {
		initialize();
	}
	private void initVariables(){
		System.out.println("Filling default data");
		for(int i=0;i<NUMBER_OF_DIRECTORIES;i++){
			cachedImagesFromDirectories.add(new ArrayList<BufferedImage>());
			cachedDirectories[i] = "";
		}
	}
	private void initialize() {
		initVariables();
		
		Lab3ImageProcessor = new JFrame();
		Lab3ImageProcessor.setMinimumSize(new Dimension(900, 600));
		Lab3ImageProcessor.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent arg0) {
				promptExit();
			}
		});
		Lab3ImageProcessor.setTitle(STRING_PROGRAM_TITLE);
		Lab3ImageProcessor.setBounds(100, 100, 900, 600);
		Lab3ImageProcessor.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		refreshDirectoryListingJButton.setContentAreaFilled(false);
		refreshDirectoryListingJButton.setBorderPainted(false);
		refreshDirectoryListingJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent arg0) {
				//TODO: Add refresh to directory listing
				updateDirectoryListing();
			}
		});
		refreshDirectoryListingJButton.setIcon(IMAGEICON_REFRESH);
		directoryListingJComboBox.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if(directoryListingJComboBox.getSelectedItem()!=null){
					if(directoryListingJComboBox.getItemCount()!=1){
						actionDirectoryListingChanged();
					}
				}
			}
		});
		btnLeft.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				previewMove(0);
			}
		});
		btnRight.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				previewMove(1);
			}
		});
		
				directoryListingJComboBox.setModel(new DefaultComboBoxModel<String>(new String[] {STRING_DEFAULT_DIRECTORY_LIST_ITEM}));
				previewJTabbedPane.addComponentListener(new ComponentAdapter() {
					@Override
					public void componentResized(ComponentEvent arg0) {
							updatePreviewSize();
					}
				});
				previewJTabbedPane.setBackground(Color.WHITE);
				
				tabbedJPanel.addTab("Image preview", null, previewJTabbedPane, null);
				previewJTabbedPane.setLayout(new BoxLayout(previewJTabbedPane, BoxLayout.X_AXIS));
				
				setImagePreview();
				
				directoriesJTabbedPane.setBackground(Color.WHITE);
				
				tabbedJPanel.addTab("Directory preview", null, directoriesJTabbedPane, null);
				GroupLayout gl_directoriesJTabbedPane = new GroupLayout(directoriesJTabbedPane);
				gl_directoriesJTabbedPane.setHorizontalGroup(
					gl_directoriesJTabbedPane.createParallelGroup(Alignment.TRAILING)
						.addGroup(gl_directoriesJTabbedPane.createSequentialGroup()
							.addContainerGap()
							.addGroup(gl_directoriesJTabbedPane.createParallelGroup(Alignment.LEADING)
								.addComponent(thumbnailJScrollPane, GroupLayout.DEFAULT_SIZE, 446, Short.MAX_VALUE)
								.addComponent(directoryListingJScrollPane)
								.addGroup(gl_directoriesJTabbedPane.createSequentialGroup()
									.addComponent(directoryJLabel)
									.addPreferredGap(ComponentPlacement.RELATED)
									.addComponent(directoryListingJComboBox, 0, 368, Short.MAX_VALUE)
									.addPreferredGap(ComponentPlacement.RELATED)
									.addComponent(refreshDirectoryListingJButton, GroupLayout.PREFERRED_SIZE, 20, GroupLayout.PREFERRED_SIZE)))
							.addContainerGap())
				);
				gl_directoriesJTabbedPane.setVerticalGroup(
					gl_directoriesJTabbedPane.createParallelGroup(Alignment.LEADING)
						.addGroup(gl_directoriesJTabbedPane.createSequentialGroup()
							.addGap(13)
							.addGroup(gl_directoriesJTabbedPane.createParallelGroup(Alignment.BASELINE)
								.addComponent(directoryJLabel)
								.addComponent(directoryListingJComboBox, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
								.addComponent(refreshDirectoryListingJButton, GroupLayout.PREFERRED_SIZE, 20, GroupLayout.PREFERRED_SIZE))
							.addPreferredGap(ComponentPlacement.RELATED)
							.addComponent(directoryListingJScrollPane, GroupLayout.DEFAULT_SIZE, 186, Short.MAX_VALUE)
							.addPreferredGap(ComponentPlacement.RELATED)
							.addComponent(thumbnailJScrollPane, GroupLayout.PREFERRED_SIZE, 234, GroupLayout.PREFERRED_SIZE)
							.addContainerGap())
				);
				thumbnailJScrollPane.setMinimumSize(new Dimension(23, 270));
				directoryListingJScrollPane.setViewportView(directoryListingJEditorPane);
				directoryListingJEditorPane.setText(STRING_DEFAULT_DIRECTORY_CONTENT_ITEM);
				directoryListingJEditorPane.setBorder(new SoftBevelBorder(BevelBorder.LOWERED, null, null, null, null));
				
				thumbnailJScrollPane.setViewportView(thumbnailJPanel);
				directoriesJTabbedPane.setLayout(gl_directoriesJTabbedPane);
		directorySelection5ClearJButton.setBorderPainted(false);
		directorySelection5ClearJButton.setContentAreaFilled(false);
		directorySelection5ClearJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent e) {
				clearDirectoryPath(4,directorySelection5JTextField);
			}
		});
		directorySelection5ClearJButton.setIcon(IMAGEICON_DELETE);
		directorySelection4ClearJButton.setContentAreaFilled(false);
		directorySelection4ClearJButton.setBorderPainted(false);
		directorySelection4ClearJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent e) {
				clearDirectoryPath(3,directorySelection4JTextField);
			}
		});
		directorySelection4ClearJButton.setIcon(IMAGEICON_DELETE);
		directorySelection3ClearJButton.setContentAreaFilled(false);
		directorySelection3ClearJButton.setBorderPainted(false);
		directorySelection3ClearJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent e) {
				clearDirectoryPath(2,directorySelection3JTextField);
			}
		});
		directorySelection3ClearJButton.setIcon(IMAGEICON_DELETE);
		directorySelection2ClearJButton.setBorderPainted(false);
		directorySelection2ClearJButton.setContentAreaFilled(false);
		directorySelection2ClearJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent e) {
				clearDirectoryPath(1,directorySelection2JTextField);
			}
		});
		directorySelection2ClearJButton.setIcon(IMAGEICON_DELETE);
		directorySelection1ClearJButton.setContentAreaFilled(false);
		directorySelection1ClearJButton.setBorderPainted(false);
		directorySelection1ClearJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent arg0) {
				clearDirectoryPath(0,directorySelection1JTextField);
			}
		});
		directorySelection1ClearJButton.setIcon(IMAGEICON_DELETE);
		directorySelection5JTextField.setBackground(Color.WHITE);
		directorySelection5JTextField.setEditable(false);
		directorySelection5JTextField.setColumns(10);
		directorySelection4JTextField.setBackground(Color.WHITE);
		directorySelection4JTextField.setEditable(false);
		directorySelection4JTextField.setColumns(10);
		directorySelection3JTextField.setBackground(Color.WHITE);
		directorySelection3JTextField.setEditable(false);
		directorySelection3JTextField.setColumns(10);
		directorySelection2JTextField.setBackground(Color.WHITE);
		directorySelection2JTextField.setEditable(false);
		directorySelection2JTextField.setColumns(10);
		directorySelection1JTextField.setBackground(Color.WHITE);
		directorySelection1JTextField.setEditable(false);
		directorySelection1JTextField.setColumns(10);
		operationsMergeJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent arg0) {
				//TODO: If not saved, prompt about it
				mergeDirectories(Type.returnTypeFromString(operationsMergeTypeJComboBox.getSelectedItem().toString()), Method.returnMethodFromString(operationsMergeMethodJComboBox.getSelectedItem().toString()));
				promptDoYouWantToSave();
			}
		});
		operationsMergeTypeJComboBox.setModel(new DefaultComboBoxModel<String>(STRING_ARRAY_TYPE));
		operationsMergeMethodJComboBox.setModel(new DefaultComboBoxModel<String>(STRING_ARRAY_METHOD));
		operationsSaveJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent e) {
				promptDoYouWantToSave();
			}
		});
		operationsSaveExtensionJComboBox.setModel(new DefaultComboBoxModel<String>(STRING_ARRAY_FILE_FORMATS));
		operationsDisposeJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent e) {
				dispose();
			}
		});
		GroupLayout gl_operationsJPanel = new GroupLayout(operationsJPanel);
		gl_operationsJPanel.setHorizontalGroup(
			gl_operationsJPanel.createParallelGroup(Alignment.LEADING)
				.addGroup(gl_operationsJPanel.createSequentialGroup()
					.addContainerGap()
					.addGroup(gl_operationsJPanel.createParallelGroup(Alignment.LEADING)
						.addComponent(directorySelectionJLabel, GroupLayout.DEFAULT_SIZE, 263, Short.MAX_VALUE)
						.addGroup(gl_operationsJPanel.createSequentialGroup()
							.addGroup(gl_operationsJPanel.createParallelGroup(Alignment.LEADING, false)
								.addComponent(directorySelection5BrowseJButton, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
								.addComponent(directorySelection4BrowseJButton, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
								.addComponent(directorySelection3BrowseJButton, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
								.addComponent(directorySelection2BrowseJButton, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
								.addComponent(directorySelection1BrowseJButton, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
							.addGap(10)
							.addGroup(gl_operationsJPanel.createParallelGroup(Alignment.TRAILING)
								.addComponent(directorySelection5JTextField, GroupLayout.DEFAULT_SIZE, 148, Short.MAX_VALUE)
								.addComponent(directorySelection4JTextField, GroupLayout.DEFAULT_SIZE, 148, Short.MAX_VALUE)
								.addComponent(directorySelection3JTextField, GroupLayout.DEFAULT_SIZE, 148, Short.MAX_VALUE)
								.addComponent(directorySelection2JTextField, GroupLayout.DEFAULT_SIZE, 148, Short.MAX_VALUE)
								.addGroup(gl_operationsJPanel.createSequentialGroup()
									.addPreferredGap(ComponentPlacement.UNRELATED)
									.addComponent(directorySelection1JTextField, GroupLayout.DEFAULT_SIZE, 148, Short.MAX_VALUE)))
							.addPreferredGap(ComponentPlacement.RELATED)
							.addGroup(gl_operationsJPanel.createParallelGroup(Alignment.LEADING)
								.addComponent(directorySelection5ClearJButton, GroupLayout.PREFERRED_SIZE, 20, GroupLayout.PREFERRED_SIZE)
								.addComponent(directorySelection4ClearJButton, GroupLayout.PREFERRED_SIZE, 20, GroupLayout.PREFERRED_SIZE)
								.addComponent(directorySelection3ClearJButton, GroupLayout.PREFERRED_SIZE, 20, GroupLayout.PREFERRED_SIZE)
								.addComponent(directorySelection2ClearJButton, GroupLayout.PREFERRED_SIZE, 20, GroupLayout.PREFERRED_SIZE)
								.addComponent(directorySelection1ClearJButton, GroupLayout.PREFERRED_SIZE, 20, GroupLayout.PREFERRED_SIZE)))
						.addComponent(operationsJLabel, GroupLayout.PREFERRED_SIZE, 228, GroupLayout.PREFERRED_SIZE)
						.addGroup(gl_operationsJPanel.createSequentialGroup()
							.addComponent(operationsMergeJButton, GroupLayout.PREFERRED_SIZE, 69, GroupLayout.PREFERRED_SIZE)
							.addPreferredGap(ComponentPlacement.RELATED)
							.addComponent(operationsMergeTypeJComboBox, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
							.addPreferredGap(ComponentPlacement.RELATED)
							.addComponent(operationsMergeMethodJComboBox, 0, 136, Short.MAX_VALUE))
						.addGroup(gl_operationsJPanel.createSequentialGroup()
							.addComponent(operationsSaveJButton, GroupLayout.PREFERRED_SIZE, 69, GroupLayout.PREFERRED_SIZE)
							.addPreferredGap(ComponentPlacement.RELATED)
							.addComponent(operationsSaveExtensionJComboBox, 0, 188, Short.MAX_VALUE))
						.addComponent(operationsDisposeJButton)
						.addComponent(operationsRotateJButton, GroupLayout.PREFERRED_SIZE, 69, GroupLayout.PREFERRED_SIZE)
						.addComponent(lblImagesLoaded))
					.addContainerGap())
		);
		gl_operationsJPanel.setVerticalGroup(
			gl_operationsJPanel.createParallelGroup(Alignment.LEADING)
				.addGroup(gl_operationsJPanel.createSequentialGroup()
					.addContainerGap()
					.addComponent(directorySelectionJLabel)
					.addGap(12)
					.addGroup(gl_operationsJPanel.createParallelGroup(Alignment.BASELINE)
						.addComponent(directorySelection1JTextField, GroupLayout.DEFAULT_SIZE, 20, Short.MAX_VALUE)
						.addComponent(directorySelection1ClearJButton, GroupLayout.PREFERRED_SIZE, 20, GroupLayout.PREFERRED_SIZE)
						.addComponent(directorySelection1BrowseJButton, GroupLayout.DEFAULT_SIZE, 26, Short.MAX_VALUE))
					.addGap(9)
					.addGroup(gl_operationsJPanel.createParallelGroup(Alignment.BASELINE)
						.addComponent(directorySelection2JTextField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
						.addComponent(directorySelection2ClearJButton, GroupLayout.PREFERRED_SIZE, 20, GroupLayout.PREFERRED_SIZE)
						.addComponent(directorySelection2BrowseJButton, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
					.addGap(9)
					.addGroup(gl_operationsJPanel.createParallelGroup(Alignment.BASELINE)
						.addComponent(directorySelection3JTextField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
						.addComponent(directorySelection3ClearJButton, GroupLayout.PREFERRED_SIZE, 20, GroupLayout.PREFERRED_SIZE)
						.addComponent(directorySelection3BrowseJButton, GroupLayout.PREFERRED_SIZE, 20, GroupLayout.PREFERRED_SIZE))
					.addGap(9)
					.addGroup(gl_operationsJPanel.createParallelGroup(Alignment.BASELINE)
						.addComponent(directorySelection4JTextField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
						.addComponent(directorySelection4ClearJButton, GroupLayout.PREFERRED_SIZE, 20, GroupLayout.PREFERRED_SIZE)
						.addComponent(directorySelection4BrowseJButton))
					.addGap(9)
					.addGroup(gl_operationsJPanel.createParallelGroup(Alignment.BASELINE)
						.addComponent(directorySelection5JTextField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
						.addComponent(directorySelection5ClearJButton, GroupLayout.PREFERRED_SIZE, 20, GroupLayout.PREFERRED_SIZE)
						.addComponent(directorySelection5BrowseJButton, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
					.addPreferredGap(ComponentPlacement.RELATED)
					.addComponent(operationsJLabel)
					.addPreferredGap(ComponentPlacement.RELATED)
					.addGroup(gl_operationsJPanel.createParallelGroup(Alignment.BASELINE)
						.addComponent(operationsMergeJButton)
						.addComponent(operationsMergeTypeJComboBox, GroupLayout.PREFERRED_SIZE, 22, GroupLayout.PREFERRED_SIZE)
						.addComponent(operationsMergeMethodJComboBox, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
					.addPreferredGap(ComponentPlacement.RELATED)
					.addGroup(gl_operationsJPanel.createParallelGroup(Alignment.BASELINE)
						.addComponent(operationsSaveJButton)
						.addComponent(operationsSaveExtensionJComboBox, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
					.addPreferredGap(ComponentPlacement.RELATED)
					.addComponent(operationsDisposeJButton)
					.addPreferredGap(ComponentPlacement.RELATED)
					.addComponent(operationsRotateJButton)
					.addPreferredGap(ComponentPlacement.RELATED)
					.addComponent(lblImagesLoaded)
					.addGap(182))
		);
		directorySelection1BrowseJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent arg0) {
				browseForDirectory(0,directorySelection1BrowseJButton,directorySelection1JTextField);
			}
		});
		directorySelection2BrowseJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent arg0) {
				browseForDirectory(1,directorySelection2BrowseJButton,directorySelection2JTextField);
			}
		});
		directorySelection3BrowseJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent arg0) {
				browseForDirectory(2,directorySelection3BrowseJButton,directorySelection3JTextField);
			}
		});
		directorySelection4BrowseJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent arg0) {
				browseForDirectory(3,directorySelection4BrowseJButton,directorySelection4JTextField);
			}
		});
		directorySelection5BrowseJButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent arg0) {
				browseForDirectory(4,directorySelection5BrowseJButton,directorySelection5JTextField);
			}
		});
		operationsJPanel.setLayout(gl_operationsJPanel);
		GroupLayout groupLayout = new GroupLayout(Lab3ImageProcessor.getContentPane());
		groupLayout.setHorizontalGroup(
			groupLayout.createParallelGroup(Alignment.LEADING)
				.addGroup(groupLayout.createSequentialGroup()
					.addContainerGap()
					.addComponent(tabbedJPanel, GroupLayout.PREFERRED_SIZE, 471, Short.MAX_VALUE)
					.addGap(18)
					.addComponent(operationsJPanel, GroupLayout.PREFERRED_SIZE, 283, GroupLayout.PREFERRED_SIZE)
					.addContainerGap())
		);
		groupLayout.setVerticalGroup(
			groupLayout.createParallelGroup(Alignment.TRAILING)
				.addGroup(groupLayout.createSequentialGroup()
					.addContainerGap()
					.addGroup(groupLayout.createParallelGroup(Alignment.TRAILING)
						.addComponent(operationsJPanel, Alignment.LEADING, GroupLayout.DEFAULT_SIZE, 526, Short.MAX_VALUE)
						.addComponent(tabbedJPanel, Alignment.LEADING, GroupLayout.DEFAULT_SIZE, 526, Short.MAX_VALUE))
					.addContainerGap())
		);
		Lab3ImageProcessor.getContentPane().setLayout(groupLayout);
		
		Lab3ImageProcessor.setJMenuBar(JMenuBar);
		
		JMenuBar.add(menuBarFile);
		mntmExit.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				promptExit();
			}
		});
		
		menuBarFile.add(mntmExit);
	}
	private void promptExit(){
	    int PromptResult = JOptionPane.showOptionDialog(null, 
		        "Are you sure you want to exit? Unsaved image will be lost", STRING_PROGRAM_TITLE, 
		        JOptionPane.DEFAULT_OPTION, JOptionPane.WARNING_MESSAGE, null, 
		        STRING_ARRAY_DIALOG_BUTTONS,STRING_ARRAY_DIALOG_BUTTONS[1]);
		    if(PromptResult==0)
		    {
		      System.exit(0);          
		    }
	}

	private void actionDirectoryListingChanged(){
		updateDirectoryListing();
	}

	private void browseForDirectory(int id,JButton parent, JTextField target){

	    //TODO: Deny setting empty folder (Without images)
	    JFileChooser chooser = new JFileChooser();
	    chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
	    int returnVal = chooser.showOpenDialog(parent);
	    if(returnVal == JFileChooser.APPROVE_OPTION) {
	    	target.setText(chooser.getSelectedFile().getPath());
	    	cachedDirectories[id]=chooser.getSelectedFile().getPath();
	    	
			System.out.println("Setting directory "+id+" with "+cachedDirectories[id]);
	    	updateCachedImages(id,cachedDirectories[id]);
	    	updateDirectoriesList();
	    }
	}
	
	private File[] getImagesListFromPath(String path){File dir = new File(path);
		File[] filesList = dir.listFiles(new FilenameFilter() {
			@Override
			public boolean accept(File dir, String name) {
				return name.toLowerCase().endsWith(".jpg")
						|| name.toLowerCase().endsWith(".jpeg")
						|| name.toLowerCase().endsWith(".png")
						|| name.toLowerCase().endsWith(".tif")
						|| name.toLowerCase().endsWith(".tiff")
						|| name.toLowerCase().endsWith(".bmp");
			}
		});
		return filesList;
	}
	private void updateCachedImages(){
		for(int i=0;i<NUMBER_OF_DIRECTORIES;i++)
		{
			if(!cachedDirectories[i].equals("")){
				updateCachedImages(i, cachedDirectories[i]);
			}
		}
	}
	private void updateCachedImages(int id, String path)
	{
		cachedImagesFromDirectories.get(id).clear();
		File[] filesList =  getImagesListFromPath(path);
		for (File file : filesList) {
			if (file.isFile()) {
				cachedImagesFromDirectories.get(id).add((BufferedImage) ImageManipulation.loadImageAsImage(path + "\\" + file.getName()));
			}
		}
		System.out.println("Images cached from directory "+id+": " + cachedImagesFromDirectories.get(id).size());
	}
	private void updateDirectoriesList(){
		directoryListingJComboBox.removeAllItems();
		for(int i=0;i<NUMBER_OF_DIRECTORIES;i++){
			if(!cachedDirectories[i].equals("")){
				directoryListingJComboBox.addItem(cachedDirectories[i]);
			}
		}
		if(directoryListingJComboBox.getSelectedItem()==null){
			directoryListingJComboBox.addItem(STRING_DEFAULT_DIRECTORY_LIST_ITEM);
			directoryListingJEditorPane.setText(STRING_DEFAULT_DIRECTORY_CONTENT_ITEM);
		}
		else {
			//cachedSelectedThumbnailDirectory =;
			if(!cachedSelectedThumbnailDirectory.equals(directoryListingJComboBox.getSelectedItem().toString())){
				cachedSelectedThumbnailDirectory = directoryListingJComboBox.getSelectedItem().toString();
				updateThumbnails(cachedSelectedThumbnailDirectory);
				updateDirectoryListing(cachedSelectedThumbnailDirectory);
			}
		}
	}
	private void updateThumbnails(){
		thumbnailImages.clear();
		thumbnailJPanel.removeAll();
		thumbnailJPanel.revalidate();
		thumbnailJPanel.repaint();
		if(directoryListingJComboBox.getItemCount()>0&&!directoryListingJComboBox.getSelectedItem().toString().equals(STRING_DEFAULT_DIRECTORY_LIST_ITEM)){
			updateThumbnails(directoryListingJComboBox.getSelectedItem().toString());
		}
	}
	private void updateThumbnails(String input){
		for(int i=0;i<NUMBER_OF_DIRECTORIES;i++){
			if(cachedDirectories[i].equals(input)){
				updateThumbnails(cachedImagesFromDirectories.get(i));
			}
		}
	}
	private void updateThumbnails(ArrayList<BufferedImage> image){
		// TODO: Cache thumbnails
		JLabel buffer = null;
		thumbnailImages.clear();
		thumbnailJPanel.removeAll();
		thumbnailJPanel.revalidate();
		thumbnailJPanel.repaint();
		if(image.size()>0){
			for(int i =0 ;i<image.size();i++){
				buffer = new JLabel("");
				float aspectRatio = (float) image.get(i).getWidth()/(float) image.get(i).getHeight();
				int newWidth = (int) (THUMBNAIL_HEIGHT*aspectRatio);
				ImageIcon newIcon = new ImageIcon(ImageManipulation.resizeImage((BufferedImage) image.get(i), newWidth, THUMBNAIL_HEIGHT));
				buffer.setPreferredSize(new Dimension(newWidth, THUMBNAIL_HEIGHT) );
				buffer.setIcon(newIcon);
				thumbnailImages.add(buffer);
				
			}
			System.out.println("Thumbnails loaded: " + thumbnailImages.size());
			for(int i =0 ;i<thumbnailImages.size();i++){
				thumbnailJPanel.add(thumbnailImages.get(i));
				
			}
			
			thumbnailJPanel.validate();
			thumbnailJPanel.repaint();
		}
		
	}
	private void updateDirectoryListing() {
		updateDirectoryListing(directoryListingJComboBox.getSelectedItem().toString());
		updateCachedImages();
		updateThumbnails(directoryListingJComboBox.getSelectedItem().toString());
	}
	private Boolean isDirectoriesValidToMerge(){
		Boolean result = false;
		Boolean firstOne = false;
		for(int i=0;i<NUMBER_OF_DIRECTORIES;i++){
			if(cachedImagesFromDirectories.get(i).size()>0){
				if(firstOne ==true){
					result = true;
					break;
				}
				firstOne = true;
			}
		}
		return result;
	}
	private void setImagePreview(ImageIcon icon){
		previewJTabbedPane.removeAll();

		
		imagePreviewJLabel.setIcon(icon);
		
		previewJTabbedPane.add(btnLeft);
		previewJTabbedPane.add(imagePreviewGlueL);
		previewJTabbedPane.add(imagePreviewJLabel);
		previewJTabbedPane.add(imagePreviewGlueR);
		previewJTabbedPane.add(btnRight);
		
		previewJTabbedPane.revalidate();
		previewJTabbedPane.repaint();
	}
	private void previewMove(int direction){
		if(cachedMergeResult.size()>0){
			if(direction==0){
				currentPreview--;
				if(currentPreview<1){
					currentPreview=cachedMergeResult.size();
				}
			}
			else {
				currentPreview++;
				if(currentPreview>cachedMergeResult.size()){
					currentPreview=1;
				}
			}
			updateImagesNumbers();
			setImagePreview(adjustSizeByPreviewSize(cachedMergeResult.get(currentPreview-1)));
			System.out.println(currentPreview+" out of "+(cachedMergeResult.size()));
		}
	}
	private void setImagePreview(){
		System.out.println("Setting default image preview");
		setImagePreview(IMAGEICON_PREVIEW_DEFAULT);
	}
	private ImageIcon adjustSizeByPreviewSize(BufferedImage img){
		int maxWidth = previewJTabbedPane.getWidth()-btnRight.getWidth()-btnLeft.getWidth();
		int maxHeight = previewJTabbedPane.getHeight();
		int imgWidth = img.getWidth();
		int imgHeight = img.getHeight();
		
		float aspectRatio = (float) imgWidth/(float) imgHeight;
		if(aspectRatio<1){
			imgWidth = maxWidth;
			imgHeight = (int) (maxWidth/aspectRatio);
		}
		else {
			imgHeight = maxHeight;
			imgWidth = (int) (maxHeight/aspectRatio);
		}

		//return new ImageIcon(ImageManipulation.resizeImage((BufferedImage) img, imgWidth, imgHeight));
		return new ImageIcon(ImageManipulation.resizeImage((BufferedImage) img, maxWidth, maxHeight));
		
	}
	private void updatePreviewSize(){
		if(!imagePreviewJLabel.getIcon().equals(IMAGEICON_PREVIEW_DEFAULT)){
			setImagePreview(adjustSizeByPreviewSize(cachedImagePreview));
		}
	}
	private void updateImagePreview(){
		if(cachedMergeResult.size()>0){
			//TODO: Switchable preview
			cachedImagePreview = cachedMergeResult.get(0);
			setImagePreview(adjustSizeByPreviewSize(cachedMergeResult.get(0)));
		}
	}
	private void updateImagesNumbers(){
		if(cachedMergeResult.size()<1){
			lblImagesLoaded.setText(STRING_DEFAULT_DIR_NUMBERS);
		}
		else {
			lblImagesLoaded.setText(currentPreview+"/"+cachedMergeResult.size()+" images loaded after merge");
		}
	}
	private void mergeDirectories(Type type,Method method){
		if(isDirectoriesValidToMerge()){
			cachedMergeResult = ImageManipulation.mergeDirectories(cachedImagesFromDirectories, type, method);
			currentPreview = 1;
			updateImagePreview();
			updateImagesNumbers();
		}
		else {
			System.out.println("You need to have at least 2 out of "+NUMBER_OF_DIRECTORIES+" directories with files to merge");
		}
	}
	private void updateDirectoryListing(String path) {
		ArrayList<String> currentDirectoryListing = new ArrayList<String>();
		String buffer = new String();
		
		File[] filesList =  getImagesListFromPath(path);
		currentDirectoryListing = new ArrayList<String>();
		for (File file : filesList) {
			if (file.isFile()) {
				currentDirectoryListing.add(directoryListingJComboBox
						.getSelectedItem().toString() + "\\" + file.getName());
				buffer += file.getName() + "\n";
			}
		}
		directoryListingJEditorPane.setText(buffer);
		System.out.println("Files found: " + currentDirectoryListing.size());
	}
	private void dispose(){
		System.out.println("Disposing...");
		setImagePreview();
		// TODO: Add clearing of image preview pane
		cachedDirectories = new String[NUMBER_OF_DIRECTORIES];
		cachedImagesFromDirectories = new ArrayList<ArrayList<BufferedImage>>();
		thumbnailImages = new ArrayList<JLabel>();
		cachedSelectedThumbnailDirectory = "";

		directorySelection1JTextField.setText("");
		directorySelection2JTextField.setText("");
		directorySelection3JTextField.setText("");
		directorySelection4JTextField.setText("");
		directorySelection5JTextField.setText("");
		cachedMergeResult = new ArrayList<BufferedImage>();
		currentPreview = 1;
		//cachedImagePreview = ImageManipulation.bufferedImageFromImageIcon(IMAGEICON_PREVIEW_DEFAULT);
		updateImagesNumbers();
		initVariables();
		updateDirectoriesList();
		updateThumbnails();
		
	}
	private void promptDoYouWantToSave(){
		if(cachedMergeResult.size()>0){
		    int PromptResult = JOptionPane.showOptionDialog(null, 
			        "Do you want to save?", STRING_PROGRAM_TITLE, 
			        JOptionPane.DEFAULT_OPTION, JOptionPane.WARNING_MESSAGE, null, 
			        STRING_ARRAY_DIALOG_BUTTONS,STRING_ARRAY_DIALOG_BUTTONS[1]);
		    if(PromptResult==0)
		    {
				ImageManipulation.saveArrayOfImages(cachedMergeResult, System.getProperty("user.home") + "\\Desktop\\"+"Result", Extension.PNG);
		    }
		}
	}
	
	private void clearDirectoryPath (int id, JTextField target){
		// TODO: Browsing same folder, deleting it wont update thumbnails/listing. TOo sleepy
		System.out.println("Clearing path "+id);
		cachedDirectories[id]="";
		cachedImagesFromDirectories.get(id).clear();
		target.setText("");
		updateDirectoriesList();
		updateThumbnails();
	}
}
