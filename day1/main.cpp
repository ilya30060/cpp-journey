#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <locale.h>

class Book
{
private:
    std::string _title;
    std::string _author;
    int _year;

public:
    Book(std::string title, std::string author, int year): _title(title), _author(author), _year(year)
    {
        std::wcout << L"Book: создан.\n";
    }

    virtual void display(void)
    {
        std::wcout << L"Book: выведена информация.\n";
    }

    ~Book()
    {
        std::wcout << L"Book: удалён.\n";
    }
};

class LibraryBook: public Book 
{
private:
    bool _is_available;
public:
    LibraryBook(std::string title, std::string author, int year): Book(title, author, year), _is_available(true)
    {
        std::wcout << L"LibraryBook: создан.\n";
    }

    void display(void) override
    {
        std::wcout << L"LibraryBook: статус доступности - " << _is_available << L".\n";
        std::wcout << L"LibraryBook: выведена информация.\n";
    }

    ~LibraryBook()
    {
        std::wcout << L"LibraryBook: удалён.\n";
    }
};

int main(void)
{
    setlocale(LC_ALL, "Russian");
    std::vector<std::unique_ptr<Book>> myLib;
    myLib.push_back(std::make_unique<Book>(Book("Колобок", "Русский фольклор", 1023)));
    myLib.push_back(std::make_unique<Book>(Book("НеКолобок", "Современный фольклор", 2023)));
    myLib.push_back(std::make_unique<LibraryBook>(LibraryBook("Евгений Онегин", "А. С. Пушкин", 1868)));

    for (const auto& book : myLib)
    {
        book->display();
    }
    return 0;
}