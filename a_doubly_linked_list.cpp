 #ifndef MY_LIST
#define MY_LIST

#include <iostream>
#include <initializer_list>

template<class S>
class My_List
{
    template<class T>
    struct Element
    {
        T m_data;
        Element *m_next;
        Element *m_previous;

        Element(const T &data): m_data{data}, m_next{nullptr}, m_previous{nullptr}
        {
        }
    };

    size_t m_size{0};
    Element<S> *m_head{nullptr};
    Element<S> *m_closing{nullptr};

    void copy(const My_List &list)
    {
        Element<S> *current_element = list->m_head;
        size_t current_size = list.m_size();

        while(current_size--)
        {
            push_back(current_element->m_data);
            current_element = current_element->m_next;
        }
    }

    public:

    My_List()
    {
    }

    My_List(const My_List &list)
    {
        copy(list);
    }

    My_List(const std::initializer_list<S> &list)
    {
        for(const auto &element: list)
        {
            push_back(element);
        }
    }

    ~My_List()
    {
        clear();
    }

    void push_back(const S &elm)
    {
        if(isEmpty())
        {
            this->m_head = new Element<S>(elm);
            m_closing = m_head; // ? проверить
        }
        else
        {
            Element<S> *current_element = this->m_head;

            while(current_element->m_next != nullptr)
            {
                current_element = current_element->m_next;
            }

            current_element->m_next = new Element<S>(elm);
            current_element->m_next->m_previous = current_element;
            m_closing = current_element->m_next;
        }

        ++m_size;
    }

    void push_from(const S &elm)
    {
        if(isEmpty())
        {
            this->m_head = new Element<S>(elm);
            this->m_closing = m_head;
        }
        else
        {
            Element<S> *current_element = m_head;
            m_head = new Element<S>(elm);
            m_head->m_next = current_element;
            current_element->m_previous = m_head;
        }

        ++m_size;
    }

    void pop_back()
    {
        if(isEmpty())
        {
            return;
        }

        Element<S> *current_element = m_closing;

        m_closing->m_previous->m_next = nullptr;
        m_closing = current_element->m_previous;
        delete current_element;
    }

    void pop_front()
    {
        if(isEmpty())
        {
            return;
        }

        Element<S> *current_element = m_head;
        m_head = current_element->m_next;
        m_head->m_previous = nullptr;
        delete current_element;
    }

    void clear()
    {
        if(isEmpty())
        {
            return;
        }

        Element<S> *current_element{nullptr};

        while(this->m_head)
        {
            Element<S> *current_element = m_head->m_next;
            delete m_head;
            m_head = current_element;
        }
    }

    void show()
    {
        if(isEmpty())
        {
            std::cout << "Zero elements\n";
            return;
        }

        Element<S> *current_element = m_head;
        size_t current_size = m_size;

        while(current_size--)
        {
            std::cout << current_element->m_data << ' ';
            current_element = current_element->m_next;
        }

        std::cout << '\n';
    }

    void revers_show()
    {
        if(isEmpty())
        {
            std::cout << "Zero elements\n";
            return;
        }

        Element<S> *current_element = m_closing;
        size_t current_size = m_size;

        while(current_size--)
        {
            std::cout << current_element->m_data << ' ';
            current_element = current_element->m_previous;
        }

        std::cout << '\n';
    }

    My_List& operator=(const My_List &list)
    {
        if(this == &list)
        {
            return *this;
        }

        clear();
        copy(list);


        return *this;
    }

    My_List& operator=(const std::initializer_list<S> &list)
    {
        clear();

        for(const auto &element: list)
        {
            push_back(element);
        }
    }

    bool isEmpty() const
    {
        return this->m_head == 0;
    }

    size_t size() const
    {
        return m_size;
    }


};

#endif
