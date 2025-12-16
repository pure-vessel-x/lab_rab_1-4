#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Класс человек
class Human {
public:
    int age;
    string name;

    Human(int age, string name) : age(age), name(name) {}

    virtual string getGroup() const = 0;

    virtual void display() const {
        cout << "Имя: " << name << ", Возраст: " << age << ", Группа: " << getGroup() << endl;
    }

    virtual ~Human() {} // Виртуальный деструктор
};

// Класс дошкольник
class Preschooler : public Human {
public:
    Preschooler(int age, string name) : Human(age, name) {}

    string getGroup() const override {
        return "Дошкольник";
    }
};

// Класс школьник
class Schoolchild : public Human {
public:
    Schoolchild(int age, string name) : Human(age, name) {}

    string getGroup() const override {
        return "Школьник";
    }
};

// Класс студент
class Student : public Human {
public:
    Student(int age, string name) : Human(age, name) {}

    string getGroup() const override {
        return "Студент";
    }
};

// Класс работающий
class Working : public Human {
public:
    Working(int age, string name) : Human(age, name) {}

    string getGroup() const override {
        return "Работающий";
    }
};

// Шаблонный класс для хранения массива указателей
template <typename T>
class PointerArray {
private:
    vector<T*> data;

public:
    // Конструктор
    PointerArray() {}

    // Деструктор
    ~PointerArray() {
        for (T* ptr : data) {
            delete ptr;
        }
        data.clear();
    }

    // Метод добавления элемента
    void add(T* element) {
        data.push_back(element);
    }

    // Перегрузка оператора []
    T* operator[](int index) {
        if (index < 0 || index >= data.size()) {
            throw out_of_range("Индекс выходит за границы массива");
        }
        return data[index];
    }

    // Получение размера массива
    size_t size() const {
        return data.size();
    }
};

int main() {
    // Создание объектов различных классов
    Preschooler* p1 = new Preschooler(5, "Елизавета");
    Schoolchild* s1 = new Schoolchild(10, "Максим");
    Student* st1 = new Student(20, "Алина");
    Working* w1 = new Working(35, "Алексей");

    // Создание шаблонного класса для хранения указателей на Human
    PointerArray<Human> humanArray;

    // Добавление объектов в массив
    humanArray.add(p1);
    humanArray.add(s1);
    humanArray.add(st1);
    humanArray.add(w1);


    cout << "Информация о людях:" << endl;
    for (size_t i = 0; i < humanArray.size(); ++i) {
        humanArray[i]->display();
    }

    cout << endl;
    cout << "/// Проверка исключения: ///" << endl;
    // Обработка исключения
    try {
        cout << "Попытка доступа к элементу с несуществующим индексом:" << endl;
        humanArray[10]->display(); // Попытка доступа за пределы массива
    }
    catch (const out_of_range& error) {
        cerr << "Ошибка: " << error.what() << endl;
    }
    catch (const domain_error& error) {
        cerr << "Ошибка domain_error: " << error.what() << endl;
    }


    return 0;
}
