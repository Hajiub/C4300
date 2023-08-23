#include <iostream>

template <typename T>
class DynamicArray
{
    private:
        size_t m_size;
        T * m_array;
    public:
        DynamicArray(size_t size)
        : m_size(size)
        , m_array(new T[size])
        {
            std::cout << "Array constructor\n";
        }
        T& operator [] (size_t index) 
        { 
            return m_array[index]; 
        }
        ~DynamicArray() 
        { 
            delete [] m_array; 
            std::cout << "Array Destructor" << std::endl;
        }
        
        // get from the array
        T get(size_t index) const
        {
            return m_array[index];
        }
        // set 
        void set(size_t index, T val)
        {
            m_array[index] = val;
        }
        void print() const
        {
            for (size_t i = 0; i < m_size; i++)
            {
                std::cout << m_array[i] << std::endl;
            }
        }
};

int main(int argv, char ** args)
{   
    DynamicArray<int> arr(5);
   
    arr.set(0, 10);
    arr.set(1, 3434);
    std::cout<< arr.get(0) << std::endl;
    arr.print();
    return 0;
}