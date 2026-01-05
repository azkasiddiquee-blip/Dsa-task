#include <iostream>
#include <string>
using namespace std;

#define MAX 5  

class TicketQueue {
private:
    int front, rear;
    string tickets[MAX];

public:
    TicketQueue() {
        front = -1;
        rear = -1;
    }
    bool isEmpty() {
        return (front == -1);
    }
    bool isFull() {
        return (rear == MAX - 1);
    }
    void enqueue(string ticket) {
        if (isFull()) {
            cout << "Queue is full. Cannot add more tickets.\n";
            return;
        }
        if (isEmpty()) {
            front = 0;
        }
        rear++;
        tickets[rear] = ticket;
        cout << "Ticket added: " << ticket << endl;
    }
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. No ticket to process.\n";
            return;
        }
        cout << "Processing ticket: " << tickets[front] << endl;

        if (front == rear) {
            front = rear = -1; 
        } else {
            front++;
        }
    }
    void display() {
        if (isEmpty()) {
            cout << "No pending tickets.\n";
            return;
        }
        cout << "Pending Tickets:\n";
        for (int i = front; i <= rear; i++) {
            cout << "- " << tickets[i] << endl;
        }
    }
    void cancelTicket(string ticket) {
        if (isEmpty()) {
            cout << "Queue is empty. No ticket to cancel.\n";
            return;
        }

        int pos = -1;
        for (int i = front; i <= rear; i++) {
            if (tickets[i] == ticket) {
                pos = i;
                break;
            }
        }

        if (pos == -1) {
            cout << "Ticket not found.\n";
            return;
        }

        for (int i = pos; i < rear; i++) {
            tickets[i] = tickets[i + 1];
        }
        rear--;

        if (rear < front) {
            front = rear = -1;
        }

        cout << "Ticket cancelled: " << ticket << endl;
    }
};

int main() {
    TicketQueue tq;

    tq.enqueue("Internet Issue");
    tq.enqueue("Login Problem");
    tq.enqueue("Payment Failure");

    tq.display();

    tq.dequeue();

    tq.display();

    tq.cancelTicket("Login Problem");

    tq.display();

    tq.dequeue();
    tq.dequeue();
    tq.dequeue();  

    return 0;
}