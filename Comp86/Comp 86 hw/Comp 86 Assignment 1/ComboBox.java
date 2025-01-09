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
