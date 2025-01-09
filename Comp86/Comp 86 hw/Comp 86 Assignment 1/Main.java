//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file creates instances of other classes. It calls 
//Button.java, ComboBox.java, ScrollBar.java, and TextField.java. 
//This file sets up the window and the layout of the window.

import javax.swing.*;
import java.awt.FlowLayout;

public class Main extends JFrame {
    public static void main (String [] args) {
        new Main (); //creates an instance of main
    }

    public Main () {
        setSize (300, 300); //sets the window size to 300 by 300 pixels 
        setLayout (new FlowLayout ()); //sets layout of window

        Button b1 = new Button ("Push Here");
        Button b2 = new Button ("Click Here");
        Button b3 = new Button ("Press Here");
        Button b4 = new Button ("Hold Here");
        Button b5 = new Button ("Dynamic Button");
        ScrollBar sb1 = new ScrollBar(); //creating an instance 
        TextField tf1 = new TextField(); //creating an instance 
        ComboBox cb1 = new ComboBox(); //creating an instance 
        
        add (b1);
        add (b2);
        add (b3);
        add (b4);
        add (b5);
        add (sb1); 
        add (tf1);
        add (cb1);

        setVisible (true); //shows the window when you run the progam
        setDefaultCloseOperation (EXIT_ON_CLOSE); //closes window
    }
}

