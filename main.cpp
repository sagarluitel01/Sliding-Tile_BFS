//
//  main.cpp
//  sliding-tileBFS
//
//  Created by Sagar Luitel on 9/22/19.
//  Copyright © 2019 Sagar Luitel. All rights reserved.
//

//  n x n sliding tile puzzle using Breadth-first search Algorithm



#include <iostream>
#include "json.hpp"
#include <vector>
#include <queue>
#include <fstream>

using json = nlohmann::json;

using namespace std;

struct Node
{
    Node* parent;
    
    // stores matrix
    vector< vector<int>> matrix;
    
    int x, y;
    
    int level;
};

void print(vector< vector<int>> mat, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

Node* newNode(vector< vector<int>> matrix, int x, int y, int newX,
              int newY, int level, Node* parent)
{
    Node* node = new Node;
    
    //node's parent to know the path of node
    node->parent = parent;
    
    copy(matrix.begin(), matrix.end(), back_inserter(node->matrix));
    
    // swap blank space with one it adjacent space
    swap(node->matrix[x][y], node->matrix[newX][newY]);
    
    // how far the node from the root
    node->level = level;
    
    // update new blank tile cordinates
    node->x = newX;
    node->y = newY;
    
    return node;
}

// botton, left, top, right
int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

//check if it is safe to move
int checkMoves(int x, int y, int N)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void printTree(Node* root, int N)
{
    if (root == NULL)
        return;
    printTree(root->parent, N);
    print(root->matrix, N);
    
    printf("\n");
}

//calculate how many node are missplaced (if it is 0 then game over)
int calculateCost(vector< vector<int>> start, vector< vector<int>> goal)
{
    int count = 0;
    for (int i = 0; i < start.size(); i++)
        for (int j = 0; j < start[i].size(); j++)
            if (start[i][j] && start[i][j] != goal[i][j])
                count++;
    return count;
}

//function that dose most of the work to solve the puzzle
void solvePuzzle(vector< vector<int>> initial, int x, int y,
           vector< vector<int>> final, int N)
{
    queue<Node*> myQueue;
    queue<queue<Node*>> q;
 
    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    
    // Add root to list of live nodes;
    myQueue.push(root);
    
    q.push(myQueue);

    while (!q.empty()) {
        myQueue = q.front();
        q.pop();
        while (!myQueue.empty())
        {
            queue<Node*>tempQ;
            Node* min = myQueue.front();
            
            myQueue.pop();
            
            for (int i = 0; i < 4; i++)
            {
                if (checkMoves(min->x + row[i], min->y + col[i], N))
                {
                    Node* child = newNode(min->matrix, min->x,
                                          min->y, min->x + row[i],
                                          min->y + col[i],
                                          min->level + 1, min);

                    if (min->level != 0) {
                        if (child->x == min->parent->x && child->y == min->parent->y ) {
                            continue;
                        }
                    }
                    tempQ.push(child);
                    
                    if (calculateCost(child->matrix, final) == 0) {
                        printTree(child, N);
                        return;
                    }
                    
                }
            }
            q.push(tempQ);
        }
    }
}

// Driver code
int main()
{
    //read matrix from json file
    ifstream infile ("/nxnMatrix.json");
    json j;
    infile >> j;

    vector< vector<int>> start;  //for initial state of matrix
    vector< vector<int>> goal;   //goal matrix
    int n = 0;
       
    int ittr = 0;
    
    //parse json objct and store the matrix in vector
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        if (ittr == 0) {
            for (json::iterator it1 = it.value().begin(); it1 != it.value().end(); ++it1) {
                vector<int> tempvect;
                for (json::iterator it2 = it1.value().begin(); it2 != it1.value().end(); ++it2) {
                         tempvect.push_back(*it2);
                     }
                     goal.push_back(tempvect);
                 }
             }
        if(ittr == 1){
                n = *it;
        }
        if (ittr == 2) {
            for (json::iterator it1 = it.value().begin(); it1 != it.value().end(); ++it1) {
                vector<int> tempvect;
                for (json::iterator it2 = it1.value().begin(); it2 != it1.value().end(); ++it2) {
                    tempvect.push_back(*it2);
                }
                start.push_back(tempvect);
            }
        }
        ittr++;
    }
    
    int x = 0, y = 0;
    
    //blank space
    for (int i = 0; i < start.size(); i++) {
        for (int j = 0; j < start[i].size(); j++) {
            if (start[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }
    solvePuzzle(start, x, y, goal, n);
    
    return 0;
}
