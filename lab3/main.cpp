#include <iostream>
#include <string>

using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3];
    Page *next;
    Page *prev;
};

Page* head = nullptr;
Page* current = nullptr;

void Visit(string u, string t, int h, int m, int s) {
    Page* newNode = new Page;
    newNode->url = u;
    newNode->title = t;
    newNode->accessTime[0] = h;
    newNode->accessTime[1] = m;
    newNode->accessTime[2] = s;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (head == nullptr) {
        head = newNode;
        current = newNode;
    } else {
        Page* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
        current = newNode; 
    }
}

void Back() {
    if (current != nullptr && current->prev != nullptr) {
        current = current->prev;
    }
}

void Forward() {
    if (current != nullptr && current->next != nullptr) {
        current = current->next;
    }
}

void DeleteEntry() {
    if (current == nullptr) return;
    Page* toDelete = current;
    if (toDelete->prev != nullptr) {
        toDelete->prev->next = toDelete->next;
    } else {
        head = toDelete->next;
    }
    if (toDelete->next != nullptr) {
        toDelete->next->prev = toDelete->prev;
        current = toDelete->next;
    } else {
        current = toDelete->prev;
    }
    delete toDelete;
}

void DisplayHistory() {
    Page* temp = head;
    while (temp != nullptr) {
        if (temp == current) cout << "-> [CURRENT] ";
        else cout << "   ";
        cout << temp->title << " (" << temp->url << ") | Zaman: ";
        for (int i = 0; i < 3; i++) {
            if (temp->accessTime[i] < 10) cout << "0";
            cout << temp->accessTime[i] << (i < 2 ? ":" : "");
        }
        cout << endl;
        temp = temp->next;
    }
}

int main() {
    string command;
    while (true) {
        cin >> command;
        if (command == "VISIT") {
            string u, t; int h, m, s;
            cin >> u >> t >> h >> m >> s;
            Visit(u, t, h, m, s);
        } else if (command == "BACK") Back();
        else if (command == "FORWARD") Forward();
        else if (command == "DELETE") DeleteEntry();
        else if (command == "SHOW") DisplayHistory();
        else if (command == "EXIT") {
            Page* temp = head;
            while (temp != nullptr) {
                Page* nextNode = temp->next;
                delete temp;
                temp = nextNode;
            }
            break;
        }
    }
    return 0;
}
