package levelEditor;
import java.awt.*;

import javax.swing.*;

import java.awt.event.*;

public class EditorGrid extends JPanel implements ActionListener{
	
	//class variables/objects
	public JButton[][] gridButt;
	public int rows = 25;
	public int columns = 25;
	public entityPanel ep = new entityPanel();
	public Dimension g = new Dimension(45, 45);
	public ImageIcon img = ep.getActiveImage();
	public ImageIcon wallGrid = new ImageIcon("wallGrid.png", "1");
	public ImageIcon gunGrid = new ImageIcon("gunGrid.png", "2");
	public ImageIcon spawnGrid = new ImageIcon("spawnGrid.png", "3");
	public ImageIcon ratGrid = new ImageIcon("ratGrid.png", "4");
	
	
	public EditorGrid(entityPanel panel){
		ep = panel;
		egGUI();
		//registerGridButtons();
	}//end EditorGrid constructor
	
	public void egGUI(){
		//editorgrid set layout to how many rows and columns
		this.setLayout(new GridLayout(rows, columns));
		//creates a gridButton object, a 2d array of jbuttons
		gridButt = new JButton[rows][columns];
		//makes a new buttons for every x,y in the rows and columns 
		for(int x=0; x<rows; x++){
			for(int y=0; y<columns; y++){
				gridButt[x][y] = new JButton();
				gridButt[x][y].setPreferredSize(g);
				//registerbuttons
				gridButt[x][y].addActionListener(this);
				//editorgrid panel adds the grid of buttons
				this.add(gridButt[x][y]);
			}//end for j
		}//end for i
		
	}//end egGUI
	
	public void actionPerformed(ActionEvent e){
		
		for(int i=0; i<rows; i++){
			for(int j=0; j<columns; j++){
				if(e.getSource() == gridButt[i][j]){
					//exception handler
					try{
						if(((ImageIcon) gridButt[i][j].getIcon()).getDescription() != ep.getActiveImage().getDescription()){
							setEntityImage(i,j);
						} else {
							gridButt[i][j].setIcon(null);
						}//end else
					}catch(NullPointerException err){
						setEntityImage(i,j);
					}//end catch/try
				}//end if
			}//end for j
		}//end for i
	}//end actionPerformed
	
	//takes in the coordinate of the button and sets image to entity clicked
	//easier to make new image and set an image size for the gridbuttons
	//sets the activeimage from entityPanel to a wall
	public void setEntityImage(int i, int j){
		img = ep.getActiveImage();
		if(img == ep.wall){
			img = wallGrid;
		} else if(img == ep.gun){
			img = gunGrid;
		} else if(img == ep.spawn){
			img = spawnGrid;
		} else if(img == ep.rat){
			img = ratGrid;
		}
		gridButt[i][j].setIcon(img);
		//return gridButt[i][j].setIcon(img);
	}//end setEntityImage
	
	//returns ep for use in EditorMenuBar
	public entityPanel getEp(){
		return ep;
	}//end getEp

}//end EditorGrid class
