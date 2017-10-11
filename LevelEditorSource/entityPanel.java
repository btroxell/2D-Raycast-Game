package levelEditor;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.lang.*;



public class entityPanel extends JPanel implements ActionListener{
	
	public ImageIcon wall = new ImageIcon("wall.png", "1");
	public ImageIcon gun = new ImageIcon("gun.png", "2");
	public ImageIcon rat = new ImageIcon("ratButt.png", "4");
	public ImageIcon spawn = new ImageIcon("spawn.png", "3");
	private JButton wallButt;
	private JButton gunButt;
	private JButton ratButt;
	private JButton spawnButt;
	public ImageIcon activeImage;
	
	//change back to panel
	//just for testing purposes
	public JPanel EPanel;
	
	public entityPanel(){
		epGUI();
		registerButtons();
	}//end entityPanel constructor
	
	//sets up the gui, need to change it to a panel format
	public void epGUI(){
		
		//makes the buttons with the images
		wallButt = new JButton("Wall",wall);
		gunButt = new JButton("Gun", gun);
		spawnButt = new JButton("Spawn", spawn);
		ratButt = new JButton("Rat", rat);
		
		//creates a default size
		Dimension buttSize = new Dimension(50,50);
		wallButt.setSize(buttSize);
		gunButt.setSize(buttSize);
		spawnButt.setSize(buttSize);
		ratButt.setSize(buttSize);
		
		//since 'this' is a jpanel, making a new jpanel wont work
		//this refers this the constructor itself, which is a panel
		this.add(wallButt);
		this.add(gunButt);
		this.add(spawnButt);
		this.add(ratButt);
		this.setLayout(new GridLayout(0,1));
		//this.setSize(200, 200);
	}//end entity gui
	
	public void registerButtons(){
		wallButt.addActionListener(this);
		gunButt.addActionListener(this);
		spawnButt.addActionListener(this);
		ratButt.addActionListener(this);
	}//end registerButtons
	
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == wallButt){
			ActiveButt(wall);
		} else if (e.getSource() == gunButt){
			ActiveButt(gun);
		} else if (e.getSource() == spawnButt){
			ActiveButt(spawn);
		} else if (e.getSource() == ratButt){
			ActiveButt(rat);
		}//end ratbutt elseif
	}//end actionPerformed
	
	public void ActiveButt(ImageIcon image){
		activeImage = image;
	}//end activeButt
	
	public ImageIcon getActiveImage(){
		return activeImage;
	}//end getter

}//end entityPanel class
