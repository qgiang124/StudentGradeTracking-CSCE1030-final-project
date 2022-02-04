/* Author:  Giang Tran (giangtran2@my.unt.edu)
 * Date: 11/21/2021
 * Instructor: Dr. Asif Baba
 * Description: The program keeps track of grades of students using structures and files.
 */

#include "gtt0023_header.h"

/* Function:    add_Student
 * Parameter:   none
 * Return:      void
 * Description: adds a new student to the record with their name,                     studentID, number of tests taken and scores.
 */
void add_Student() {
    Student student;
    string  lastName;
    string  firstName;
    ofstream out_s;         //output stream

    //Prompt user for the information of the student add to to the record
    cout << "Enter last name of the student: ";
    cin  >> lastName;
    cout << "Enter first name of the student: ";
    cin  >> firstName;
    cout << "Enter student ID: ";
    cin  >> student.stuID;
    cout << "How many tests did this student take? ";
    cin  >> student.numTestTaken;

    for (int i = 0; i < student.numTestTaken; i++) {
        cout << "Enter score #" << i + 1 << ": ";
        cin  >> *(student.testScores + i);
    }

    //open output file student.dat keeping the orginal content
    out_s.open("student.dat", std::ios::app);
    if (out_s.fail()) {
        cout << "Unable to open the file student.dat."<< endl;
        exit(EXIT_FAILURE);
    }

    //put ouput to the student.dat file keeping the original format
    student.stuName = lastName + "," + firstName;
    out_s << student.stuName << "," << student.stuID << "," << student.numTestTaken << ",";
    for (int i = 0; i < student.numTestTaken; i++) {
        out_s << *(student.testScores + i) << ",";
    }

    out_s.close();      //close output stream

}

/* Function:    display
 * Parameter:   none
 * Return:      void
 * Description: displays all the students in the record
 */
void display() {
    ifstream in_s;      //input stream
    int      numStu = getNumber(); //number of students in student.dat file
    string   lastname;
    string   firstname;
    Student* studentList = new Student[numStu]; //dynamic array type of Student

    //open the input file and check if it works
    in_s.open("student.dat");
    if (in_s.fail()) {
        cout << "Unable to open input file student.dat."<< endl;
        exit(EXIT_FAILURE);
    }

    //from the input file, read the contents and copies it to the dynamic array type Student
    for (int i = 0; i < numStu; i++) {
        getline(in_s, lastname, ',');
        getline(in_s, firstname, ',');

        (*(studentList + i)).stuName = lastname + "," + firstname;

        getline(in_s, (*(studentList + i)).stuID, ',');

        in_s >> (*(studentList + i)).numTestTaken;
        in_s.ignore(256, ',');

        for (int j = 0; j < (*(studentList + i)).numTestTaken; j++) {
            in_s >> *((*(studentList + i)).testScores + j);
            in_s.ignore(256, ',');
        }
        
            in_s.ignore(256, '\n');
        
    }

    //displays the formated content to the screen
    for (int i = 0; i < numStu; i++) {
        cout << setw(30) << (*(studentList + i)).stuName;
        cout << setw(15) << (*(studentList + i)).stuID;
        for (int j = 0; j < (*(studentList + i)).numTestTaken; j++) {
            cout << setw(5) << *((*(studentList + i)).testScores + j);
        }
        cout << endl;

    }
    
    in_s.close();   //close input stream
    delete [] studentList;  //delete the dynamic array
}

/* Function:    add_Student
 * Parameter:   none
 * Return:      void
 * Description: computes the average of each student and export the                   results to the output file named averages.dat
 */
void exportResults() {
    ifstream in_s;      //input stream
    ofstream out_s;     //output stream
    int      numStu = getNumber();      //number of students read from input file
    int      sumTestScores = 0;     //sum of test scores of each student
    double   average;               //average score of each student
    string   lastname;
    string   firstname;
    Student *studentList = new Student[numStu]; //dynamic array contains the list of student and their information
    
    in_s.open("student.dat");           //open file student.dat for reading
    if (out_s.fail()) {
        cout << "Unable to open the file student.dat."<< endl;
        exit(EXIT_FAILURE);
    }
    
    //reads the content from input file and stores information with proper variables
    for (int i = 0; i < numStu; i++) {
        getline(in_s, lastname, ',');
        getline(in_s, firstname, ',');

        (*(studentList + i)).stuName = lastname + "," + firstname;

        getline(in_s, (*(studentList + i)).stuID, ',');

        in_s >> (*(studentList + i)).numTestTaken;
        in_s.ignore(256, ',');

        for (int j = 0; j < (*(studentList + i)).numTestTaken; j++) {
            in_s >> *((*(studentList + i)).testScores + j);
            in_s.ignore(256, ',');
        }
        in_s.ignore(256, '\n');
    }
    
    //open output file and check if it's working
    out_s.open("averages.dat");
    if (out_s.fail()) {
        cout << "Unable to open the file averages.dat."<< endl;
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < numStu; i++) {
        sumTestScores = 0; //initialize every loop
    
        for (int j = 0; j < (*(studentList + i)).numTestTaken; j++) {
            //sum of test scores of each student
            sumTestScores += *((*(studentList + i)).testScores + j);
        }
        
        //drop the lowest score
        sumTestScores -= findMinimum((*(studentList + i)).testScores,
                                     (*(studentList + i)).numTestTaken);
        
        average = ((double) sumTestScores) / 4;
        
        out_s << (*(studentList + i)).stuID  << " " << average << endl;
    }
    
    in_s.close();   //close input stream
    out_s.close();  //close output stream
    delete[] studentList; //delete the dynamic array
    cout << "See the averages.dat file. \n";
}

/* Function:    findMinimum
 * Parameter:   an array type int
                an integer value indicating the size of the array
 * Return:      minVal
 * Description: computes the minimum out of the test scores and returns the score.
 */
int findMinimum(int array[], int arrSize) {
    int minVal = 0;
    if (arrSize == NUM_TEST){
        minVal = array[0];
        for (int i = 1; i < arrSize; i++) {
            if (array[i] < minVal) {
                minVal = array[i];
            }
        }
    }
    return minVal;
}

/* Function:    search
 * Parameter:   a string indicating the student ID
 * Return:      boolean value
 * Description: looks for the information of the student by their student ID and returns if the student is found
 */
bool search(string studentID) {
    bool     studentFound = false;
    ifstream in_s;      //input stream
    string   lastname;
    string   firstname;
    int      numStu = getNumber();      //number of students
    Student  my_student;                //variable type Student
    Student* studentptr = nullptr;      //pointer poingting to my_student
    studentptr = &my_student;
    
    //open input file and check if it's working
    in_s.open("student.dat");
    if (in_s.fail()) {
        cout << "Unable to open the file student.dat."<< endl;
        exit(EXIT_FAILURE);
    }
    
    //reads the input file and store information to proper variables
    for (int i = 0; i < numStu; i++) {
        getline(in_s, lastname, ',');
        getline(in_s, firstname, ',');

        (*studentptr).stuName = lastname + "," + firstname;

        getline(in_s, (*studentptr).stuID, ',');

        in_s >> (*studentptr).numTestTaken;
        in_s.ignore(256, ',');

        for (int j = 0; j < (*studentptr).numTestTaken; j++) {
            in_s >> *((*studentptr).testScores + j);
            in_s.ignore(256, ',');
        }
        in_s.ignore(256, '\n');

    }

    //check if the typed-in studentID matches the studentID on the record and put output to the screen
    if (((*studentptr).stuID).compare(studentID) == 0) {
        studentFound = true;
        cout << setw(30) << (*studentptr).stuName;
        cout << setw(15) << (*studentptr).stuID;
        for (int j = 0; j < (*studentptr).numTestTaken; j++) {
            cout << setw(5) << *((*studentptr).testScores + j);
        }
        cout << endl;
    }
    else {
        studentFound = false;
        cout << "ID Student does not exist." << endl;
    }
    
    in_s.close();   //close input stream

    return studentFound;
}

/* Function:    remove_Student
 * Parameter:   a string variable indicating the studentID
 * Return:      void
 * Description: removes a student from the record by their student ID
 */
void remove_Student(string studentID) {
    bool     stuFound = false;
    int      numStu = getNumber();  //number of students
    int      removeStu = NULL;      //holds the index at which the student needed to remove found.
    string   lastname;
    string   firstname;
    ifstream in_s;                  //input stream
    ofstream out_s;                 //output stream
    Student* studentList = new Student[numStu];     //dynamic array contains the information of students on record

    //open input file and check if it's working
    in_s.open("student.dat");
    if (in_s.fail()) {
        cout << "Unable to open input file student.dat."<< endl;
        exit(EXIT_FAILURE);
    }

    //reads input from the student.dat file
    for (int i = 0; i < numStu; i++) {
        getline(in_s, lastname, ',');
        getline(in_s, firstname, ',');
        (*(studentList + i)).stuName = lastname + "," + firstname;

        getline(in_s, (*(studentList + i)).stuID, ',');

        if (studentID.compare((*(studentList + i)).stuID) == 0) {
            stuFound = true;
            removeStu = i;
        }

        in_s >> (*(studentList + i)).numTestTaken;
        in_s.ignore(256, ',');

        for (int j = 0; j < (*(studentList + i)).numTestTaken; j++) {
            in_s >> *((*(studentList + i)).testScores + j);
            in_s.ignore(256, ',');
        }
        in_s.ignore(256, '\n');

    }

    in_s.close(); //close input stream

    //check if the studentID found
    if (stuFound == true) {
        //opent output file and check if it's working
        out_s.open("student.dat");
        if (out_s.fail()) {
            cout << "Unable to open output file student.dat."<< endl;
            exit(EXIT_FAILURE);
        }
        
        //loop running through dynamic array
        for (int i = 0; i < numStu; i++) {
            //skip and not output that student's information of the student
            if (i == removeStu) {
                continue;
            }
            //output other students information back to the file
            else{
                out_s << (*(studentList + i)).stuName << "," << (*(studentList + i)).stuID << ","
                      << (*(studentList + i)).numTestTaken << ",";
                for (int j = 0; j < (*(studentList + i)).numTestTaken; j++) {
                    out_s << *((*(studentList + i)).testScores + j) << ",";
                }
                out_s << endl;
            }
        }
        cout << "Successfully removed!" << endl;
    }
    else {
        cout << "Student ID not found." << endl;
    }

    out_s.close(); //close output tream
    delete [] studentList;
}


void printInfo () {
    cout << "Computer Science and Engineering" << endl;
    cout << "CSCE 1030 - Computer Science I" << endl;
    cout << "Giang Thi Quynh Tran - EUID gtt0023" << endl;
    cout << "-------------------------------------" << endl;
}

void printMenuChoice() {
    cout << "\n Menu choices: \n";
    string choices[] = {"Add", "Remove", "Display", "Search", "Results", "Quit"};

    for (int i = 0; i < 6; i++) {
        cout << i + 1 << ". " << choices[i] << endl;
    }
}

