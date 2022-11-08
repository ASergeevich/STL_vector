#include <iostream>
#include <initializer_list>

template<class S>
class My_list
{
    template<class T>
    struct Element
    {
        T m_data;
        Element *m_next;

        Element(const T &data): m_data{data}, m_next{nullptr}
        {
        }
    };

    Element<S> *m_first{nullptr};
    size_t m_size{0};

    void copy(const My_list &list)
    {
        Element<S> *current_element = list.m_first;
        size_t time_size{list.get_size()};

        while(time_size)
        {
            push_back(current_element->m_data);
            current_element = current_element->m_next;
            --time_size;
        }
    }

    public:

    My_list(): m_first{nullptr}, m_size{0}
    {
    }

    My_list(const My_list &list)
    {
        copy(list);
    }

    ~My_list()
    {
        clear();
    }

    void push_back(const S &elm)
    {
        if(isEmpty())
        {
            this->m_first = new Element<S>(elm);
        }
        else
        {
            Element<S> *current_element = this->m_first;

            while(current_element->m_next != nullptr)
            {
                current_element = current_element->m_next;
            }

            current_element->m_next = new Element<S>(elm);
        }

        ++m_size;
    }

    void push_front(const S &elm)
    {
        if(isEmpty())
        {
            this->m_first = new Element<S>(elm);
        }
        else
        {
            Element<S> *current_element = this->m_first;
            this->m_first = new Element<S>(elm);
            this->m_first->m_next = current_element;
        }
        ++m_size;
    }

    void clear()
    {
        if(isEmpty())
        {
            return;
        }
        else
        {
            Element<S> *current_element{nullptr};

            while(this->m_size)
            {
                current_element = this->m_first;
                this->m_first = this->m_first->m_next;
                delete current_element;
                --m_size;
            }
        }
    }

    void show()
    {
        if(isEmpty())
        {
            std::cout << 0 << '\n';
        }
        else
        {
            Element<S> *current_element = this->m_first;
            size_t time_size{m_size};

            do
            {
                std::cout << current_element->m_data << ' ';
                current_element = current_element->m_next;
                --time_size;

            } while (time_size);
        }
        std::cout << std::endl;
    }

    My_list& operator=(const My_list &list)
    {
        if(this == &list)
        {
            return *this;
        }

        clear();
        copy(list);

        return *this;
    }

    My_list& operator=(const std::initializer_list<S> &list)
    {
        clear();
  
        for(const auto &element: list)
        {
            push_back(element);
        }

        return *this;
    }

    bool isEmpty() const
    {
        return this->m_first == nullptr;
    }

    size_t get_size() const
    {
        return m_size;
    }
};
