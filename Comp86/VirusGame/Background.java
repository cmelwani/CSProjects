//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file creates a Background class that sets up the Background
//of the screen. This class is called in Model.java. 

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class Background extends JPanel{
    ImageIcon icon1;
    Background() {
        icon1 = new ImageIcon ("background.jpg");
    }

    public void draw(Graphics g) {
        icon1.paintIcon(this, g, 0, 0);
    }

}