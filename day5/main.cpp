#include <memory>

template <typename T>
class CustomVector
{
private:
    std::allocator<T*> _alloc;
    size_t _size;
    size_t _capacity;
    T* _data;
public:
    CustomVector(size_t initial_size = 0)
    : _alloc(), _size(0), _capacity(initial_size)
    {
        _data = _alloc.allocate(initial_size);
    }

    CustomVector(CustomVector&& origin)
    : _alloc(std::move(origin._alloc)), _size(std::move(origin._size)),
    _capacity(std::move(origin._capacity)), _data(std::move(origin._data))
    {}

    CustomVector& operator=(CustomVector&& origin)
    {
        _alloc = std::move(origin._alloc);
        _size = std::move(origin._size);
        _capacity = std::move(origin._capacity);
        _data = std::move(origin._data);
        return *this;
    }

    ~CustomVector()
    {
        _alloc.deallocate(_data, _capacity);
    }
    
    void push_back(const T& new_element)
    {
        if (_size == _capacity)
        {   //expanding and reallocating
            T* temp_data = _alloc.allocate(_capacity * 2);
            std::copy(_data, _data + _size, temp_data);
            _alloc.deallocate(_data, _capacity);
            _data = std::move(temp_data);
            _capacity *= 2;
        }

        _data[_size] = new_element;
        ++_size;
    }

    void reserve(const size_t new_capacity)
    {
        T* temp_data = _alloc.allocate(new_capacity);
        const size_t min_size = std::min(_size, new_capacity);
        std::copy(_data, _data + min_size, temp_data);
        _alloc.deallocate(_data, _capacity);
        _data = std::move(temp_data);
        _size = min_size;
        _capacity = new_capacity;
    }

    T* begin(void) { return _data; }
    const T* begin(void) const noexcept { return _data; }

    T* end(void) { return _data + _size; }
    const T* end(void) const noexcept { return _data + _size; }


};

int main(void)
{

    return 0;
}
