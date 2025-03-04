//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file sets up the object Coronavirus that has a specific 
//icon and features. It extends Vehicle which is its parent class.

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class Coronavirus extends Vehicle{

    ImageIcon icon1;
    private int row;
    private int column;

    Coronavirus (int x, int y) {
        this.row = x;
        this.column = y;
        icon1 = new ImageIcon ("coronavirus.png");
    }

    public int getX() {
        return row;
    }

    public int getY() {
        return column;
    }

    public void move(int x, int y) {}


    public void tick() {
        column -= 4;
    }
    public boolean pickCorrelation(int x, int y) {
        return false;
    }

    public void highlight(Graphics g, int zoom, int pan_x, int pan_y) {}

    public void draw(Graphics g, int zoom, int pan_x, int pan_y) {
        int curr_x = (row + pan_x) * zoom;
        int curr_y = (column + pan_y) * zoom;
        icon1.paintIcon(this, g, curr_x, curr_y);
    }
    
}
