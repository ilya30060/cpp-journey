#include <memory>
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <locale>


class SafeArray
{
private:
    std::unique_ptr<int[]> _data;
    size_t _size;
public:
    SafeArray(const size_t initial_size = 64)
    :_data(std::make_unique<int[]>(initial_size)), _size(initial_size)
    {}
    
    SafeArray(const SafeArray&) = delete;
    SafeArray& operator=(const SafeArray&) = delete;
    
    SafeArray(SafeArray&& origin) noexcept
    :_data(std::move(origin._data)), _size(origin._size)
    {
        origin._size = 0;
    }

    SafeArray& operator=(SafeArray&& origin) noexcept
    {
        _data = std::move(origin._data);
        _size = origin._size;
        origin._size = 0;
        return *this;
    }
    
    int& at(const size_t index)
    {
        if (index >= 0 && index < _size)
        {
            return _data[index];
        }
        else
        {
            throw std::out_of_range("SafeArray::at(): invalid index.\n");
        }
    }
    
    void resize(size_t new_size)
    {
        //realloc для std::unique_ptr???
        size_t min_size = std::min(_size, new_size);
        std::unique_ptr temp = std::make_unique<int[]>(new_size);
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
        // 1. Тест конструктора и at()
        SafeArray arr(3);
        arr.at(0) = 10;
        arr.at(1) = 20;
        arr.at(2) = 30;
        std::wcout << L"Создан массив: " << arr.at(0) << ", " << arr.at(1) << ", " << arr.at(2) << std::endl;

        // 2. Тест исключения при выходе за границы
        try {
            arr.at(3) = 40; // Должно бросить исключение
        } catch (const std::out_of_range& e) {
            std::wcout << L"Ошибка: " << e.what() << std::endl; // Ожидаемое поведение
        }

        // 3. Тест resize()
        arr.resize(5);
        arr.at(3) = 40;
        arr.at(4) = 50;
        std::wcout << L"После увеличения: " << arr.at(3) << L", " << arr.at(4) << std::endl;

        arr.resize(2);
        std::wcout << L"После уменьшения: " << arr.at(0) << L", " << arr.at(1) << std::endl;

        // 4. Тест move-семантики
        SafeArray arr_moved = std::move(arr);
        std::wcout << L"После перемещения: " << arr_moved.at(0) << L", " << arr_moved.at(1) << std::endl;

        // 5. Проверка состояния перемещённого объекта
        if (arr.getSize() == 0) {
            std::wcout << L"Исходный массив после move корректен (размер = 0)" << std::endl;
        }

    } catch (const std::exception& e) {
        std::wcerr << L"Критическая ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}