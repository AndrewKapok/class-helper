#include <iostream>
#include "algorithm.h"
using namespace std;

int main()
{
    // Create a simple test student
    Student student;
    student.setName(L"Test");
    student.setScore(90);
    
    vector<Student> students;
    students.push_back(student);
    
    // Test the function
    vector<Student> result = allocateSeats(students, 1, 1, 4);
    
    cout << "Test completed successfully!" << endl;
    return 0;
}
