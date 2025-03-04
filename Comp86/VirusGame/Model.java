//Name: Cheryl Melwani
//Email: cheryl.melwani@tufts.edu
//Description: This file creates a Model class that holds all of 
//the data necessary to create the simulation. 
//Instances of vehicles are created in this class. 
//An instance of Module is created in main.

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;

public class Model {
    ArrayList<Vehicle> v = new ArrayList<Vehicle>();
    ArrayList<Vehicle> cv = new ArrayList<Vehicle>();
    ArrayList<Vehicle> person = new ArrayList <Vehicle>();

    private Worker worker1;
    private Manager manager1;
    private Custodian custodian1;
    private Coronavirus cv1, cv2, cv3, cv4, cv5, cv6, cv7, cv8;
    private Background b;
    private Canvas canvas;
    private Vehicle selectedVehicle;
    private int zoom;
    private int pan_x;
    private int pan_y;
    private int pan_mult = 10;

    Model(Canvas canvas) {
        this.canvas = canvas;
        worker1 = new Worker(100, 100);
        manager1 = new Manager(200, 200);
        custodian1 = new Custodian(300, 300);
        v.add (worker1);
        person.add(worker1);
        v.add (manager1);
        person.add(manager1);
        v.add(custodian1);    
        person.add(custodian1);    
        cv1 = new Coronavirus(100, 800);
        cv2 = new Coronavirus(200, 800);
        cv3 = new Coronavirus(300, 800);
        cv4 = new Coronavirus(400, 800);
        cv5 = new Coronavirus(500, 800);
        cv6 = new Coronavirus(600, 800);
        cv7 = new Coronavirus(700, 800);
        cv8 = new Coronavirus(800, 800);
        v.add(cv1);
        v.add(cv2);
        v.add(cv3);
        v.add(cv4);
        v.add(cv5);
        v.add(cv6);
        v.add(cv7);
        v.add(cv8);
        cv.add(cv1);
        cv.add(cv2);
        cv.add(cv3);
        cv.add(cv4);
        cv.add(cv5);
        cv.add(cv6);
        cv.add(cv7);
        cv.add(cv8);
        b = new Background();

        selectedVehicle = worker1;
        this.zoom = 1;
        this.pan_x = 0;
        this.pan_y = 0;
    }

    public void zoom(int zoom) {
        this.zoom += zoom;
        canvas.repaint();
    }

    public void pan(int pan_x, int pan_y) {
        this.pan_x += pan_x * this.pan_mult;
        this.pan_y += pan_y * this.pan_mult;
        canvas.repaint();
    }

    //Purpose: To figure out which vehicle the user picks through mouse 
    //clicking.
    public void correlate(int x, int y) {
        for (Vehicle vehicles: v) {
            if(vehicles.pickCorrelation(x, y)) {
                this.selectedVehicle = vehicles;
            }
        }
        canvas.repaint();
    }

    public void draw (Graphics g) {
       b.draw(g);
        for (Vehicle vehicle: v) {
            vehicle.draw(g, this.zoom, this.pan_x, this.pan_y);
            if(selectedVehicle == vehicle) {
                vehicle.highlight(g, this.zoom, this.pan_x, this.pan_y);
            }
        }
    }

    public void animate () {
        for (Vehicle vehicle: v) {
            vehicle.tick();
        }
    }

    public void move_vehicle(int x, int y) {
        selectedVehicle.move(x, y);
        canvas.repaint();
    }

    //Purpose: is to add people on to the screen. This function takes care 
    //of adding the different types of people onto the screen. It can add
    //all vehicles except for the coronavirus. This allows the user to 
    //add what vehicles they desire on to the simulation.
    public void addVehicle(String v_type) {
        int counter1 = 1;
        int counter2 = 1;
        int counter3 = 1;
        if(v_type == "Factory Worker") {
            counter1++;
            Worker worker = new Worker(200*counter1, 200);
            v.add(worker);
            person.add(worker);
        }
        else if(v_type == "Manager") {
            counter2++;
            Manager manager = new Manager(300*counter2, 200);
            v.add(manager);
            person.add(manager);
        }
        else if(v_type == "Custodian") {
            counter3++;
            Custodian custodian = new Custodian(400*counter3, 200);
            v.add(custodian);
            person.add(custodian);
        }
        canvas.repaint();
    }

    //Purpose: checks if there is a collision between the people on the
    //simulation and the coronavirus. If there is a collision then the 
    //people are moved to a lower position on the screen.
    public boolean checkCollisions() {
        for(Vehicle p: person) {
            for(Vehicle corona: cv) {
                int p_x = p.getX();
                int p_y = p.getY();
                int c_x = corona.getX();
                int c_y = corona.getY();
                int delta_x = Math.abs(p_x - c_x);
                int delta_y = Math.abs(p_y - c_y);
                if(delta_x <= 30 && delta_y <= 30) {
                    p.move(0, 200);
                    return true;
                    // System.out.println("Collision Happened");
                }
            }
        }
        return false;
    }
}


