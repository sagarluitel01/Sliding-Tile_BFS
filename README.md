# Sliding-Tile_BFS

A sliding tile puzzle is a rectangular grid of tile with one empty space. We can slide a tile into an adjacent empty space. The goal of the game is to arrange the tiles from initial state to a given goal state. This progrom Solve the puzzle using Breadth-first search Algorithm. It reads the JSON file which contain initial state and goal state of N x N matrix with value of N. Then It parse the JSON object and sote the matrix in 2d vector. Then It creats node with initial matrix, blak space, lavel (distance from root node), and parent node (so that it will be easier to print the parh.) The program then search for the goal state using BFS and Queue data structures. 

                                       Initail            Goal
                
                                        1 0 3             1 2 3
                                        4 2 6             4 5 6 
                                        7 5 8             7 8 0

                                        / | \
                                      /   |   \
                                    /     |     \
                                  /       |       \
                                
            0 1 3                       1 2 3                    1 3 0 
            4 2 6                       4 0 6                    4 2 6
            7 5 8                       7 5 8                    7 5 8
                                            
              |                         / | \                      | 
              |                       /   |   \                    |  
              |                     /     |     \                  |
              
            4 1 3           1 2 3       1 2 3       1 2 3        1 3 6
            0 2 6           0 4 6       4 5 6       4 6 0        4 2 0
            7 5 8           7 5 8       7 0 8       7 5 8        7 5 8
            
            / |              / |         / \                    
           /  |             /  |        /   \      
          /   |            /   |       /     \
                                                                  
    4 1 3   4 1 3    0 2 3   1 2 3  1 2 3   1 2 3                               
    2 0 6   7 2 6    1 4 6   7 4 6  4 5 6   4 5 6 ----> GOAL 
    7 5 8   0 5 8    7 5 8   0 5 8  0 7 8   7 8 0

