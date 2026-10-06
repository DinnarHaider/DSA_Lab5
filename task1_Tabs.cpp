#include <iostream>
using namespace std;

class Node
{
public:
    int ID;
    string title;
    string URL;
    Node* next;
    Node* prev;

    Node(int id, string Title, string url)
    {
        ID = id;
        title = Title;
        URL = url;

        next = NULL;
        prev = NULL;
    }
};

class tabManager
{
public:
    Node* current;
    Node* head;
    Node* tail;

    tabManager()
    {
        current = NULL;
        head = NULL;
        tail = NULL;
    }

    void newTab(int id, string Title, string url)
    {
        Node* newNode = new Node(id, Title, url);

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
            current = newNode;
            head->next = head;
            head->prev = head;
        }
        else
        {
            newNode->prev = tail;
            newNode->next = head;
            tail->next = newNode;
            head->prev = newNode;
            tail = newNode;
            current = newNode;
        }
    }


    void removeTab()
    {
        if (head == NULL)
        {
            cout << "There is no tab" << endl;
        }

        else if (head == tail)
        {
            delete current;
            head = NULL;
            tail = NULL;
            current = NULL;

            cout << "The list is empty now" << endl;
        }

        else
        {
            Node* temp = current;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            if (current == head)
            {
                head = current->next;
            }
            if (current == tail)
            {
                tail = current->prev;
            }
            Node* nextTab = temp->next;
            delete temp;
            temp = NULL;
            current = nextTab;
            head->prev = tail;
            tail->next = head;
        }
    }


    void moveNext()
    {
        if (current == NULL)
        {
            cout << "There are no tabs" << endl;
        }
        else
        {
            current = current->next;
        }
    }


    void movePrevious()
    {
        if (current == NULL)
        {
            cout << "There are no tabs" << endl;
        }
        else
        {
            current = current->prev;
        }
    }


    void displayCurrent()
    {

        if (current == NULL)
        {
            cout << "There are no tabs to display." << endl;
            return;
        }

        cout << "The ID of current tab = " << current->ID << endl;
        cout << "The title of current tab = " << current->title << endl;
        cout << "The URL of current tab = " << current->URL << endl;
    }

    void displayTabsForward()
    {
        if (head == NULL)
    {
    cout << "There are no tabs" << endl;
    return;
    }
    else{
        Node* temp=head;
        do
        {
            cout<<" The ID of the Tab="<<temp->ID<<endl;
            cout<<" The title of the Tab="<<temp->title<<endl;
            cout<<" The URL of the Tab="<<temp->URL<<endl;

            temp=temp->next;

            
        }
        while(temp!=head);

    }}

    void displayTabsBackwards()
    {
        if (head == NULL)
    {
    cout << "There are no tabs" << endl;
    return;
    }   
    
    else{
    Node* temp=tail;
        do
        {
            cout<<" The ID of the Tab="<<temp->ID<<endl;
            cout<<" The title of the Tab="<<temp->title<<endl;
            cout<<" The URL of the Tab="<<temp->URL<<endl;

            temp=temp->prev;

            
        }
        while(temp!=tail);

    }}

    void searchTab(int id)

    {
        Node* temp=head;
        do
        {
            if(temp->ID==id)
            {
            cout<<" The ID of the Tab="<<temp->ID<<endl;
            cout<<" The title of the Tab="<<temp->title<<endl;
            cout<<" The URL of the Tab="<<temp->URL<<endl;
            return;
            }
            temp=temp->next;

        }
        while(temp!=head);

    }
};


int main()
{
    tabManager tm;

    cout << "========== TEST 1: ADDING TABS ==========" << endl;

    tm.newTab(1, "YouTube", "www.youtube.com");
    tm.newTab(2, "Google", "www.google.com");
    tm.newTab(3, "Substack", "www.substack.com");
    tm.newTab(4, "LMS", "www.lms.com");
    cout << "========== DISPLAY CURRENT TAB ==========" << endl;
    tm.displayCurrent();
    cout << "==========  MOVE TO NEXT TAB ==========" << endl;
    tm.moveNext();
    tm.displayCurrent();
    cout << "==========  MOVE TO PREVIOUS TAB ==========" << endl;
    tm.movePrevious();
    tm.displayCurrent();
    cout << "========== DISPLAY TABS FORWARD ==========" << endl;
    tm.displayTabsForward();
    cout << "========== DISPLAY TABS BACKWARDS ==========" << endl;
    tm.displayTabsBackwards();
    cout << "========== SEARCH EXISTING TAB ==========" << endl;
    tm.searchTab(2);

    cout << "========== REMOVE CURRENT TAB ==========" << endl;
    cout << "Before removing:" << endl;
    tm.displayCurrent();

    tm.removeTab();

    cout << "After removing:" << endl;
    tm.displayCurrent();


    cout << "==========DISPLAY AFTER REMOVAL ==========" << endl;

    tm.displayTabsForward();
    return 0;
}