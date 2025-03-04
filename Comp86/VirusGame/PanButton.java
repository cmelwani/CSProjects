//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file creates a button that handles the 
//the panning of the screen. 

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class PanButton extends JButton implements ActionListener{
    private Model model;
    private int pan_x;
    private int pan_y;

    public PanButton(Model model, String label, int pan_x, int pan_y) {
        this.model = model;
        this.setText(label);
        Color maroon = new Color (128, 0, 0);
        //found it on the internt to find the color maroon. 
        setForeground(maroon);
        setFont(new Font("Times New Roman", Font.BOLD, 12));
        this.pan_x = pan_x;
        this.pan_y = pan_y;
        this.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        this.model.pan(this.pan_x, this.pan_y);
    }
}
