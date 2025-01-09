//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file creates a Button class that sets up the Button 
//widget. This class is called in Main.java

import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class Button extends JButton implements ActionListener { 
    public Button (String label) {
        setText (label);
        addActionListener (this); 
    }

    public void actionPerformed (ActionEvent e) { 
        System.out.println ("The " + getText() + " button was pushed");     
        String text = (String)e.getActionCommand();
        if(text.equals("Dynamic Button")) {
            JButton b6 = (JButton) e.getSource(); //stores clicked button
            b6.setText("I've changed"); //changes label of button
        } 
        else if(text.equals("I've changed")) {
            JButton b6 = (JButton) e.getSource(); //stores clicked button
            b6.setText("Dynamic Button"); //changes label of button
        }
    }
}