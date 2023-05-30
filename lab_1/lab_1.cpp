#include <iostream>
#include <cstring>

using namespace std;

struct student {
    char* name;
    double cgpa;
};

struct Node {
    student* data;
    Node* next;
};

Node* head = nullptr;

void insert(const char* name, const double cgpa) {
    // Allocate memory for a new char array
    char* newName = new char[strlen(name) + 1];

    strcpy(newName, name);

    student* newStudent = new student();
    newStudent->name = newName;
    newStudent->cgpa = cgpa;


    Node* newNode = new Node();
    newNode->data = newStudent;
    newNode->next = nullptr;


    if (head == nullptr) {
        head = newNode;
    } else {
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

void print() {
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data->name << " ";
        cout << curr->data->cgpa << endl;
        curr = curr->next;
    }
    std::cout << std::endl;
}

bool search_cgpa(const double cgpa){
    Node* curr = head;
    while (curr != nullptr) {
        if(curr->data->cgpa == cgpa){
            cout << "found it at" << " " << curr << endl;
            return true;
        }
        curr = curr->next;
    }
    cout << "did not find it " << endl;
    return false;
}

int main(){
    insert("Akira",5.6);
    insert("Saad", 5.5);
    print();
    search_cgpa(5.5);

    return 0;
}