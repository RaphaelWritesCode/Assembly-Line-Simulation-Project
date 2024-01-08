# Assembly Line Simulation Project

This C++ project, utilizing Object-Oriented Programming (OOP) principles, simulates an assembly line. It demonstrates the application of OOP concepts such as encapsulation, inheritance, and polymorphism to create a realistic and complex system.

## Table of Contents
- [Project Description](#project-description)
- [Key Components](#key-components)
- [OOP Concepts Utilized](#oop-concepts-utilized)

## Project Description
The simulation models a functional assembly line, where multiple stations are responsible for handling specific stock items and processing customer orders. The main objective is to manage these orders and evaluate the performance of the assembly line based on the completion of these orders.

### Overview
- **Objective**: Implementing OOP principles in C++ to simulate an assembly line environment.
- **Focus**: Efficient management and processing of customer orders across various stations.

## Key Components
1. **`Utilities` and `Station` Classes**
   - `Utilities`: Manages parsing of input files and token extraction.
   - `Station`: Manages station-specific information, including item handling and order processing.

2. **`CustomerOrder` Module**
   - Manages the orders as they move through the assembly line and are processed at each station.

3. **`Workstation` and `LineManager` Modules**
   - `Workstation`: Represents an active station on the assembly line.
   - `LineManager`: Manages the workflow and order movement along the assembly line.

## OOP Concepts Utilized
- **Encapsulation**: Enclosing data and functions in classes to ensure data integrity.
- **Inheritance**: Using base classes to provide common functionalities extended by derived classes.
- **Polymorphism**: Using virtual functions and overrides for dynamic handling of station and order types.
- **Class Design**: Structuring classes with single responsibilities for modularity and maintainability.

