
//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file creates a TimerButton that handles 
//starting and stoping the animation portion of the simulation.

import javax.swing.*;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class TimerButton extends JButton implements ActionListener {
    private String label = "";
    private Timer timer;
    private Boolean animationTrigger;
    private TimerButton c_button;

    TimerButton(String label, Timer timer, Boolean animationTrigger) {
        this.label = label;
        setText(label);
        Color maroon = new Color (128, 0, 0);
        //found it on the internt to find the color maroon. 
        setForeground(maroon);
        setFont(new Font("Times New Roman", Font.BOLD, 12));

        this.timer = timer;
        this.animationTrigger = animationTrigger;
        if(animationTrigger) {
            setEnabled(false);
        }
        addActionListener(this);
    }

    public void addCButton(TimerButton c_button) {
        this.c_button = c_button;
    }

    public void actionPerformed(ActionEvent e) {
        System.out.println(label);
        if(animationTrigger) {
            timer.start();
        } else {
            timer.stop();
        }
        setEnabled(false);
        c_button.setEnabled(true);
    }
    
}
