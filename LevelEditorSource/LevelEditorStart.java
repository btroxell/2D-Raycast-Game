package levelEditor;
import java.awt.*;
import java.awt.event.ActionEvent;

import javax.swing.*;

public class LevelEditorStart extends JFrame{
	
	//create new instances
	private EditorMenuBar emBar;
	private EditorGrid edGrid;
	private entityPanel epPanel;
	
	
	public LevelEditorStart(){
		super("Level Editor");
		
		//create objects
		epPanel = new entityPanel();
		edGrid = new EditorGrid(epPanel);
		emBar = new EditorMenuBar(edGrid);
		
		//set variable to screensize
		Toolkit tk = Toolkit.getDefaultToolkit();
		int xWidth = ((int) tk.getScreenSize().getWidth());
		int yHeight = ((int) tk.getScreenSize().getHeight());
		
		//create frame, setlayout, add components
		Container startFrame = this.getContentPane();
		startFrame.setLayout(new BorderLayout(2,1));
		startFrame.add(edGrid, BorderLayout.WEST);
		startFrame.add(epPanel, BorderLayout.LINE_END);
		startFrame.add(emBar, BorderLayout.NORTH);
	
		//set size to fullscreen-ish and normal stuff
		this.setSize(xWidth, yHeight - 50);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
		

		
	}//end levelEditorStart constructor
	
	public static void main(String[] args){
		new LevelEditorStart();
	}//end main
	
	
}//end class LevelEditorStart
