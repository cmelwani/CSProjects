//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file creates a Button class that sets up the Button 
//widget. This class is called in Main.java. 

import javax.swing.*;
import java.awt.event.ActionListener;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;

public class Button extends JButton implements ActionListener { 
    
    private Model model;

    public Button (String label, Model m) {
        this.model = m;
        setText (label);
        addActionListener (this);
        Color maroon = new Color (128, 0, 0);
        //found it on the internt to find the color maroon. 
        setForeground(maroon);
        setFont(new Font("Times New Roman", Font.BOLD, 12));
    }

    public void actionPerformed (ActionEvent e) { 
        System.out.println ("The " + getText() + " button was pushed"); 
        String text = (String)e.getActionCommand();
        if(text.equals("Move Left")) {
            model.move_vehicle(-40, 0);
        } 
        else if(text.equals("Move Right")) {
            model.move_vehicle(40, 0);
        }
        else if(text.equals("Move Up")) {
            model.move_vehicle(0, -40);
        }
        else if(text.equals("Move Down")) {
            model.move_vehicle(0, 40);
        }
        else if(text.equals("Add Worker")) {
            model.addVehicle("Factory Worker");
        }
        else if(text.equals("Add Manager")) {
            model.addVehicle("Manager");
        }
        else if(text.equals("Add Custodian")) {
            model.addVehicle("Custodian");
        }
    }
}
        

