//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file creates instances of other classes. It calls 
//Button.java, ComboBox.java, Radio.java, and Canvas.java and more.
//This file sets up the window, and the layout of the window as well as 
//the panels.

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

import javax.swing.border.Border;
import javax.swing.BorderFactory;


public class Main extends JFrame implements ActionListener {
    public static void main (String [] args) {
        java.awt.EventQueue.invokeLater (new Runnable() {
            public void run() {
		        new Main (); //creates an instance of main
            }
        });
    }

    private Canvas c1;
    private Model model;
    private int score;
    private JLabel label;

    public Main () {
        setSize (600, 700); //sets the window size 
        setLayout (new BorderLayout()); //sets layout of window

        JPanel p2 = new JPanel(new GridLayout(7,1,10,5));
        //changing the size of the panel 
        JPanel p3 = new JPanel();

        c1 = new Canvas ();
        model = new Model (c1);
        c1.setModel (model);

        add(c1, BorderLayout.CENTER);

        add(p2, BorderLayout.EAST);
        add(p3, BorderLayout.SOUTH);
        p2.setBackground(Color.black);
        p3.setBackground(Color.black);

        label = new JLabel();
        label.setHorizontalAlignment(JLabel.CENTER);
        score = 100;
        label.setText("Health of People: " + String.valueOf(score));
        // Color maroon = new Color (128, 0, 0);
        label.setForeground(Color.WHITE);
        Border border = BorderFactory.createLineBorder(Color.WHITE, 2);
        label.setBorder(border);
        p2.add(label);

        Button right = new Button ("Move Right", model); 
        p2.add(right);
        Button left = new Button ("Move Left", model);
        p2.add(left);
        Button down = new Button ("Move Down", model);
        p2.add(down);
        Button up = new Button ("Move Up", model);
        p2.add(up);
        Button add_worker = new Button ("Add Worker", model);
        p2.add(add_worker);
        Button add_manager = new Button ("Add Manager", model);
        p2.add(add_manager);
        Button add_custodian = new Button ("Add Custodian", model);
        p2.add(add_custodian);

        Timer timer = new Timer (100, this);
        timer.start();

        TimerButton start_button = new TimerButton("Start Animation", timer, true);
        TimerButton stop_button = new TimerButton("Stop Animation", timer, false);
        p2.add(start_button);
        p2.add(stop_button);
        start_button.addCButton(stop_button);
        stop_button.addCButton(start_button);

        PanButton pan_right = new PanButton(model, "Pan Right", 1, 0);
        PanButton pan_left = new PanButton(model, "Pan Left", -1, 0);
        ZoomButton zoom_out = new ZoomButton(model, "Zoom Out", -1);
        ZoomButton zoom_in = new ZoomButton(model, "Zoom In", 1);
        p3.add(pan_right);
        p3.add(pan_left);
        p3.add(zoom_in);
        p3.add(zoom_out);

        setVisible (true); //shows the window when you run the progam
        setDefaultCloseOperation (EXIT_ON_CLOSE); //closes window
    }

    public void actionPerformed (ActionEvent e) {
        model.animate();
        //model.checkCollisions();
        if(model.checkCollisions()) {
            score -= 20;
            refreshLabel();
        }
        c1.repaint ();
    }

    public void refreshLabel() {
        label.setText("Health of People:" + String.valueOf(score));
    }

}