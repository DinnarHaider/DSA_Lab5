#include <iostream>
#include <string>
#include <limits>
using namespace std;

class CoachNode
{
public:
    int number, capacity, passengers;
    string type;
    CoachNode *next, *prev;

    CoachNode(int num, string t, int cap, int people)
    {
        number = num;
        type = t;
        capacity = cap;
        passengers = people;
        next = prev = NULL;
    }
};

class Train
{
public:
    CoachNode *head, *tail, *current;

    Train() { head = tail = current = NULL; }
    Train(const Train&) = delete;
    Train& operator=(const Train&) = delete;

    ~Train()
    {
        while (head != NULL) erase(head);
    }

    CoachNode* findCoach(int number)
    {
        if (head == NULL) return NULL;
        CoachNode* temp = head;
        do
        {
            if (temp->number == number) return temp;
            temp = temp->next;
        } while (temp != head);
        return NULL;
    }

    void showCoach(CoachNode* coach)
    {
        if (coach == NULL)
        {
            cout << "No coach selected.\n";
            return;
        }
        cout << "Coach: " << coach->number
             << " | Type: " << coach->type << '\n';
        cout << "Capacity: " << coach->capacity
             << " | Passengers: " << coach->passengers
             << " | Empty seats: "
             << coach->capacity - coach->passengers << '\n';
    }

    bool validCoach(int num, int cap, int people)
    {
        if (findCoach(num) != NULL)
        {
            cout << "Coach number already exists.\n";
            return false;
        }
        if (cap < 0 || people < 0 || people > cap)
        {
            cout << "Invalid capacity or passenger count.\n";
            return false;
        }
        return true;
    }

    void linkAfter(CoachNode* position, CoachNode* node)
    {
        if (head == NULL)
        {
            head = tail = current = node;
            node->next = node->prev = node;
            return;
        }
        node->prev = position;
        node->next = position->next;
        position->next->prev = node;
        position->next = node;
        if (position == tail) tail = node;
    }

    void addCoach(int num, string t, int cap, int people)
    {
        if (!validCoach(num, cap, people)) return;
        linkAfter(tail, new CoachNode(num, t, cap, people));
        cout << "Coach added: " << num << '\n';
    }

    void insertCoach(int after, int num, string t,
                     int cap, int people)
    {
        CoachNode* position = findCoach(after);
        if (position == NULL)
        {
            cout << "Specified coach not found.\n";
            return;
        }
        if (!validCoach(num, cap, people)) return;
        linkAfter(position, new CoachNode(num, t, cap, people));
        cout << "Coach inserted: " << num
             << " after " << after << '\n';
    }

    void erase(CoachNode* coach)
    {
        if (coach->next == coach)
        {
            head = tail = current = NULL;
        }
        else
        {
            coach->prev->next = coach->next;
            coach->next->prev = coach->prev;
            if (coach == head) head = coach->next;
            if (coach == tail) tail = coach->prev;
            if (coach == current) current = coach->next;
        }
        delete coach;
    }

    void removeCoach(int num)
    {
        CoachNode* coach = findCoach(num);
        if (coach == NULL)
        {
            cout << "Coach not found.\n";
            return;
        }
        erase(coach);
        cout << "Coach removed: " << num << '\n';
    }

    void moveForward()
    {
        if (current == NULL) cout << "Train is empty.\n";
        else { current = current->next; showCoach(current); }
    }

    void moveBackward()
    {
        if (current == NULL) cout << "Train is empty.\n";
        else { current = current->prev; showCoach(current); }
    }

    void displayClockwise()
    {
        if (current == NULL)
        {
            cout << "Train is empty.\n";
            return;
        }
        CoachNode* temp = current;
        do
        {
            showCoach(temp);
            temp = temp->next;
        } while (temp != current);
    }

    void displayAnticlockwise()
    {
        if (current == NULL)
        {
            cout << "Train is empty.\n";
            return;
        }
        CoachNode* temp = current;
        do
        {
            showCoach(temp);
            temp = temp->prev;
        } while (temp != current);
    }

    void searchCoach(int num)
    {
        CoachNode* coach = findCoach(num);
        if (coach == NULL) cout << "Coach not found.\n";
        else showCoach(coach);
    }

    void maximumAvailable()
    {
        if (head == NULL)
        {
            cout << "Train is empty.\n";
            return;
        }
        CoachNode* best = head;
        CoachNode* temp = head->next;
        while (temp != head)
        {
            if (temp->capacity - temp->passengers >
                best->capacity - best->passengers)
                best = temp;
            temp = temp->next;
        }
        cout << "Coach with maximum available capacity:\n";
        showCoach(best);
    }

    void displayCurrent() { showCoach(current); }

    void reverseDirection()
    {
        if (head == NULL)
        {
            cout << "Train is empty.\n";
            return;
        }
        CoachNode* temp = head;
        do
        {
            CoachNode* oldNext = temp->next;
            temp->next = temp->prev;
            temp->prev = oldNext;
            temp = oldNext;
        } while (temp != head);
        CoachNode* oldHead = head;
        head = tail;
        tail = oldHead;
        cout << "Train direction reversed.\n";
    }
};

bool readCoach(int& num, string& type, int& cap, int& people)
{
    cout << "Coach number: ";
    if (!(cin >> num)) return false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Coach type: ";
    if (!getline(cin, type)) return false;
    cout << "Capacity and current passengers: ";
    return static_cast<bool>(cin >> cap >> people);
}

int main()
{
    Train train;
    int count, num, capacity, people, after, choice;
    string type;
    cout << "Number of coaches: ";
    if (!(cin >> count) || count < 0) return 1;
    for (int i = 0; i < count; i++)
    {
        if (!readCoach(num, type, capacity, people)) return 1;
        train.addCoach(num, type, capacity, people);
    }
    cout << "\n1 Add Coach | 2 Insert After Coach\n"
         << "3 Remove Coach | 4 Move Forward | 5 Move Backward\n"
         << "6 Display Clockwise | 7 Display Anti-clockwise\n"
         << "8 Search Coach | 9 Maximum Available Capacity\n"
         << "10 Display Current | 11 Reverse Direction | 0 Exit\n";
    while (true)
    {
        cout << "\nChoice: ";
        if (!(cin >> choice)) return 0;
        if (choice == 0) break;
        else if (choice == 1 || choice == 2)
        {
            if (choice == 2)
            {
                cout << "Insert after coach number: ";
                if (!(cin >> after)) return 1;
            }
            if (!readCoach(num, type, capacity, people)) return 1;
            if (choice == 1)
                train.addCoach(num, type, capacity, people);
            else
                train.insertCoach(after, num, type, capacity, people);
        }
        else if (choice == 3 || choice == 8)
        {
            cout << "Coach number: ";
            if (!(cin >> num)) return 1;
            if (choice == 3) train.removeCoach(num);
            else train.searchCoach(num);
        }
        else if (choice == 4) train.moveForward();
        else if (choice == 5) train.moveBackward();
        else if (choice == 6) train.displayClockwise();
        else if (choice == 7) train.displayAnticlockwise();
        else if (choice == 9) train.maximumAvailable();
        else if (choice == 10) train.displayCurrent();
        else if (choice == 11) train.reverseDirection();
        else cout << "Invalid choice.\n";
    }
    return 0;
}
