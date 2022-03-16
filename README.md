# Dijkstras-Routing-Algorithm
A program to implement Dijkstra's routing algorithm for cities near Calgary

This program was made as an assignment for a computer networks class.
An example file can be found in map.txt to see what the input should look like. YYC must exist somewhere in the file.
The City and Edge classes work together to simulate a map of the routes that are read from the file.
Routing.cpp reads the file and creates all the cities and edges of the map. The Calgary city is then called to find all the cities near itself.
The program prints out the distance from Calgary to every other city that Calgary can reach.
