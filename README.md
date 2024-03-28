Overview:
The project aims to develop a program that calculates the shortest path between two cities using Dijkstra's and Breadth-First Search (BFS) algorithms. The program reads city data from a file, constructs a graph representing the connections between cities, and allows users to input source and destination cities to find the shortest path. It provides functionalities to print the full path and total distance using both algorithms and saves the results to a file.

Functional Requirements:

Load Cities:

Read city data from a file named "cities.txt".
Construct a graph representing connections between cities based on the data.
Handle cases where the file is missing or improperly formatted.
Enter Source City:

Prompt the user to input the source city.
Validate the input to ensure it matches a city in the loaded data.
Handle cases where the input city is not found in the data.
Enter Destination City:

Prompt the user to input the destination city.
Validate the input to ensure it matches a city in the loaded data.
Calculate the shortest path between the source and destination cities using Dijkstra's and BFS algorithms.
Print the full path, including the distance between each pair of connected cities.
Print the total distance for Dijkstra's algorithm.
Save Results:

Provide an option to save the results of the shortest path calculations to a file named "shortest_distance.txt".
Include the full paths and total distances calculated by both algorithms in the file.
Error Handling:

Handle invalid user inputs gracefully and provide informative error messages.
Address cases where the source or destination city is not found in the loaded data.
Handle file-related errors, such as missing or improperly formatted input files.
Non-functional Requirements:

Efficiency:

Implement algorithms efficiently to minimize computation time and memory usage.
Optimize data structures and algorithms for graph traversal and shortest path calculation.
Usability:

Design a user-friendly interface with clear prompts and informative messages.
Ensure ease of use for users with varying levels of technical expertise.
Reliability:

Develop robust error-handling mechanisms to handle unexpected inputs and situations.
Test the program extensively to identify and address potential bugs and issues.
Scalability:

Design the program to handle a large number of cities and connections without significant performance degradation.
Ensure that memory usage remains reasonable even for large input datasets.
