//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file creates a Combo Box class that sets up the Combo 
//box widget. This class is called in Main.java

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class ComboBox extends JComboBox<String> implements ItemListener {
    public ComboBox () {
	addItem ("One"); 
	addItem ("Two"); 
	addItem ("Three"); 
	addItem ("Four"); 
	setSelectedItem ("three"); 
	addItemListener (this);
    }

    public void itemStateChanged (ItemEvent e) { 
	if (e.getStateChange()==ItemEvent.SELECTED) { 
	    System.out.println ("Combo: " + e.getItem()); 
	}
    }
}
