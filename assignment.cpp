#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class UniversitySystemException : public exception {
protected:
    string message;
public:
    UniversitySystemException(const string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class Person {
protected:
    string name;
    int age;
    string id;
    string contact;
public:
    Person(const string& n, int a, const string& i, const string& c) {
        setName(n);
        setAge(a);
        id = i;
        contact = c;
    }

    virtual ~Person() {}

    void setName(const string& n) {
        if (n.empty()) throw invalid_argument("Name cannot be empty.");
        name = n;
    }

    void setAge(int a) {
        if (a <= 0 || a > 120) throw invalid_argument("Invalid age.");
        age = a;
    }

    void setContact(const string& c) {
        contact = c;
    }

    string getName() const { return name; }
    int getAge() const { return age; }
    string getID() const { return id; }
    string getContact() const { return contact; }

    virtual void displayDetails() const {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << id << ", Contact: " << contact << endl;
    }
};

class Student : public Person {
protected:
    string enrollmentDate;
    string program;
    double gpa;
public:
    Student(const string& n, int a, const string& i, const string& c,
            const string& e, const string& p, double g)
        : Person(n, a, i, c), enrollmentDate(e), program(p), gpa(g) {}

    void displayDetails() const override {
        Person::displayDetails();
        cout << "Enrollment Date: " << enrollmentDate << ", Program: " << program << ", GPA: " << gpa << endl;
    }
};

class UndergraduateStudent : public Student {
    string major, minor, expectedGradDate;
public:
    UndergraduateStudent(const string& n, int a, const string& i, const string& c,
                         const string& e, const string& p, double g,
                         const string& m, const string& mi, const string& ex)
        : Student(n, a, i, c, e, p, g), major(m), minor(mi), expectedGradDate(ex) {}

    void displayDetails() const override {
        Student::displayDetails();
        cout << "Major: " << major << ", Minor: " << minor << ", Expected Graduation: " << expectedGradDate << endl;
    }
};

class GraduateStudent : public Student {
    string researchTopic, advisor, thesisTitle;
public:
    GraduateStudent(const string& n, int a, const string& i, const string& c,
                   const string& e, const string& p, double g,
                   const string& r, const string& adv, const string& th)
        : Student(n, a, i, c, e, p, g), researchTopic(r), advisor(adv), thesisTitle(th) {}

    void displayDetails() const override {
        Student::displayDetails();
        cout << "Research Topic: " << researchTopic << ", Advisor: " << advisor << ", Thesis Title: " << thesisTitle << endl;
    }
};

class Professor : public Person {
protected:
    string department;
    string specialization;
    string hireDate;
public:
    Professor(const string& n, int a, const string& i, const string& c,
              const string& d, const string& s, const string& h)
        : Person(n, a, i, c), department(d), specialization(s), hireDate(h) {}

    void displayDetails() const override {
        Person::displayDetails();
        cout << "Department: " << department << ", Specialization: " << specialization << ", Hire Date: " << hireDate << endl;
    }
};

class AssistantProfessor : public Professor {
public:
    AssistantProfessor(const string& n, int a, const string& i, const string& c,
                       const string& d, const string& s, const string& h)
        : Professor(n, a, i, c, d, s, h) {}

    void displayDetails() const override {
        Professor::displayDetails();
        cout << "Rank: Assistant Professor\n";
    }
};

class AssociateProfessor : public Professor {
public:
    AssociateProfessor(const string& n, int a, const string& i, const string& c,
                       const string& d, const string& s, const string& h)
        : Professor(n, a, i, c, d, s, h) {}

    void displayDetails() const override {
        Professor::displayDetails();
        cout << "Rank: Associate Professor\n";
    }
};

class FullProfessor : public Professor {
public:
    FullProfessor(const string& n, int a, const string& i, const string& c,
                  const string& d, const string& s, const string& h)
        : Professor(n, a, i, c, d, s, h) {}

    void displayDetails() const override {
        Professor::displayDetails();
        cout << "Rank: Full Professor\n";
    }
};

class University {
    vector<Student*> students;
    vector<Professor*> professors;
public:
    ~University() {
        for (auto s : students) delete s;
        for (auto p : professors) delete p;
    }

    void addStudent(Student* s) {
        students.push_back(s);
    }

    void addProfessor(Professor* p) {
        professors.push_back(p);
    }

    void displayStudents() const {
        if (students.empty()) {
            cout << "No students available.\n";
            return;
        }
        for (const auto& s : students) {
            s->displayDetails();
            cout << "--------------------------\n";
        }
    }

    void displayProfessors() const {
        if (professors.empty()) {
            cout << "No professors available.\n";
            return;
        }
        for (const auto& p : professors) {
            p->displayDetails();
            cout << "--------------------------\n";
        }
    }
};

int main() {
    University uni;
    int choice;

    try {
        while (true) {
            cout << "\nUniversity Management System\n";
            cout << "1. Add Undergraduate Student\n";
            cout << "2. Add Graduate Student\n";
            cout << "3. Add Assistant Professor\n";
            cout << "4. Add Associate Professor\n";
            cout << "5. Add Full Professor\n";
            cout << "6. Display Students\n";
            cout << "7. Display Professors\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 0) break;

            if (choice == 1 || choice == 2) {
                string name, id, contact, enrollmentDate, program;
                int age;
                double gpa;

                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter ID: ";
                getline(cin, id);
                cout << "Enter Contact: ";
                getline(cin, contact);
                cout << "Enter Enrollment Date: ";
                getline(cin, enrollmentDate);
                cout << "Enter Program: ";
                getline(cin, program);
                cout << "Enter GPA: ";
                cin >> gpa;
                cin.ignore();

                if (choice == 1) {
                    string major, minor, gradDate;
                    cout << "Enter Major: ";
                    getline(cin, major);
                    cout << "Enter Minor: ";
                    getline(cin, minor);
                    cout << "Enter Expected Graduation Date: ";
                    getline(cin, gradDate);
                    Student* s = new UndergraduateStudent(name, age, id, contact, enrollmentDate, program, gpa, major, minor, gradDate);
                    uni.addStudent(s);
                } else {
                    string researchTopic, advisor, thesisTitle;
                    cout << "Enter Research Topic: ";
                    getline(cin, researchTopic);
                    cout << "Enter Advisor: ";
                    getline(cin, advisor);
                    cout << "Enter Thesis Title: ";
                    getline(cin, thesisTitle);
                    Student* s = new GraduateStudent(name, age, id, contact, enrollmentDate, program, gpa, researchTopic, advisor, thesisTitle);
                    uni.addStudent(s);
                }
                cout << "Student added successfully.\n";
            }
            else if (choice >= 3 && choice <= 5) {
                string name, id, contact, department, specialization, hireDate;
                int age;

                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter ID: ";
                getline(cin, id);
                cout << "Enter Contact: ";
                getline(cin, contact);
                cout << "Enter Department: ";
                getline(cin, department);
                cout << "Enter Specialization: ";
                getline(cin, specialization);
                cout << "Enter Hire Date: ";
                getline(cin, hireDate);

                Professor* p = nullptr;
                if (choice == 3)
                    p = new AssistantProfessor(name, age, id, contact, department, specialization, hireDate);
                else if (choice == 4)
                    p = new AssociateProfessor(name, age, id, contact, department, specialization, hireDate);
                else
                    p = new FullProfessor(name, age, id, contact, department, specialization, hireDate);

                uni.addProfessor(p);
                cout << "Professor added successfully.\n";
            }
            else if (choice == 6) {
                uni.displayStudents();
            }
            else if (choice == 7) {
                uni.displayProfessors();
            }
            else {
                cout << "Invalid choice. Try again.\n";
            }
        }
    } catch (const exception& ex) {
        cout << "Error: " << ex.what() << endl;
    }

    return 0;
}
