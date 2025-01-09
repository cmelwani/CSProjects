
Details:
    Cheryl Melwani
    Comp86 Assignment 7
    Sophomore Class (Year of 2023)
    
Instructions on how to compile and run your program.
Step 1: javac Main.java
Step 2: java Main 

Description of the kind of simulation (i.e theme, layout, types of vehicles).

This program will be a simulation of a factory during this pandemic.
The type of factory is still to be determined.
There will be different types of workers, managers, and custodials that 
are the "vehicles" in the program. The different vehicles will have 
different capabilities. The map will be the factory and I plan to have 
different sections of the factory outlined for different purposes. 
The simulation will also take into account the pandemic where social 
distancing guidelines will be implemented by the software (but I'm still 
unclear on the specific details of how).
 
Description of User Interface, and how it will work/what it will do.

The user interface will have buttons that will be able to do different
features such as move a vehicle or stop them from moving. 
The interface will also have a combobox or drop down menu that allows 
the user to pick the specific vehicle that they'd like to move or change
(the functionality of the combobox still needs to be implemented).
There is also a radio button widget that will allow the user to move
the vehicle upbrutly whether it be to the outside, or to socially distance
6 ft from other co-workers. There will be other features implemented in the 
future and some features changed depending on what we learn in the future. 


I added a Manager, Worker, and Custodian class that all extends from the
super class Vehicle. Vehicle holds all the functionalities that my 
3 vehicles have in common. I also added a background that shows the 
factory, however, I still have to adjust it properly to fit the entire
screen or more of the screen and not just the center of the borderlayout.
All of the move buttons have functionality and work to move only the 
Factory Worker for now. I intend on making the buttons work on all the 
vehicles. I also need to change the move buttons so that they move 
the vehicles respective to their original position and not to the 
same coordinates everytime a "Move Right" button (for example) is
pressed. 

Additions from old homework:

The Manager, Worker, and Custodian all move once the "Start Animation"
button is clicked. They stop moving once the "Stop Animation" button
is clicked. The label of the button changes once that specific button
is clicked. I also implemented an add function where the user can choose
a specific vehicle to add. The buttons that move the vehicle left, right, up, 
and down only apply to one of my vehicles and not all of them. A text 
field was also added to the program that allows the user to set the speed of
the vehicle. 

All of the move buttons are applied to all of my person vehicles! The animation
now works to a better extent. I changed the start and stop simulation buttons 
and changed how my timer and tick functions worked because I was doing it 
incorrectly before. I also applied mouse clicking so when you click on a certain vehicle, 
a rectangular border appears and you can move them however you want. 
I also added a coronavirus object that collides with the person vehicles. 
When it collides the health of the people in the factory decrease by a factor of 20. 
I also increased the size of my background. Lastly, I added a state of the game label 
onto my JPanel that shows the health of the workers on the screen and changes 
if a collision happens.

NEW ADDITIONS:
For assignment 7 I cleaned up the code, commented on important functions and classes.
I also added a pan and zoom function where users can pan left and right as well as 
zoom in and out of the screen using buttons. I also edited some of my instance variables
to make sure that they are protected/private. I also cleaned up commented code 
and make sure everything looks clean and follows the guidelines of the spec. 

Include your Design Documentation (outlined in “Programming and design 
documentation practices”)

Inheritance Hierarchy: 
Super Class --> Child Class 

JButton --> Button
        --> TimerButton
        --> ZoomButton
        --> PanButton
JPanel --> Canvas 
       --> Vehicle
       --> Background
JFrame --> Main
Vehicle --> Worker
        --> Manager
        --> Custodian
        --> Coronavirus

Aggregation Hierarchy:                   
Object ---> Component ---> Canvas (1)
                                          
Object ---> Component ---> Button (6)            
                                         ---> Panel p2
Object --> Component --> Panel 

Object --> Panel --> Background 

Object --> Panel --> Vehicle --> Worker & Manager & Custodian & Coronavirus

Object --> Component --> TimerButton & ZoomButton & PanButton 



Acknowledgements:
I swearched up how to use the borderlayout and how to get the color maroon. 
I used the TA's code for mousepicking and I used it as inspiration for the 
collision part of the assignment. I searched up how to add a border
to a jpanel and used that information in my code. 
I used oracle to get most of my information. I also used snippets of code 
from my Professor in class and from my previous hw1, hw2, hw3, and hw4 
assignment. 


Instructions for the user to play my simulation: 
The health of all people in the factory is at a 100 in the beginning 
of the simulation. When a person gets hit by the coronavirus then
the health of the workers reduce by a factor of 20. The goal of
the game is to move the people by clicking and using the 
move buttons to make sure that they don't get killed by the 
coronavirus. Users can also zoom in and out, as well as pan 
left and right using the buttons at the bottom of the screen. 

