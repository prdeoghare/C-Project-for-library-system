class Book {
private:
    std::string title;
    std::string author;
    std::string ISBN;
    bool isAvailable;
public:
    Book(std::string t, std::string a, std::string i);
    void checkOut();
    void returnBook();
    bool getAvailability() const;
    std::string getTitle() const;
};

class Library {
private:
    std::vector<Book> books;
public:
    void addBook(const Book& book);
    void listAvailableBooks() const;
    bool checkOutBook(const std::string& ISBN);
    bool returnBook(const std::string& ISBN);
};

class User {
private:
    std::string name;
    std::string userID;
public:
    User(std::string n, std::string id);
    void checkOutBook(Library& library, const std::string& ISBN);
    void returnBook(Library& library, const std::string& ISBN);
};

// Book class implementation
Book::Book(std::string t, std::string a, std::string i) : title(t), author(a), ISBN(i), isAvailable(true) {}

void Book::checkOut() {
    if (isAvailable) {
        isAvailable = false;
    }
}

void Book::returnBook() {
    isAvailable = true;
}

bool Book::getAvailability() const {
    return isAvailable;
}

std::string Book::getTitle() const {
    return title;
}

// Library class implementation
void Library::addBook(const Book& book) {
    books.push_back(book);
}

void Library::listAvailableBooks() const {
    for (const auto& book : books) {
        if (book.getAvailability()) {
            std::cout << book.getTitle() << std::endl;
        }
    }
}

bool Library::checkOutBook(const std::string& ISBN) {
    for (auto& book : books) {
        if (book.getISBN() == ISBN && book.getAvailability()) {
            book.checkOut();
            return true;
        }
    }
    return false;
}

bool Library::returnBook(const std::string& ISBN) {
    for (auto& book : books) {
        if (book.getISBN() == ISBN && !book.getAvailability()) {
            book.returnBook();
            return true;
        }
    }
    return false;
}

// User class implementation
User::User(std::string n, std::string id) : name(n), userID(id) {}

void User::checkOutBook(Library& library, const std::string& ISBN) {
    if (!library.checkOutBook(ISBN)) {
        std::cout << "Book is not available" << std::endl;
    }
}

void User::returnBook(Library& library, const std::string& ISBN) {
    if (!library.returnBook(ISBN)) {
        std::cout << "Book not found in library" << std::endl;
    }
}

int main() {
    Library library;
    Book book1("1984", "George Orwell", "12345");
    Book book2("Brave New World", "Aldous Huxley", "67890");

    library.addBook(book1);
    library.addBook(book2);

    library.listAvailableBooks();

    User user("Alice", "U001");
    user.checkOutBook(library, "12345");
    user.returnBook(library, "12345");

    library.listAvailableBooks();

    return 0;
}
