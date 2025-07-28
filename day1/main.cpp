#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <locale.h>

class Book
{
protected:
    std::wstring _title;
    std::wstring _author;
    int _year;

public:
    Book(const std::wstring& title, const std::wstring& author, int year)
    : _title(title), _author(author), _year(year)
    {
        std::wcout << L"Book(" << _title << L"): создан.\n";
    }

    virtual void display(void)
    {
        std::wcout << L"\"" << _title << L"\" " << _author << L", " << _year
        << L"\nBook(" << _title << L"): выведена информация.\n";
    }

    virtual ~Book()
    {
        std::wcout << L"Book(" << _title << L"): удалён.\n";
    }
};

class LibraryBook: public Book 
{
private:
    bool _is_available;
public:
    LibraryBook(const std::wstring& title, const std::wstring& author, int year)
    : Book(title, author, year), _is_available(true)
    {
        std::wcout << L"LibraryBook(" << _title << L"): создан.\n";
    }

    void display(void) override
    {
        std::wcout << L"[Библиотека] \"" << _title << L"\" " << _author << L", " << _year
        << L" - " << (_is_available ? L"доступна" : L"недоступна") << L".\n";
        std::wcout << L"LibraryBook(" << _title << L"): выведена информация.\n";
    }

    ~LibraryBook() override
    {
        std::wcout << L"LibraryBook(" << _title << L"): удалён.\n";
    }
};

int main(void)
{
    setlocale(LC_ALL, "Russian");
    std::vector<std::unique_ptr<Book>> myLib;
    myLib.push_back(std::make_unique<Book>(L"Колобок", L"Русский фольклор", 1023));
    myLib.push_back(std::make_unique<Book>(L"НеКолобок", L"Современный фольклор", 2023));
    myLib.push_back(std::make_unique<LibraryBook>(L"Евгений Онегин", L"А. С. Пушкин", 1868));

    for (const auto& book : myLib)
    {
        book->display();
    }
    return 0;
}