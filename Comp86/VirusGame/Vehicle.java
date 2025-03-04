//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file creates a Vehicle class that is a parent class
//of the vehicles in the simulation. 


import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public abstract class Vehicle extends JPanel {
    public abstract void draw(Graphics g, int zoom, int pan_x, int pan_y);
    public abstract int getX();
    public abstract int getY();
    public abstract void move(int x, int y);
    public abstract void tick();
    public abstract boolean pickCorrelation(int x, int y);
    public abstract void highlight(Graphics g, int zoom, int pan_x, int pan_y);
}
