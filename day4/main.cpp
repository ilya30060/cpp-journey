#include <memory>
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <locale>

template <typename T> 
class GenericArray
{
private:
    std::unique_ptr<T[]> _data;
    size_t _size;
public:
    GenericArray(const size_t initial_size = 64)
    :_data(std::make_unique<T[]>(initial_size)), _size(initial_size)
    {}
    
    GenericArray(const GenericArray&) = delete;
    GenericArray& operator=(const GenericArray&) = delete;
    
    GenericArray(GenericArray&& origin) noexcept
    :_data(std::move(origin._data)), _size(origin._size)
    {
        origin._size = 0;
    }

    GenericArray& operator=(GenericArray&& origin) noexcept
    {
        _data = std::move(origin._data);
        _size = origin._size;
        origin._size = 0;
        return *this;
    }
    
    T* begin(void) {return _data.get();}
    const T* begin(void) const noexcept {return _data.get();}


    T* end(void) { return _data.get() + _size; }
    const T* end(void) const noexcept { return _data.get() + _size; }


    T& at(const size_t index)
    {
        if (index >= 0 && index < _size)
        {
            return _data[index];
        }
        else
        {
            throw std::out_of_range("GenericArray::at(): invalid index.\n");
        }
    }
    const T& at(const size_t index) const noexcept
    {
        if (index >= 0 && index < _size)
        {
            return _data[index];
        }
        else
        {
            throw std::out_of_range("GenericArray::at(): invalid index.\n");
        }
    }

    void resize(const size_t new_size)
    {
        size_t min_size = std::min(_size, new_size);
        std::unique_ptr temp = std::make_unique<T[]>(new_size);
        std::copy(_data.get(), _data.get() + min_size, temp.get());
        _data = std::move(temp);
        _size = new_size;
        std::wcout << L"Новый размер: " << _size << std::endl;
    }

    size_t getSize()
    {
        return _size;
    }
};

int main(void)
{
    setlocale(LC_ALL, "Russian");
    try {
        // 1. Тест с целыми числами (int)
        {
            std::wcout << L"\n=== Тест GenericArray<int> ===\n";
            GenericArray<int> int_arr(3);
            int_arr.at(0) = 10;
            int_arr.at(1) = 20;
            int_arr.at(2) = 30;

            // Проверка доступа через at()
            std::wcout << L"Элементы массива (int): ";
            for (size_t i = 0; i < int_arr.getSize(); ++i) {
                std::wcout << int_arr.at(i) << L" ";
            }
            std::wcout << std::endl;

            // Проверка итераторов (range-based for)
            std::wcout << L"Range-based for: ";
            for (const auto& item : int_arr) {
                std::wcout << item << L" ";
            }
            std::wcout << std::endl;

            // Проверка исключения
            try {
                int_arr.at(3) = 40;
            } catch (const std::out_of_range& e) {
                std::wcout << L"Ошибка (int): " << e.what() << std::endl;
            }
        }

        // 2. Тест со строками (std::string)
        {
            std::wcout << L"\n=== Тест GenericArray<std::string> ===\n";
            GenericArray<std::wstring> str_arr(2);
            str_arr.at(0) = L"Привет";
            str_arr.at(1) = L"Мир";

            // Проверка итераторов
            std::wcout << L"Строки: ";
            for (const auto& s : str_arr) {
                std::wcout << s << L" ";
            }
            std::wcout << std::endl;
        }

        // 3. Тест с изменением размера (resize)
        {
            std::wcout << L"\n=== Тест resize() ===\n";
            GenericArray<double> double_arr(2);
            double_arr.at(0) = 3.14;
            double_arr.at(1) = 2.71;

            std::wcout << L"До resize: ";
            for (const auto& val : double_arr) {
                std::wcout << val << L" ";
            }
            std::wcout << std::endl;

            double_arr.resize(4);
            double_arr.at(2) = 1.41;
            double_arr.at(3) = 0.99;

            std::wcout << L"После resize: ";
            for (const auto& val : double_arr) {
                std::wcout << val << L" ";
            }
            std::wcout << std::endl;
        }

        // 4. Тест move-семантики
        {
            std::wcout << L"\n=== Тест перемещения ===\n";
            GenericArray<char> char_arr(3);
            char_arr.at(0) = 'A';
            char_arr.at(1) = 'B';
            char_arr.at(2) = 'C';

            GenericArray<char> moved_arr = std::move(char_arr);
            std::wcout << L"После перемещения: ";
            for (const auto& c : moved_arr) {
                std::wcout << c << L" ";
            }
            std::wcout << std::endl;

            if (char_arr.getSize() == 0) {
                std::wcout << L"Исходный массив пуст (корректно)\n";
            }
        }

    } catch (const std::exception& e) {
        std::wcerr << L"Критическая ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}