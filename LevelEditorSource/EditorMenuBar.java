package levelEditor;
import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;

public class EditorMenuBar extends JMenuBar implements ActionListener 
{ 
	public JMenu menuFile;
	public JMenuItem menuSave, menuLoad, menuNew;
	//entityPanel ep = new entityPanel();
	public EditorGrid eg;
	
	
	//public static void main(String args[]){
	//	new EditorMenuBar();
	//}
	
	public EditorMenuBar(EditorGrid editorgrid)
	{
		eg = editorgrid;
		setupMenuBar();
		registerMenuItems();
		
	}//end editormenubar constructor
	
	//create the menuBar
	public void setupMenuBar()
	{

		menuFile = new JMenu("File");
		this.add(menuFile);
		
		
		menuSave = new JMenuItem("Save");
		menuNew = new JMenuItem("New");

		menuFile.add(menuSave);
		menuFile.add(menuNew);
		menuFile.setSize(20,20);
		
	}//end setupmenubar
	
	public void registerMenuItems()
	{
		menuSave.addActionListener(this);
		menuNew.addActionListener(this);
		
	}//end registerFileItems
	
	public void actionPerformed(ActionEvent e)
	{
		if (e.getSource() == menuSave){
			writeMap();
		}  else if (e.getSource() == menuNew){
			newMap();
		}//end if/elseif statements
		
	}//end actionPerformed

	/* TO DO:
	 * 1. ADD FUNCTIONALITY
	 * 2. MAKE SURE SAVEMAP IS SAVING AN ARRAYLIST FOR GAME ENGINE TO A NEW .MAP FILE
	 * 3. MAKE THE LOADMAP LOAD UP A MAP FILE
	 * 4. MAKE SURE THE NEWMAP CREATES A NEW GRID AREA, CAN KEEP THE OBJECTS
	 */
	
	//sets all icons in the grid to nothing
	public void newMap()
	{
		for(int x=0; x<eg.rows; x++){
			for(int y=0; y<eg.columns; y++){
				eg.gridButt[x][y].setIcon(null);
			}
		}
	}//end newMap
	
	/*
	* write map creates a filewriter and writes over the current data in file
	* gets the position of the gridButt and gets the icon and compares to the
	* image of the and prints a number for map to read in game engine
	*/
	public void writeMap(){
		try{
		FileWriter outfile = new FileWriter("game.map", false);
		PrintWriter output = new PrintWriter(outfile);
		output.print("{");
			for(int x=0; x<eg.rows; x++){
				for(int y=0; y<eg.columns; y++){
					if(eg.gridButt[x][y].getIcon() == (eg.wallGrid)){
						output.print("1,");
					} else if(eg.gridButt[x][y].getIcon() == (eg.gunGrid)){
						output.print("2,");
					} else if(eg.gridButt[x][y].getIcon() == (eg.ratGrid)){
						output.print("4,");
					} else if(eg.gridButt[x][y].getIcon() == (eg.spawnGrid)){
						output.print("3,");
					} 
					else{
						output.print("0,");
					}
				}//end for y
				output.print("\n");
			}//end for x
			output.print("}");
			output.close();
		}catch (IOException e){
			System.out.println(e.getMessage());
		}
	}//end writeMap
	
}//end editormenubar class
