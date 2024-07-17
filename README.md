# BrickGame Snake
Summary: In this project, you will implement the Snake game in the C++ programming language in the object-oriented programming paradigm.

💡 [Tap here](https://new.oprosso.net/p/4cb31ec3f47a4596bc758ea1861fb624) **to leave your feedback on the project**. It's anonymous and will help our team make your educational experience better. We recommend completing the survey immediately after the project.

# Contents

- [BrickGame Snake](#brickgame-snake)
  - [Contents](#contents)
  - [Introduction](#introduction)
- [Chapter I](#chapter-i)
  - [General Information](#general-information)
    - [Snake](#snake)
    - [MVC Pattern](#mvc-pattern)
    - [MVP Pattern ](#mvp-pattern)
    - [MVVM Pattern ](#mvvm-pattern)
- [Chapter II](#chapter-ii)
  - [Project Requirments](#project-requirements)
    - [Part 1. Main task](#part-1-main-task)
    - [Part 2. Bonus. Scoring and game record](#part-2-bonus-scoring-and-game-record)
    - [Part 3. Bonus. Level mechanics](#part-3-bonus-level-mechanics)

## Introduction

The project consists of two separate components to implement the Snake game: a library responsible for implementing the game logic and a desktop GUI.

The developed library must also be connected to the console interface of BrickGame v1.0. The console interface must fully support the new game.

The Tetris game developed in BrickGame v1.0 must be connected to the desktop interface developed in this project. It must fully support the game.

## Chapter I 
# General information

Remember to use finite-state machines to formalize the logic of the game. You can find descriptions and examples of FMS to refresh your knowledge [here](materials/brick-game-v1.0.md).

### Snake

![Snake](misc/images/snake-game.png)

The player controls a snake that moves forward continuously. The player changes the direction of the snake by using the arrows. The goal of the game is to collect "apples" that appear on the playing field. The player must avoid hitting the walls of the playing field. After "eating" the next "apple", the length of the snake increases by one. The player wins when the snake reaches the maximum size (200 "pixels"). If the snake hits a boundary of the playing field, the player loses.

The game was based on another game called Blockage. It had two players controlling characters that left a trail that you couldn't run into. The player who lasted the longest won. In 1977, Atari released Worm, which was now a single player game. The most popular version of the game is probably the 1997 version released by the Swedish company Nokia for their Nokia 6110 phone, developed by Taneli Armanto.

### MVC Pattern

The Model-View-Controller (MVC) pattern is a scheme for dividing application modules into three separate macro components: a model that contains the business logic, a view - a form of user interface for interacting with the program, and a controller that modifies the model based on user actions.

The concept of MVC was described by Trygve Reenskaug in 1978 while working on the Smalltalk programming language at Xerox PARC. Steve Burbeck later implemented the pattern in Smalltalk-80. The final version of the MVC concept was not published until 1988 in Technology Object magazine. After that, the design pattern began to evolve. For example, a hierarchical version of HMVC was introduced; MVA, MVVM.

The main need for this pattern is related to the developers' desire to separate the program's business logic from the views, which allows them to easily replace views and reuse once-implemented logic in other contexts. A model that is separate from the view and a controller that interacts with it allows you to efficiently reuse or modify code that has already been written.

The model stores and accesses key data, performs operations defined by the program's business logic, and manages the part of the program responsible for all algorithms and information handling processes. These models, when modified by the controller, affect the display of information on the user interface view. The class library that implements the logic of the snake game must act as a model in this program. This library must provide all the necessary classes and methods to execute the game mechanics. This is the business logic of this program, as it provides the means to solve the problem.

The controller is a thin macro component that performs the modification of the model. All requests for model changes are generated through the controller. It looks like a kind of "facade" for the model in the code, that is, a set of methods that already work directly with the model. It is called thin because the ideal controller contains no additional logic other than calling one or more methods of the model. The controller acts as a link between the interface and the model. This allows the model to be completely encapsulated from the view. Such separation is useful because it allows the view code to know nothing about the model code and to refer only to the controller, whose interface of provided functions is unlikely to change significantly. The model, on the other hand, can change significantly, and when "moving" to other algorithms, technologies, or even programming languages in the model, only a small portion of the code in the controller directly related to the model needs to be changed. Otherwise, it is likely that much of the interface code would have to be rewritten, as it is highly dependent on the model implementation. Thus, when the user interacts with the interface, he or she calls controller methods that modify the model.

The view contains all the code associated with the program interface. There should be no business logic in the code of a perfect interface. It is just a form for user interaction.

![MVC-Process](misc/images/MVC-Process.png)

### MVP Pattern

The MVP pattern shares two components with MVC: model and view. However, it replaces the controller with a presenter.

The presenter implements the interaction between the model and the view. When the view notifies the presenter that the user has done something (e.g., pressed a button), the presenter decides to update the model and synchronizes all changes between the model and the view. However, the presenter does not communicate directly with the view. Instead, it communicates through an interface. This allows all components of the application to be tested individually afterwards.

![MVP-Process](misc/images/MVP-Process.png)

### MVVM Pattern

MVVM is a more modern evolution of MVC. The main goal of MVVM is to provide a clear separation between the view and model layers.

MVVM supports bi-directional data binding between View and ViewModel components.

The view acts as a subscriber to property value change events provided by the ViewModel. When a property in the view model changes, it notifies all subscribers, and the view in turn requests the updated property value from the view model.  When the user interacts with an UI element, the view calls the appropriate command provided by the view model.

A view model is both an abstraction of a view and a wrapper of data from the model to be bound. In other words, it contains the model that has been transformed into the view, as well as the commands that the view can use to manipulate the model.

![MVVM-Process](misc/images/MVVM-Process.png)

## Chapter II 
## Project Requirements

### Part 1. Main task

Implement BrickGame v2.0:

- The program must be developed in C++ language of C++17 standard.
- The program must consist of two parts: a library that implements the logic of the snake game and a desktop interface.
- A finite state machine must be used to formalize the logic of the game.
 The library must conform to the specification given in the first part of BrickGame (you can find it in materials/library-specification.md).
- The program library code must be in the `src/brick_game/snake` folder.
- The program interface code must be in the `src/gui/desktop` folder.
- Follow Google Style when writing code.
- Classes must be implemented within the `s21` namespace.
- The library that implements the game logic must be covered by unit tests. 
- Pay special attention to checking FMS states and transitions. Use the GTest library for testing. The coverage of the library with tests must be at least 80 percent.
- The program must be built using a Makefile with the standard set of targets for GNU programs: all, install, uninstall, clean, dvi, dist, tests. The installation directory can be arbitrary.
- The implementation must have a GUI based on one of the GUI libraries with an API for C++17:
  - Qt
  - GTK+
- The program must be implemented using the MVC pattern. Also 
  - There must be no business logic code in the view code;
  - There must be no interface code in the model, presenter, and view model;
  - Controllers must be thin.
- Copy the game logic library folder from the BrickGame v1.0 project.
- The desktop interface must support the game from the BrickGame v1.0 project.
- Copy the console interface folder from the BrickGame v1.0 project.
The console interface must support the snake.
- The following mechanics must be present in the Snake game:
  - The snake must move on its own, one block ahead, when the game timer runs out.
  - When the snake hits an "apple", its length increases by one.
  - When the length of the snake reaches 200 units, the game ends and the player wins.
  - If a snake hits a field boundary or itself, the game ends with the player losing.
  - The user can change the direction of the snake's movement using the arrows, and the snake can only turn left and right relative to the current direction of movement.
  - The user can speed up the snake's movement by pressing the action key.
- The initial length of the snake is four "pixels".
- The playing field is 10 "pixels" wide and 20 "pixels" high.
- Prepare a diagram showing all states and transitions between them for the implemented FMS for project submission.

### Part 2. Bonus. Scoring and game record

Add the following mechanics to the game:

- scoring;
- storing maximum points.

This information must be passed and displayed by the user interface in the sidebar. The maximum score must be stored in a file or an embedded DBMS and saved between program runs.

The maximum score must be changed during the game if the user exceeds the current maximum score.

Points are scored as follows: eating another "apple" adds one point.

### Part 3. Bonus. Level Mechanics

Add level mechanics to the game. Each time a player gains 5 points, the level increases by 1. Increasing the level increases the snake's speed. The maximum number of levels is 10.
