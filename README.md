# BrickGame Snake
Summary: In this project, you will implement the Snake game in the C++ programming language in the object-oriented programming paradigm.

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

The developed library must also be connected to the console interface from BrickGame v1.0. The console interface needs to fully support the new game.

The Tetris game developed in BrickGame v1.0 needs to be connected to the desktop interface developed in this project. It has to fully support the game.

## Chapter I 
# General information

Remember to use finite-state machines to formalize the logic of the game. You can find descriptions and examples of FMS to refresh your knowledge [here](materials/brick-game-v1.0.md).

### Snake

![Snake](misc/images/snake-game.png)

The player controls a snake that continuously moves forward. The player changes the direction of the snake using the arrows. The goal of the game is to collect "apples" appearing on the playing field. The player must avoid hitting walls of the playing field. After "eating" the next "apple" the length of the snake increases by one. The player wins if the snake reaches the maximum size (200 "pixels"). If the snake bumps into a boundary of the playing field, the player loses.

The game was developed on the basis of another one called Blockage. It had two players controlling characters that left a trail that you mustn’t crash into. The player who lasted longer would win. In 1977, Atari released the Worm, which was now a single-player game. The most popular version of the game is probably the 1997 version released by the Swedish company Nokia for their Nokia 6110 phone, developed by Taneli Armanto.

### MVC Pattern

The MVC (Model-View-Controller) pattern is a scheme for dividing application modules into three separate macro components: a model containing business logic, a view - a form of user interface for interacting with the program, and a controller that modifies the model based on user actions.

The concept of MVC was described by Trygve Reenskaug in 1978, while working at the Xerox PARC research center on the Smalltalk programming language. Steve Burbeck later implemented the pattern in Smalltalk-80. The final version of the MVC concept was only published in 1988 in the Technology Object magazine. Thereafter, the design pattern began to evolve. For example, a hierarchical version of HMVC was introduced; MVA, MVVM.

The main need for this pattern is related to the developers' desire to separate the program's business logic from the views, which allows them to easily replace views and reuse once-implemented logic in other contexts. A model separated from the view and a controller to interact with it allows you to efficiently reuse or modify code that has already been written.

The model stores and accesses the main data, performs operations defined by the business logic of the program, i.e. manages the part of the program that is responsible for all algorithms and information handling processes. These models, when modified by the controller, affect the display of information on the user interface view. The class library that performs the logic of the snake game must act as a model in this program. This library must provide all the necessary classes and methods to perform the game mechanics. This is the business logic of this program, as it provides the means to solve the problem.

The controller is a thin macro component that performs the modification of the model. All requests for model changes are generated via controller. It looks like a kind of "facade" for the model in the code, that is, a set of methods that already work directly with the model. It is called thin because the ideal controller contains no additional logic other than calling one or more methods of the model. The controller acts as a linking element between the interface and the model. This allows the model to be completely encapsulated from the View. Such a separation is useful because it allows the view code to know nothing about the model code and to refer to the controller only, whose interface of provided functions is not likely to change significantly. The model, on the other hand, can undergo significant changes, and, when "moving" to other algorithms, technologies or even programming languages in the model, only a small section of code in the controller directly related to the model will need to be changed. Otherwise, it is likely that much of the interface code would have to be rewritten, as it would be highly dependent on the model implementation. Thus, when interacting with the interface, the user calls controller methods that modify the model.

The view includes all the code associated with the program interface. There should be no business logic in the code of a perfect interface. It only is a form for user interaction.

![MVC-Process](misc/images/MVC-Process.png)

### MVP Pattern

The MVP pattern has two components in common with MVC: model and view. But it replaces the controller with a presenter.

The presenter implements the interaction between the model and the view. When the view notifies the presenter that the user has done something (e.g., pressed a button), the presenter decides to update the model and synchronizes all changes between the model and the view. However, the presenter is not communicating with the view directly. Instead, it communicates via an interface. This allows all components of the application to be tested individually afterwards.

![MVP-Process](misc/images/MVP-Process.png)

### MVVM Pattern

MVVM is a more modern evolution of MVC. The main goal of MVVM is to provide a clear separation between the view and model levels.

MVVM supports two-way data binding between View and ViewModel components.

The view acts as a subscriber to property value change events provided by the ViewModel. If a property has changed in the view model, it notifies all subscribers about it, and the view, in turn, requests the updated property value from the view model.  If the user interacts with an interface element, the view calls the corresponding command provided by the view model.

A view model is on the one hand an abstraction of a view, and on the other hand a wrapper of data from the model to be bound. In other words, it contains the model converted to the view, as well as the commands the view can use to affect the model.

![MVVM-Process](misc/images/MVVM-Process.png)

## Chapter II 
## Project Requirements

### Part 1. Main task

Implement BrickGame v2.0:

- The program must be developed in C++ language of C++17 standard.
- The program must consist of two parts: a library that implements the logic of the snake game and a desktop interface.
- A finite-state machine must be used to formalize the logic of the game.
 The library must conform to the specification given in the first part of BrickGame (you can find it in materials/library-specification.md)
- The program library code must be located in the `src/brick_game/snake` folder.
- The program interface code must be located in the `src/gui/desktop` folder
- Stick to Google Style when writing code.
- Classes must be implemented within the `s21` namespace
- The library that implements the game logic must be covered by unit tests. - Pay special attention to checking the FMS states and transitions. Use GTest library for tests. The coverage of the library with tests must be at least 80 percent.
- The program must be built using a Makefile with the standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests. Installation directory can be arbitrary
- The implementation must be with a GUI, based on one of the GUI libraries with an API for C++17:
  - Qt
  - GTK+
- The program must be implemented using the MVC pattern. Also: 
  - there must be no business logic code in the view code;
  - there must be no interface code in the model, presenter and view model
  - controllers must be thin.
- Copy the library folder with the game logic from the BrickGame v1.0 project.
- The desktop interface must support the game from the BrickGame v1.0 project.
- Copy the folder with the console interface of the game from the BrickGame v1.0 project.
The console interface needs to support the Snake.
- The following mechanics must be in the Snake game:
  - The snake must move across the field on its own, one block ahead when the game timer expires.
  - When a snake meets an "apple", its length increases by one.
  - When the length of the snake reaches 200 units, the game ends with the player winning.
  - When a snake bumps into a field boundary or itself, the game ends with the player losing.
  - The user can change the direction of movement of the snake using the arrows, and the snake can only turn left and right relative to the current direction of movement.
  - The user can speed up the movement of the snake by pressing the action key.
- The initial length of the snake is four "pixels".
- The playing field is 10 "pixels" wide and 20 "pixels" high.
- Prepare a diagram showing all states and transitions between them for the implemented FMS for project submission.

### Part 2. Bonus. Scoring and game record

Add the following mechanics to the game:

- scoring;
- storing maximum points.

This information must be passed and displayed by the user interface in the sidebar. The maximum number of points must be stored in a file or embedded DBMS and saved between program runs.

The maximum number of points must be changed during the game if the user exceeds the current maximum score.

Points will be accrued as follows: eating another "apple" adds one point.

### Part 3. Bonus. Level mechanics

Add level mechanics to the game. Each time a player gains 5 points, the level increases by 1. Increasing the level increases the speed of the snake. The maximum number of levels is 10.

 💡 [Press here](https://forms.yandex.ru/cloud/65d4b6ac84227c3db2d15b0b/)**, to give us feedback on this project**. It's anonymous and will help our team make your learning process better.
