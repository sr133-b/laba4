#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <clocale>
using namespace std;

class ProgramError {
public:
    virtual string what() const {
        return "Ошибка в программе";
    }
};

class NotEnoughMemory : public ProgramError {
public:
    string what() const override {
        return "Недостаточно памяти";
    }
};

class IOError : public ProgramError {
public:
    string what() const override {
        return "Ошибка ввода/вывода";
    }
};

class FileReadError : public IOError {
public:
    string what() const override {
        return "Ошибка чтения файла";
    }
};

class FileWriteError : public IOError {
public:
    string what() const override {
        return "Ошибка записи файла";
    }
};

template<typename T>
class PtrArray {
private:
    T* data[10];
    int count = 0;
public:
    void add(T* ptr) {
        if (count < 10) {
            data[count++] = ptr;
        }
    }

    T*& operator[](int index) {
        return data[index];
    }

    int size() const {
        return count;
    }
};

class TestClass {
public:
    void print() const {
        cout << "TestClass" << endl;
    }
};

class Anotherclass {
public:
    void display() const {
        cout << "Anotherclass" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    PtrArray<ProgramError> errors;

    errors.add(new NotEnoughMemory());
    errors.add(new FileReadError());
    errors.add(new FileWriteError());

    cout << "Ошибки в программе:" << endl;
    for (int i = 0; i < errors.size(); i++) {
        cout << errors[i]->what() << endl;
    }

    PtrArray<TestClass> testObjects;
    testObjects.add(new TestClass());
    testObjects.add(new TestClass());

    PtrArray<Anotherclass> anotherObjects;
    anotherObjects.add(new Anotherclass());

    cout << "\nТестовые объекты:" << endl;
    for (int i = 0; i < testObjects.size(); i++) {
        testObjects[i]->print();
    }

    cout << "\nДругие объекты:" << endl;
    for (int i = 0; i < anotherObjects.size(); i++) {
        anotherObjects[i]->display();
    }

    cout << "\nДоступ через оператор []:" << endl;
    testObjects[0]->print();

    // Явное удаление объектов
    for (int i = 0; i < errors.size(); i++) delete errors[i];
    for (int i = 0; i < testObjects.size(); i++) delete testObjects[i];
    for (int i = 0; i < anotherObjects.size(); i++) delete anotherObjects[i];

    return 0;
}