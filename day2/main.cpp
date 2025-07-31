#include <cstddef>
#include <iostream>
#include <locale>

class ResourceManager
{
private:
    int* _data;
    size_t _size;
public:
    ResourceManager()
    : _size(64), _data(new int[64])
    {
        std::wcout << L"Ресурсы выделены.\n";
    }
    
    ResourceManager(size_t size)
    : _size(size), _data(new int[size])
    {
        std::wcout << L"Ресурсы выделены.\n";
    }
    
    ResourceManager(const ResourceManager&) = delete;
    
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    void resize(size_t new_size)
    {
        if (new_size == _size) return;

        if (new_size == 0)
        {
            delete[] _data;
            _data = nullptr;
            return;
        }

        if (new_size < 0) throw std::invalid_argument("ResourceManager::resize(): new_size must be greater than 0(zero).\n");

        std::wcout << L"Приступаю к изменению размера контейнера.\n";
        //init
        int* temp_data;
        temp_data = new int[new_size];
        std::wcout << L"Создан буфер.\n";
        //choose range of copy
        size_t size_loop = 0;
        if (new_size <= _size)
        {
            size_loop = new_size;
        }
        else
        {
            size_loop = _size;
        }
        std::wcout << L"Определён размер копирования.\n";
        std::wcout << L"Приступаю к копированию данных в новый контейнер.\n";
        //deep copying
        for (size_t i = 0; i < size_loop; ++i)
        {
            temp_data[i] = _data[i];
        }
        std::wcout << L"Копирование завершено.\n";
        std::wcout << L"Приступаю к освобождению старой памяти.\n";
        //clean-up
        delete[] _data;
        _data = temp_data;
        _size = new_size;
        std::wcout << L"Освобождение старой памяти завершено.\n";
        std::wcout << L"Изменение размера завершено.\n";
    }
    
    ~ResourceManager()
    {
        if (_data != nullptr)
        {
            delete[] _data;
            _data = nullptr;
        }

        std::wcout << L"Ресурсы очищены.\n";
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    ResourceManager rm;
    rm.resize(20);
    rm.resize(5);
    return 0;
}
