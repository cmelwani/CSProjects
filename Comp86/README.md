# Comp 86 – Object-Oriented Programming for Graphical User Interfaces

**School:** Tufts University · **Languages:** Java (Swing/AWT), JavaScript (HTML5 Canvas, Three.js/WebGL)

## Overview
Comp 86 covers designing interactive programs with object-oriented techniques: event-driven programming, widget hierarchies, model/view separation, animation, and non-traditional interfaces such as 3D graphics and emotion recognition. Most of the work is a single semester-long Java project: a **pandemic factory simulation**, built one assignment at a time. Later assignments move the same ideas into the browser.

## Skills demonstrated
- **Event-driven GUI programming:** Swing components, listeners, layout managers, mouse picking
- **OO design:** inheritance hierarchies (`Vehicle` → `Worker`/`Manager`/`Custodian`/`Coronavirus`), aggregation, separating the model from the view
- **Animation and interaction:** timer-driven animation, collision detection, panning and zooming
- **3D graphics:** building scene graphs in Three.js from basic shapes, lighting, animation
- **Non-WIMP interfaces:** webcam-based emotion detection that changes what the UI shows

## Highlighted projects
### `VirusGame` – Pandemic factory simulation (Java Swing)
The finished semester project. A factory floor is filled with workers, managers, and custodians while coronavirus particles move around the screen. The player selects a person with the mouse (a border highlights the selection) and moves them with buttons to avoid the virus. Each collision lowers everyone's health by 20, and a status label shows the current health.
- **Animation:** `TimerButton` starts and stops a Swing timer that calls each object's `tick`.
- **View controls:** `PanButton` and `ZoomButton` transform the canvas.
- **Class hierarchy:** `JFrame` → `Main`; `JPanel` → `Canvas`, `Background`, `Vehicle` → (`Worker`, `Manager`, `Custodian`, `Coronavirus`); `JButton` → `Button`, `TimerButton`, `PanButton`, `ZoomButton`. A UML diagram is included as a PDF.
```bash
cd Comp86/VirusGame && javac *.java && java Main
```

### `EmotionRecognition` – Emotion-aware web interface
Uses the **Affectiva** JavaScript SDK to read the user's facial expression through the webcam. `affectiva_test.html` classifies the face as *happy*, *sad*, *mad*, or *surprised* (a confidence score above 75) and adjusts the page to match: emotion-specific images, animations, and a matching Spotify playlist link. `affectiva_original.html` is the SDK's baseline demo. `3D_world.html` (balloons) and `3D_ghost.html` (ghosts) are companion Three.js scenes. Open the pages in a browser and allow camera access.

### `project_3D` – 3D factory world (Three.js)
`assignment10.html` recreates the Java project's factory in 3D. The `Scene`, `Worker`, `Board`, and `BuildingBlocks` classes extend `THREE.Object3D`, and each worker is built from boxes, cylinders, and spheres. The workers' hats spin, and buttons slide the building blocks left and right. `Robot*.html` and `Stereo.html` are course example scenes that I studied.

## All folders
| Folder | Summary |
|--------|---------|
| `hw1` | Assignment 1: a window with a Button, TextField, ComboBox, and ScrollBar; each widget's events print to stdout |
| `hw2` | An earlier working copy of the factory simulation (the same source as `VirusGame`) with design notes in `readme.txt` |
| `hw8` | HTML5 Canvas drawing: two squares with "Make Bigger/Smaller" buttons that redraw the canvas |
| `VirusGame` | Final Java simulation (see above) |
| `project_3D` | Three.js 3D world (see above) |
| `EmotionRecognition` | Affectiva and Three.js emotion-aware interface (see above) |
| `Comp 86 hw/` | Archived ZIPs of each assignment's submission (Assignments 1–7 and 10), showing step by step how the simulation grew: widgets → canvas and radio buttons → `Worker`/`Manager` → `Vehicle` hierarchy and `Model` → text field input → timer animation and `Coronavirus` → pan and zoom |
