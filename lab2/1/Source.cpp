#include <iostream>
#include <string>

using namespace std;

class Publication {
protected:
    string title;
    float price;
public:
    virtual void getdata() {
        cout << "Введите название: ";
        getline(cin >> ws, title);
        cout << "Введите цену: ";
        cin >> price;
    }
    virtual void putdata() {
        cout << "Название: " << title << endl;
        cout << "Цена: " << price << endl;
    }
};

class Sales {
protected:
    float sales_data[3];
public:
    void getSalesData() {
        cout << "Введите данные о продажах за последние 3 месяца:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "Месяц " << (i + 1) << ": ";
            cin >> sales_data[i];
        }
    }
    void putSalesData() {
        cout << "Данные о продажах за последние 3 месяца:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "Месяц " << (i + 1) << ": " << sales_data[i] << endl;
        }
    }
};

class Book : public Publication, public Sales {
private:
    int pages;
public:
    void getdata() override {
        Publication::getdata();
        cout << "Введите количество страниц: ";
        cin >> pages;
        getSalesData();
    }
    void putdata() override {
        Publication::putdata();
        cout << "Количество страниц: " << pages << endl;
        putSalesData();
    }
};

class Audio : public Publication, public Sales {
private:
    float recordingTime;
public:
    void getdata() override {
        Publication::getdata();
        cout << "Введите время записи (в минутах): ";
        cin >> recordingTime;
        getSalesData();
    }
    void putdata() override {
        Publication::putdata();
        cout << "Время записи (в минутах): " << recordingTime << endl;
        putSalesData();
    }
};

int main() {
    Book book;
    Audio audio;

    cout << "Ввод данных для книги:" << endl;
    book.getdata();
    cout << endl;

    cout << "Ввод данных для аудиозаписи:" << endl;
    audio.getdata();
    cout << endl;

    cout << "Данные о книге:" << endl;
    book.putdata();
    cout << endl;

    cout << "Данные об аудиозаписи:" << endl;
    audio.putdata();

    return 0;
}
