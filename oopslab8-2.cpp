// diamond problem of inheritence 
#include <iostream>
using namespace std;
class Person {
protected:
    string name;
    int age;
public:
    Person(string name, int age) {
        cout << "Person Constructor Called" << endl;
        this->name = name;
        this->age = age;
    }
};
class Faculty : virtual public Person {
protected:
    string facid;
public:
    Faculty(string n, int a, string facid) : Person(name, age) {
        cout << "Faculty Constructor Called" << endl;
        this->facid = facid;
    }
};
class Student : virtual public Person {
protected:
    string studentid;
public:
    Student(string n, int a, string studentid) : Person(n, a) {
        cout << "Student Constructor Called" << endl;
        this->studentid = studentid;
    }
};
class TA : public Faculty, public Student {
    string taid;
public:
    TA(string n, int a, string f_id, string s_id, string taid)
       : Person(n, a), Faculty(n, a, f_id), Student(n, a, s_id)  {
        cout << "TA Constructor Called" << endl;
        this->taid = taid;   }
    

    void show() {
        cout << "\n--- Attributes ---" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Faculty ID: " << facid<< endl;
        cout << "Student ID: " << studentid << endl;
        cout << "TA ID: " << taid << endl;
    }
};

int main() {
    TA ta1("dheeru", 19, "F101", "12410100550", "BCS-042");
    ta1.show();
    return 0;
}


