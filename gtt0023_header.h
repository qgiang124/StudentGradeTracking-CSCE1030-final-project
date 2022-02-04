//
//  gtt0023_header.h
//  Project 2
//
//  Created by Giang Tran on 11/15/21.
//

#ifndef gtt0023_header_h
#define gtt0023_header_h

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

const int NUM_TEST = 5;
enum      MenuChoice {Add = 1, Remove = 2, Display = 3, Search = 4, Results = 5, Quit = 6};

typedef struct Student_struct {
    string stuName;
    string stuID;
    int    numTestTaken = NULL;
    int*   testScores = new int[numTestTaken];
    double average;
}Student;

int getNumber();
int findMinimum(int array[], int arrSize);
void add_Student();
void display();
void exportResults();
void remove_Student(string studentID);
bool search(string studentID);
void printInfo();
void printMenuChoice();

#endif /* gtt0023_header_h */
