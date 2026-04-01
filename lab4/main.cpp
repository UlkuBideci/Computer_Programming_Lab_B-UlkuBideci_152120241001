#include <iostream>
#include <string>

using namespace std;

struct Bundle {
    string serial;
    string currency;
    int bills[3];
    Bundle* next;
};

struct Stack {
    Bundle* top;
};

struct Customer {
    string name;
    string type;
};

struct Queue {
    Customer arr[5];
    int front;
    int rear;
    int count;
};

void initStack(Stack &s) {
    s.top = nullptr;
}

bool isStackEmpty(Stack &s) {
    return s.top == nullptr;
}

void push(Stack &s, string serial, string currency, int c100, int c50, int c20) {
    Bundle* b = new Bundle();
    b->serial = serial;
    b->currency = currency;
    b->bills[0] = c100;
    b->bills[1] = c50;
    b->bills[2] = c20;
    b->next = s.top;
    s.top = b;
    cout << "para safe'e eklendi: " << serial << endl;
}

Bundle* pop(Stack &s) {
    if (isStackEmpty(s)) return nullptr;
    Bundle* temp = s.top;
    s.top = s.top->next;
    return temp;
}

void displayStack(Stack &s) {
    if (isStackEmpty(s)) {
        cout << "Safe empty." << endl;
        return;
    }
    Bundle* curr = s.top;
    while (curr != nullptr) {
        cout << curr->serial << " (" << curr->currency << ")" << endl;
        curr = curr->next;
    }
}

void initQueue(Queue &q) {
    q.front = 0;
    q.rear = -1;
    q.count = 0;
}

bool isQueueEmpty(Queue &q) {
    return q.count == 0;
}

bool isQueueFull(Queue &q) {
    return q.count == 5;
}

void enqueue(Queue &q, string name, string type) {
    if (isQueueFull(q)) return;
    q.rear = (q.rear + 1) % 5;
    q.arr[q.rear].name = name;
    q.arr[q.rear].type = type;
    q.count++;
    cout << "customer: " << name << endl;
}


bool dequeue(Queue &q, Customer &cust) {
    if (isQueueEmpty(q)) return false;
    cust = q.arr[q.front];
    q.front = (q.front + 1) % 5;
    q.count--;
    return true;
}

void displayQueue(Queue &q) {
    if (isQueueEmpty(q)) {
        cout << "empty"<< endl;
        return;
    }
    for (int i=0; i < q.count; i++) {
        int idx = (q.front + i) % 5;
        cout << i + 1 << ". " << q.arr[idx].name << endl;
    }
}



void processTransaction(Stack &s, Queue &q) {
    if (isQueueEmpty(q) || isStackEmpty(s)) return;
    Customer c;
    dequeue(q, c);
    Bundle* b = pop(s);
    cout << "\n>>> Served: " << c.name << " with bundle: " << b->serial << endl;
    delete b; 
}

int main() {
    Stack s;
    Queue q;
    initStack(s);
    initQueue(q);

    push(s, "serialn1", "TL", 10, 5, 2);
    push(s, "serialn2", "USD", 5, 0, 0);

    enqueue(q, "Ulku", "Withdraw");
    enqueue(q, "Tuana", "Deposit");

    cout << "\n safe durumu" << endl;
    displayStack(s);
    cout << "\n line durumu" << endl;
    displayQueue(q);

    processTransaction(s, q);

    while (!isStackEmpty(s)) {
        Bundle* temp = pop(s);
        delete temp;
    }

    return 0;
}