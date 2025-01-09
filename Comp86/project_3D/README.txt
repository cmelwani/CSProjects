
Cheryl Melwani
Comp86 Assignment 10
Sophomore Class (Year of 2023)

Highlighting how to run your program:

The 3D world that I've created is one that resembles my Java project slightly. 
The program consists of three 3D objects: factory workers, a board, and a set 
of building blocks. The simulation shows three factory workers where all of
their hats are rotating. The simulation also has a button that moves
the set of building blocks either left or right on the screen.

Inheritance Hierarchy: 
Super Class --> Child Class 

THREE.Object3D --> Scene
               --> Worker
               --> Board
               --> BuildingBlocks


A list of 3D object classes:

Scene: The 3D object scene class is what instatiates the objects
created to put onto the screen. This class handles the creation
of the worker, board, and buildingblocks as well as calls the
tick function of all workers and handles the functionality of 
my buttons to move around the buildingblocks.

Worker: The 3D object Worker class creates a Worker on the screen that has
arms, legs, a torso, a hat, and a head. These body parts are created 
by using different Three.js shapes and positioning them so that they look
like one complex shape. I create multiple instances of this
Worker on the screen in my Scene class. The colors were chosen to mimic
the vehicle that I chose for my java project.

Board: The 3D object Board class creates a box at the bottom of the 
factory workers and building blocks that acts like a floor. I used 
Three.js's BoxGeometry to create the board at the bottom and changed
the height and width accordingly. 

BuildingBlocks: The 3D object BuildingBlocks class creates a set 
of buildingblocks that are (theoretically) used by the factory
workers and fit the whole story. They are colored in red to 
look like bricks. The BuildingBlocks are made out of two boxes 
and one cone stacked on top of each other. 

IMPORTANT NOTE FOR MY PROGRAM:
Sometimes when you scroll down, because of the 3D world it's
hard to scroll back up and see the buttons that control
the horizontal movement of the building blocks so just
wanted to put a note here to make it aware! 