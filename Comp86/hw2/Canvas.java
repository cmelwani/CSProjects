//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file creates a canvas in order to draw everything and uses
//the repaint feature.
//This class calls Model which holds all of the data. 
//This class is called in Main.java 

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

public class Canvas extends JPanel implements MouseListener {

    // This is the draw callback
    Canvas() {
        addMouseListener(this);
    }

    public Model model;
    public void setModel (Model model) {
        this.model = model;

    }
    public void paintComponent (Graphics g) { 
        super.paintComponent(g); 
        model.draw(g);
    }

    public void mousePressed (MouseEvent e) {
        model.correlate(e.getX(), e.getY());
    }

    public void mouseClicked (MouseEvent e) {}
    public void mouseReleased (MouseEvent e) {}
    public void mouseEntered (MouseEvent e) {}
    public void mouseExited (MouseEvent e) {}

}
