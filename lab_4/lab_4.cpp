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
        delete group_name;
    }

    bool search(const char *name, Node* &where) {
        Node* curr = head;
        while (curr != nullptr) {
            if (strcmp(curr->data->name, name) == 0) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    bool insert(const char* name, const double cgpa) {
        // Allocate memory for a new char array
        char* newName = new char[strlen(name) + 1];
        Node* where;
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

    bool Remove(const char name[]) {
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

    bool operator==(Group& other) const {
        // Check if both linked lists have the same students in the same order
        Node* curr1 = head;
        Node* curr2 = other.head;
        while (curr1 != nullptr && curr2 != nullptr) {
            if (strcmp(curr1->data->name, curr2->data->name) != 0 || curr1->data->cgpa != curr2->data->cgpa) {
                return false;
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        // Check if both linked lists have the same length
        if (curr1 != curr2) {
            return false;
        }
        // If all checks pass, the two objects are equal
        // Delete the second object to avoid memory leaks
        delete &other;
        cout << "Group B Inside:" << &other << endl;
        return true;
        }
};


int main() {
    Group* groupA = new Group("GroupA");
    groupA->insert("Akira", 5.6);
    groupA->insert("Saad", 5.5);
    groupA->insert("Ahmed", 2.5);
    // groupA.Remove("Ahmed");
    groupA->print();
    groupA->search_cgpa(5.5);
    // Group B
    Group* groupB = new Group("GroupB");
    groupB->insert("Akira", 5.6);
    groupB->insert("Saad", 5.5);
    groupB->insert("Ahmed", 2.5);
    groupB->print();
    //groupB.Remove("Ahmed");
    groupB->search_cgpa(5.5);
    
    cout << "GroupB Address:" << groupB << endl;
    cout << (*groupA == *groupB) << endl;
    
    return 0;
}