//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file creates the object Worker that extends JPanel.
//Instances of this object is created in Module and Worker has its own features.

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class Worker extends Vehicle{

    ImageIcon icon1;

    private int row;
    private int column;

    Worker (int x, int y) {
        this.row = x;
        this.column = y;
        icon1 = new ImageIcon ("worker.png");
    }

    public int getX() {
        return row;
    }

    public int getY() {
        return column;
    }

    public void move(int x, int y) {
        row += x;
        column += y;
    }

    public void tick() {
        row += 2;
    }

    public boolean pickCorrelation(int x, int y) {
        int icon_height = icon1.getIconHeight();
        int icon_width = icon1.getIconWidth();

        if(x >= row && x <= row + icon_width) {
            if(y >= column && y <= column + icon_height) {
                return true;
            }
        }
        return false;
    }

    public void highlight(Graphics g, int zoom, int pan_x, int pan_y) {
        int width = icon1.getIconWidth();
        int height = icon1.getIconHeight();
        int curr_x = (row + pan_x) * zoom;
        int curr_y = (column + pan_y) * zoom;
        g.drawRect(curr_x, curr_y, (width + 1), (height + 1));
    }

    public void draw(Graphics g, int zoom, int pan_x, int pan_y) {
        int curr_x = (row + pan_x) * zoom;
        int curr_y = (column + pan_y) * zoom;
        icon1.paintIcon(this, g, curr_x, curr_y);
    }
}