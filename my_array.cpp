#include <iostream>
#include <initializer_list>



template<class T>
class My_vector
{
    T *m_vector;
    size_t m_length;
    size_t m_capacity;

    public:

    My_vector(): m_length{0}, m_capacity{0}, m_vector{nullptr}
    {
    }

    My_vector(size_t length): m_length{length}, m_capacity{length}, m_vector{new T[m_capacity]}
    {
    }

    My_vector(const My_vector &vec)
    {
        m_length = vec.m_length;
        m_capacity = vec.m_capacity;

        if(vec.m_vector)
        {
            m_vector = new T[m_capacity];

            for(size_t index{0}; index < m_capacity; ++index)
            {
                m_vector[index] = vec.m_vector[index];
            }
        }
        else
        {
            m_vector = nullptr;
        }
    }

    My_vector(const std::initializer_list<T> &list): My_vector(list.size())
    {
        size_t index{0};

        for(const auto &element: list)
        {
            m_vector[index] = element;
            ++index;
        }
    }

    ~My_vector()
    {
        delete[] m_vector;
    }

    My_vector& operator=(const My_vector &vec)
    {
        if(this == &vec)
        {
            return *this;
        }

        m_length = vec.m_length;
        m_capacity = m_length;

        delete[] m_vector;

        if(vec.m_vector)
        {
            m_vector = new T[m_capacity];

            for(size_t index{0}; index < m_length; ++index)
            {
                m_vector[index] = vec.m_vector[index];
            }
        }
        else
        {
            m_vector = nullptr;
        }

        return *this;
    }

    My_vector& operator=(const std::initializer_list<T> &list)
    {
        if(list.size() != m_capacity)
        {
            m_length = list.size();
            m_capacity = list.size();

            delete[] m_vector;
            m_vector = new T[m_capacity];
        }

        size_t index{0};

        for(const auto &element: list)
        {
            m_vector[index] = element;
            ++index;
        }
    }

    T& operator[](size_t index)
    {
        return m_vector[index];
    }

    const T& operator[](size_t index) const
    {
        return m_vector[index];
    }

    size_t size() const
    {
        return m_length;
    }

    size_t capacity() const
    {
        return m_capacity;
    }

    bool empty() const
    {
        return !(m_length);
    }

    void clear()
    {
        m_length = 0;
    }

    void resize(size_t length)
    {
        if(m_vector)
        {
            if(length <= m_length)
            {
                m_length = length;
            }
            else
            {
                size_t old_length {m_length};
                m_length = length;
                m_capacity = length;

                T *time_vector = new T[m_capacity];

                for(size_t index{0}; index < old_length; ++index)
                {
                    time_vector[index] = m_vector[index];
                }

                delete[] m_vector;
                m_vector = time_vector;

                time_vector = nullptr;
            }
        }
        else
        {
            m_length = length;
            m_capacity = length;
            m_vector = new T[m_capacity];
        }
    }

    void pop_back()
    {
        if(m_length > 0)
        {
            --m_length;
        }
    }

    void push_back(const T &elm)
    {
        bool flag_m_vector{false};
        size_t old_length{m_length};

        if(m_length < m_capacity)
        {
            ++m_length;
        }
        else
        {
            if(!m_length)
            {
                ++m_capacity;
                flag_m_vector = true;
            }
            else
            {
                m_capacity *= 2;
                flag_m_vector = true;
            }

            ++m_length;
        }

        if(flag_m_vector)
        {
            T *time_vector = new T[m_capacity];
            for(size_t index{0}; index < old_length; ++index)
            {
                time_vector[index] = m_vector[index];
            }

            delete[] m_vector;
            m_vector = time_vector;
            time_vector = nullptr;
        }

        m_vector[m_length - 1] = elm;
    }

    T* begin()
    {
        return &m_vector[0];
    }

    const T* begin() const
    {
        return &m_vector[0];
    }

    T* end()
    {
        return &m_vector[m_length];
    }

    const T* end() const
    {
        return &m_vector[m_length];
    }

    T& at(size_t index)
    {
        if(index < 0 || index > m_length)
        {
            throw std::out_of_range("Index outside the range");
        }

        return m_vector[index];
    }

    const T& at(size_t index) const
    {
        if(index < 0 || index > m_length)
        {
            throw std::out_of_range("Index outside the range");
        }

        return m_vector[index];
    }
};
