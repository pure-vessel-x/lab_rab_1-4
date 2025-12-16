#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class BookType {
    FICTION,
    TECHNICAL
};

class Book {
private:
    string author;
    string title;
    BookType type;

public:
    Book(string author, string title, BookType type) : author(author), title(title), type(type) {
        if (author.empty() || title.empty()) {
            cout << "Ошибка: Имя автора и название книги не могут быть пустыми." << endl;
            exit(1);
        }
    }

    string getAuthor() const { return author; }
    string getTitle() const { return title; }
    BookType getType() const { return type; }
};

void printBookCountsSwitch(const vector<Book>& library) {
    int fictionCount = 0;
    int technicalCount = 0;

    for (const auto& book : library) {
        switch (book.getType()) {
        case BookType::FICTION:
            fictionCount++;
            break;
        case BookType::TECHNICAL:
            technicalCount++;
            break;
        }
    }

    cout << "Количество художественной литературы: " << fictionCount << endl;
    cout << "Количество технической литературы: " << technicalCount << endl;
}

void printBookCountsNoSwitch(const vector<Book>& library) {
    int fictionCount = 0;
    int technicalCount = 0;

    for (const auto& book : library) {
        if (book.getType() == BookType::FICTION) {
            fictionCount++;
        }
        else {
            technicalCount++;
        }
    }

    cout << "Количество художественной литературы: " << fictionCount << endl;
    cout << "Количество технической литературы: " << technicalCount << endl;
}

int main() {
    vector<Book> library;

    library.emplace_back("Лев Толстой", "Война и мир", BookType::FICTION);
    library.emplace_back("Александр Пушкин", "Евгений Онегин", BookType::FICTION);
    library.emplace_back("Джон Страуструп", "Язык программирования C++", BookType::TECHNICAL);
    library.emplace_back("Кнут", "Искусство программирования", BookType::TECHNICAL);
    library.emplace_back("Ричард Бах", "Чайка по имени Джонатан Ливингстон", BookType::FICTION);


    cout << "Статистика библиотеки (с использованием switch):\n";
    printBookCountsSwitch(library);

    cout << "\nСтатистика библиотеки (без использования switch):\n";
    printBookCountsNoSwitch(library);

    return 0;
}