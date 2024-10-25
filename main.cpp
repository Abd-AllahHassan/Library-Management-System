#include <iostream>
#include <string>

using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    string genre;
    bool available;

    bool operator==(const Book& other) const {
        return title == other.title &&
            author == other.author &&
            ISBN == other.ISBN &&
            genre == other.genre;
    }
    bool operator>(const Book& other) const {

        return title > other.title;
    }

};

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* previous;

    Node(const T& item) : data(item), next(nullptr), previous(nullptr) {}
};

template <typename T>
class Container {
public:
    Node<T>* head;
    Node<T>* tail;
    size_t length;

    Container() : head(nullptr), tail(nullptr), length(0) {}

    ~Container() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isEmpty() {
        return (head == nullptr);
    }

    void push_back(const T& item) {
        if (isEmpty()) {
            add_first(item);
        }
        else {
            Node<T>* temp = tail;
            Node<T>* newnode = new Node<T>(item);
            newnode->previous = temp;
            temp->next = newnode;
            tail = newnode;
        }
    }

    void add_first(const T& item) {
        Node<T>* newnode = new Node<T>(item);

        if (isEmpty()) {
            newnode->next = nullptr;
            head = newnode;
            tail = newnode;
        }
        else {
            newnode->next = head;
            head->previous = newnode;
            head = newnode;
        }
    }

    int count() {
        int counter = 0;
        Node<T>* temp = head;

        while (temp != NULL) {
            counter++;
            temp = temp->next;
        }
        return counter;
    }

    void insertAt(const T& item, size_t index) {
        if (index > count()) {
            return;
        }

        if (index == 0) {
            Node<T>* newNode = new Node<T>(item);
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
            length++;
            return;
        }

        Node<T>* current = head;
        for (size_t i = 1; i < index; ++i) {
            current = current->next;
        }

        Node<T>* newNode = new Node<T>(item);
        newNode->next = current->next;
        current->next->previous = newNode;
        current->next = newNode;
        newNode->previous = current;
        length++;
    }

    void bubbleSort() {
        if (isEmpty()) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            Node<T>* current = head;
            while (current->next != nullptr) {
                if (current->data > current->next->data) {

                    T temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        cout << "Sorting Done :)\n";
    }


    void remove(const Book& bookToRemove) {
        if (isEmpty()) {
            cout << "There are no items to delete.\n";
            return;
        }

        Node<T>* current = head;
        Node<T>* prev = nullptr;

        while (current != nullptr) {
            if (current->data == bookToRemove) {
                if (prev == nullptr) {
                    head = current->next;
                    if (head != nullptr) {
                        head->previous = nullptr;
                    }
                }
                else {
                    prev->next = current->next;
                    if (current->next) {
                        current->next->previous = prev;
                    }
                }
                delete current;
                length--;
                cout << "removed successfully \n";
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Not found.\n";
    }

    T find(const Book& bookToFind) {
        Node<T>* current = head;
        while (current) {
            if (current->data == bookToFind) {
                return current->data;
            }
            current = current->next;
        }
        return T();
    }

    size_t getSize() const {
        return length;
    }

    T& operator[](size_t index) {
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            if (current) {
                current = current->next;
            }
            else {
                throw out_of_range("Index out of bounds.");
            }
        }
        if (current) {
            return current->data;
        }
        else {
            throw out_of_range("Index out of bounds.");
        }
    }
};

void LibraryMangemmentSystem()
{
    Container<Book> catalog;

    while (true) {
        cout << "##############################\n";
        cout << "Library Management System" << endl;
        cout << "1. Add a book" << endl;
        cout << "2. Remove a book" << endl;
        cout << "3. Search for a book by title" << endl;
        cout << "4. Borrow a book" << endl;
        cout << "5. Show Book Statistics" << endl;
        cout << "6. Add a book at a specific position" << endl;//for testing
        cout << "7. Display All books " << endl;//for testing
        cout << "8. Add in the first " << endl;//for testing
        cout << "9. Sorting by title " << endl;
        cout << "10. Quit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            Book newBook;
            cout << "Enter book title: ";
            cin >> newBook.title;
            cout << "Enter author: ";
            cin >> newBook.author;
            cout << "Enter ISBN: ";
            cin >> newBook.ISBN;
            cout << "Enter genre: ";
            cin >> newBook.genre;
            newBook.available = true;
            catalog.push_back(newBook);
        }
        else if (choice == 2) {
            Book bookToRemove;
            cout << "Enter book title to remove: ";
            cin >> bookToRemove.title;
            cout << "Enter author: ";
            cin >> bookToRemove.author;
            cout << "Enter ISBN: ";
            cin >> bookToRemove.ISBN;
            cout << "Enter genre: ";
            cin >> bookToRemove.genre;
            bookToRemove.available = true;
            catalog.remove(bookToRemove);
        }
        else if (choice == 3) {
            Book searchBook;
            cout << "Enter book title to search for: ";
            cin >> searchBook.title;
            cout << "Enter author: ";
            cin >> searchBook.author;
            cout << "Enter ISBN: ";
            cin >> searchBook.ISBN;
            cout << "Enter genre: ";
            cin >> searchBook.genre;
            searchBook.available = true;

            Book foundBook = catalog.find(searchBook);

            if (foundBook.title != "") {
                cout << "Book found:" << endl;
                cout << "Title: " << foundBook.title << endl;
                cout << "Author: " << foundBook.author << endl;
                cout << "ISBN: " << foundBook.ISBN << endl;
                cout << "Genre: " << foundBook.genre << endl;
            }
            else {
                cout << "Book not found." << endl;
            }
        }
        else if (choice == 4) {
            Book bookToBorrow;
            cout << "Enter book title : ";
            cin >> bookToBorrow.title;

            bool borrowed = false;
            for (size_t i = 0; i < catalog.count(); ++i) {
                if (catalog[i].title == bookToBorrow.title && catalog[i].available) {
                    catalog[i].available = false;
                    borrowed = true;
                    cout << "Book borrowed successfully." << endl;
                    break;
                }
            }
            if (!borrowed) {
                cout << "Book not available for borrowing." << endl;
            }
        }
        else if (choice == 5) {
            size_t totalBooks = catalog.count();
            size_t availableBooks = 0;
            for (size_t i = 0; i < totalBooks; ++i) {
                if (catalog[i].available) {
                    availableBooks++;
                }
            }
            size_t borrowedBooks = totalBooks - availableBooks;

            cout << "Total Books: " << totalBooks << endl;
            cout << "Available Books: " << availableBooks << endl;
            cout << "Borrowed Books: " << borrowedBooks << endl;
        }
        else if (choice == 6) {
            Book newBook;
            size_t position;
            cout << "Enter the position to add the book: ";
            cin >> position;

            if (position > catalog.count()) {
                cout << "Invalid position. Book not added." << endl;
            }
            else {
                cout << "Enter book title: ";
                cin >> newBook.title;
                cout << "Enter author: ";
                cin >> newBook.author;
                cout << "Enter ISBN: ";
                cin >> newBook.ISBN;
                cout << "Enter genre: ";
                cin >> newBook.genre;
                newBook.available = true;

                catalog.insertAt(newBook, position);
                cout << "Book added at position " << position << endl;
            }
        }
        else if (choice == 7) {
            cout << "All books :\n";
            Node<Book>* temp = catalog.head;
            while (temp != nullptr) {
                cout << "Title: " << temp->data.title << endl;
                cout << "Author: " << temp->data.author << endl;
                cout << "ISBN: " << temp->data.ISBN << endl;
                cout << "Genre: " << temp->data.genre << endl;
                cout << "Available: " << (temp->data.available ? "Yes" : "No") << endl;
                cout << "----------------------" << endl;
                temp = temp->next;
            }
        }
        else if (choice == 8) {
            Book newbook;
            cout << "Enter book title: ";
            cin >> newbook.title;
            cout << "Enter author: ";
            cin >> newbook.author;
            cout << "Enter ISBN: ";
            cin >> newbook.ISBN;
            cout << "Enter genre: ";
            cin >> newbook.genre;
            newbook.available = true;
            catalog.add_first(newbook);
        }
        else if (choice == 9) {
            catalog.bubbleSort();
        }
        else if (choice == 10) {
            cout << "Exiting the program" << endl;
            break;
        }
        else {
            cout << "Felse choice  . try again" << endl;
        }
    }

}

int main() {

    LibraryMangemmentSystem();

    return 0;
}
