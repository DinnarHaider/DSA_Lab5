#include <iostream>
#include <string>
using namespace std;

class PhotoNode
{
public:
    int ID;
    string name, date, location;
    PhotoNode *next, *prev;

    PhotoNode(int id, string n, string d, string l)
    {
        ID = id;
        name = n;
        date = d;
        location = l;
        next = prev = NULL;
    }
};

class PhotoAlbum
{
public:
    PhotoNode *head, *tail, *current;

    PhotoAlbum() { head = tail = current = NULL; }
    PhotoAlbum(const PhotoAlbum&) = delete;
    PhotoAlbum& operator=(const PhotoAlbum&) = delete;

    ~PhotoAlbum()
    {
        while (head != NULL) erase(head);
    }

    PhotoNode* findPhoto(int id)
    {
        if (head == NULL) return NULL;
        PhotoNode* temp = head;
        do
        {
            if (temp->ID == id) return temp;
            temp = temp->next;
        } while (temp != head);
        return NULL;
    }

    void showPhoto(PhotoNode* photo)
    {
        if (photo == NULL)
        {
            cout << "No photo selected.\n";
            return;
        }
        cout << "ID: " << photo->ID
             << " | Name: " << photo->name << '\n';
        cout << "Date: " << photo->date
             << " | Location: " << photo->location << '\n';
    }

    void linkAfter(PhotoNode* position, PhotoNode* node)
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

    void addPhoto(int id, string n, string d, string l)
    {
        if (findPhoto(id) != NULL)
        {
            cout << "Photo ID already exists.\n";
            return;
        }
        linkAfter(tail, new PhotoNode(id, n, d, l));
        cout << "Photo added: " << id << '\n';
    }

    void insertAfterCurrent(int id, string n,
                            string d, string l)
    {
        if (findPhoto(id) != NULL)
        {
            cout << "Photo ID already exists.\n";
            return;
        }
        linkAfter(current, new PhotoNode(id, n, d, l));
        cout << "Photo inserted: " << id << '\n';
    }

    void erase(PhotoNode* photo)
    {
        if (photo->next == photo)
        {
            head = tail = current = NULL;
        }
        else
        {
            photo->prev->next = photo->next;
            photo->next->prev = photo->prev;
            if (photo == head) head = photo->next;
            if (photo == tail) tail = photo->prev;
            if (photo == current) current = photo->next;
        }
        delete photo;
    }

    void removePhoto(int id)
    {
        PhotoNode* photo = findPhoto(id);
        if (photo == NULL)
        {
            cout << "Photo not found.\n";
            return;
        }
        erase(photo);
        cout << "Photo removed: " << id << '\n';
    }

    void removeCurrent()
    {
        if (current == NULL)
        {
            cout << "Album is empty.\n";
            return;
        }
        int id = current->ID;
        erase(current);
        cout << "Current photo removed: " << id << '\n';
    }

    void moveNext()
    {
        if (current == NULL) cout << "Album is empty.\n";
        else { current = current->next; showPhoto(current); }
    }

    void movePrevious()
    {
        if (current == NULL) cout << "Album is empty.\n";
        else { current = current->prev; showPhoto(current); }
    }

    void displayForward()
    {
        if (current == NULL)
        {
            cout << "Album is empty.\n";
            return;
        }
        PhotoNode* temp = current;
        do
        {
            showPhoto(temp);
            temp = temp->next;
        } while (temp != current);
    }

    void displayBackward()
    {
        if (current == NULL)
        {
            cout << "Album is empty.\n";
            return;
        }
        PhotoNode* temp = current;
        do
        {
            showPhoto(temp);
            temp = temp->prev;
        } while (temp != current);
    }

    void searchPhoto(int id)
    {
        PhotoNode* photo = findPhoto(id);
        if (photo == NULL) cout << "Photo not found.\n";
        else showPhoto(photo);
    }

    void countPhotos()
    {
        int count = 0;
        if (head != NULL)
        {
            PhotoNode* temp = head;
            do
            {
                count++;
                temp = temp->next;
            } while (temp != head);
        }
        cout << "Total photos: " << count << '\n';
    }
};

bool readPhoto(int& id, string& n, string& d, string& l)
{
    cout << "Photo ID: ";
    if (!(cin >> id)) return false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Photo name: ";
    if (!getline(cin, n)) return false;
    cout << "Date taken: ";
    if (!getline(cin, d)) return false;
    cout << "Location: ";
    return static_cast<bool>(getline(cin, l));
}

int main()
{
    PhotoAlbum album;
    int count, id, choice;
    string name, date, location;
    cout << "Number of photos: ";
    if (!(cin >> count) || count < 0) return 1;
    for (int i = 0; i < count; i++)
    {
        if (!readPhoto(id, name, date, location)) return 1;
        album.addPhoto(id, name, date, location);
    }
    cout << "\n1 Add Photo | 2 Insert After Current\n"
         << "3 Remove by ID | 4 Remove Current\n"
         << "5 Move Next | 6 Move Previous\n"
         << "7 Display Forward | 8 Display Backward\n"
         << "9 Search Photo | 10 Count Photos | 0 Exit\n";
    while (true)
    {
        cout << "\nChoice: ";
        if (!(cin >> choice)) return 0;
        if (choice == 0) break;
        else if (choice == 1 || choice == 2)
        {
            if (!readPhoto(id, name, date, location)) return 1;
            if (choice == 1)
                album.addPhoto(id, name, date, location);
            else
                album.insertAfterCurrent(id, name, date, location);
        }
        else if (choice == 3 || choice == 9)
        {
            cout << "Photo ID: ";
            if (!(cin >> id)) return 1;
            if (choice == 3) album.removePhoto(id);
            else album.searchPhoto(id);
        }
        else if (choice == 4) album.removeCurrent();
        else if (choice == 5) album.moveNext();
        else if (choice == 6) album.movePrevious();
        else if (choice == 7) album.displayForward();
        else if (choice == 8) album.displayBackward();
        else if (choice == 10) album.countPhotos();
        else cout << "Invalid choice.\n";
    }
    return 0;
}
