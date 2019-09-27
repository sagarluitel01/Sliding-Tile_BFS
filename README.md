# Sliding-Tile_BFS

A sliding tile puzzle is a rectangular grid of tile with one empty space. We can slide a tile into an adjacent empty space. The goal of the game is to arrange the tiles from initial state to a given goal state. This progrom Solve the puzzle using Breadth-first search Algorithm. It reads the JSON file which contain initial state and goal state of N x N matrix with value of N. Then It parse the JSON object and sote the matrix in 2d vector. Then It creats node with initial matrix, blak space, lavel (distance from root node), and parent node (so that it will be easier to print the parh.) The program then search for the goal state using BFS and Queue data structures. 

                                      Initail           Goal
                
                                        103             123
                                        426             456 
                                        758             780

                                