//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file creates a button that handles the zooming 
//of the screen on the simulation. 

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class ZoomButton extends JButton implements ActionListener{
    private Model model;
    private int zoom_amount;

    public ZoomButton(Model model, String label, int zoom_amount) {
        this.model = model;
        this.setText(label);
        Color maroon = new Color (128, 0, 0);
        //found it on the internt to find the color maroon. 
        setForeground(maroon);
        setFont(new Font("Times New Roman", Font.BOLD, 12));
        this.zoom_amount = zoom_amount;
        this.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        this.model.zoom(this.zoom_amount);
    }
    
}
