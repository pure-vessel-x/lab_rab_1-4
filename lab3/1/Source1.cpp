
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace Parts {

    class Detail {
    protected:
        string name;
        double weight;

    public:
        Detail(const string& name, double weight) : name(name), weight(weight) {}

        virtual ~Detail() = default;

        virtual void print() const {
            cout << "Деталь: " << name << ", Вес: " << weight << endl;
        }

        double getWeight() const {
            return weight;
        }
    };

    class Assembly : public Detail {
    private:
        vector<Detail*> parts;

    public:
        Assembly(const string& name, double weight) : Detail(name, weight) {}

        void addPart(Detail* part) {
            parts.push_back(part);
        }

        void print() const override {
            cout << "Сборка: " << name << ", Общий вес: " << weight << ", Состоит из:" << endl;
            for (const auto& part : parts) {
                part->print();
            }
        }

        ~Assembly() override {
            for (auto& part : parts) {
                delete part;
            }
            parts.clear();
        }
    };

    template <typename T>
    T* createPart(const string& name, double weight);

    template <>
    Detail* createPart<Detail>(const string& name, double weight) {
        return new Detail(name, weight);
    }

    template <>
    Assembly* createPart<Assembly>(const string& name, double weight) {
        return new Assembly(name, weight);
    }

} // namespace Parts


int main() {
    setlocale(LC_ALL, "ru");
    using namespace Parts;

    vector<Detail*> warehouse;

    Detail* detail1 = createPart<Detail>("Болт", 0.1);
    Detail* detail2 = createPart<Detail>("Гайка", 0.05);
    Assembly* assembly1 = createPart<Assembly>("Соединение", 0.15);

    assembly1->addPart(detail1);
    assembly1->addPart(detail2);

    warehouse.push_back(assembly1);

    cout << "Содержимое склада:" << endl;
    for (const auto& part : warehouse) {
        part->print();
    }

    for (auto& part : warehouse) {
        delete part;
    }
    warehouse.clear();

    return 0;
}


/*
#include <iostream>
#include <vector>
#include <memory>
#include <random>

using namespace std;

class Base {
public:
    virtual ~Base() = default;
    virtual void print() const {
        cout << "Base" << endl;
    }
    virtual unique_ptr<Base> clone() const {
        return make_unique<Base>(*this);
    }
};

class Derived : public Base {
public:
    void print() const override {
        cout << "Derived" << endl;
    }
    unique_ptr<Base> clone() const override {
        return make_unique<Derived>(*this);
    }
};

void add(vector<unique_ptr<Base>>& storage, unique_ptr<Base> obj) {
    storage.push_back(std::move(obj));
}



int main() {
    using namespace std;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1);
    vector<unique_ptr<Base>> storage;


    for (int i = 0; i < 10; ++i) {
        if (distrib(gen) == 0) {
            add(storage, make_unique<Base>());
        }
        else {
            add(storage, make_unique<Derived>());
        }
    }

    for (size_t i = 0; i < storage.size(); ++i) {
        cout << "Object " << i << ": ";
        storage[i]->print();
    }

    return 0;
}
*/