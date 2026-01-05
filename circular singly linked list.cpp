#include <iostream>
using namespace std;

struct Track {
    int id;
    string name;
    string artist;
    float duration;
    Track* next;
};

class CircularPlaylist {
private:
    Track* head;

public:
    CircularPlaylist() {
        head = nullptr;
    }
    void insertAtBeginning(int id, string name, string artist, float duration) {
        Track* newNode = new Track{id, name, artist, duration, nullptr};

        if (!head) {
            head = newNode;
            newNode->next = head;
            return;
        }

        Track* temp = head;
        while (temp->next != head)
            temp = temp->next;

        newNode->next = head;
        temp->next = newNode;
        head = newNode;
    }
    void insertAtEnd(int id, string name, string artist, float duration) {
        if (!head) {
            insertAtBeginning(id, name, artist, duration);
            return;
        }

        Track* newNode = new Track{id, name, artist, duration, head};
        Track* temp = head;

        while (temp->next != head)
            temp = temp->next;

        temp->next = newNode;
    }
    void insertAtPosition(int pos, int id, string name, string artist, float duration) {
        if (pos <= 1) {
            insertAtBeginning(id, name, artist, duration);
            return;
        }

        Track* temp = head;
        for (int i = 1; i < pos - 1 && temp->next != head; i++)
            temp = temp->next;

        Track* newNode = new Track{id, name, artist, duration, temp->next};
        temp->next = newNode;
    }
    void deleteFirst() {
        if (!head) return;

        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }

        Track* temp = head;
        while (temp->next != head)
            temp = temp->next;

        Track* del = head;
        head = head->next;
        temp->next = head;
        delete del;
    }
    void deleteLast() {
        if (!head) return;

        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }

        Track* prev = nullptr;
        Track* curr = head;

        while (curr->next != head) {
            prev = curr;
            curr = curr->next;
        }

        prev->next = head;
        delete curr;
    }
    void deleteByID(int id) {
        if (!head) return;

        Track* curr = head;
        Track* prev = nullptr;

        do {
            if (curr->id == id) {
                if (curr == head)
                    deleteFirst();
                else {
                    prev->next = curr->next;
                    delete curr;
                }
                return;
            }
            prev = curr;
            curr = curr->next;
        } while (curr != head);

        cout << "Track ID not found!\n";
    }
    void display() {
        if (!head) {
            cout << "Playlist is empty.\n";
            return;
        }

        Track* temp = head;
        cout << "\n--- Playlist ---\n";
        do {
            cout << "ID: " << temp->id
                 << ", Name: " << temp->name
                 << ", Artist: " << temp->artist
                 << ", Duration: " << temp->duration << " mins\n";
            temp = temp->next;
        } while (temp != head);
    }
};
int main() {
    CircularPlaylist playlist;

    playlist.insertAtEnd(1, "Shape of You", "Ed Sheeran", 4.2);
    playlist.insertAtEnd(2, "Believer", "Imagine Dragons", 3.5);
    playlist.insertAtBeginning(3, "Blinding Lights", "The Weeknd", 3.8);

    playlist.display();

    playlist.deleteByID(2);
    cout << "\nAfter deleting Track ID 2:\n";
    playlist.display();

    return 0;
}