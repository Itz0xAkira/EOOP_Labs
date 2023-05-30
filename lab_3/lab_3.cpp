#include <iostream>
#include <cstring>

using namespace std;

class Group {
private:
    char* group_name;
    struct student {
        char* name;
        double cgpa;
    };
    struct Node {
        student* data;
        Node* next;
    };
    Node* head = nullptr;

public:
    Group(const char* name) {
        // Allocate memory for a new char array
        group_name = new char[strlen(name) + 1];
        strcpy(group_name, name);
    }

    ~Group() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp->data->name;
            delete temp->data;
            delete temp;
        }
        delete[] group_name;
    }

    bool search(const char *name,Node* &where){
    Node* curr = head;
    while (curr != nullptr) {
        if(curr->data->name == name){
            where = curr;
            return true;
        }
        curr = curr->next;
    }
    where = nullptr;
    return false;
    }

    bool insert(const char* name, const double cgpa) {
        // Allocate memory for a new char array
        char* newName = new char[strlen(name) + 1];
        Node *where;
        strcpy(newName, name);
        if (search(newName,where)) {
            cout << "Student Already exist" << endl;
            delete newName;
            return false;
        }
        student* newStudent = new student();
        newStudent->name = newName;
        newStudent->cgpa = cgpa;

        Node* newNode = new Node();
        newNode->data = newStudent;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            return true;
        } else {
            Node* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = newNode;
            return true;
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

    bool search_cgpa(const double cgpa) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data->cgpa == cgpa) {
                cout << "found it at" << " " << curr << endl;
                return true;
            }
            curr = curr->next;
        }
        cout << "did not find it " << endl;
        return false;
    }

    bool Remove(const char *name) {
        if (head == nullptr) {
            cout << "the linked list is empty" << endl;
            return false;
        }

        if (strcmp(head->data->name, name) == 0) {
            Node* temp = head;
            head = temp->next;
            delete temp->data->name;
            delete temp->data;
            delete temp;
            return true;
        }

        Node* curr = head;
        while (curr->next != nullptr) {
            if (strcmp(curr->next->data->name, name) == 0) {
                Node* temp = curr->next;
                curr->next = temp->next;
                delete temp->data->name;
                delete temp->data;
                delete temp;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
};


int main() {
    Group group("Group1");
    group.insert("Akira", 5.6);
    group.insert("Saad", 5.5);
    group.insert("Ahmed", 2.5);
    group.print();
    group.Remove("Ahmed");
    group.print();
    group.search_cgpa(5.5);

    return 0;
}