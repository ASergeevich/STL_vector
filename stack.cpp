#ifndef MY_STACK
#define MY_STACK

#include <iostream>

template<class S>
class Stack
{
    template<class T>
    struct Element
    {
        T m_data;
        Element *m_next;
        Element *m_previous;
        Element(const T &elm): m_data{elm}, m_next{nullptr}, m_previous{nullptr}
        {
        }
    };

    size_t m_size{0};
    Element<S> *m_head{nullptr};
    Element<S> *m_closing{nullptr};

    public:

    Stack()
    {
    }

    ~Stack()
    {
        clear();
    }

    void push_back(const S &elm)
    {
        if(isEmpty())
        {
            m_head = new Element<S>(elm);
            m_closing = m_head;
        }
        else
        {
            Element<S> *current_element = m_head;

            while(current_element->m_next != nullptr)
            {
                current_element = current_element->m_next;
            }

            current_element->m_next = new Element<S>(elm);
            m_closing = current_element->m_next;
            current_element->m_next->m_previous = current_element;

        }

        ++m_size;
    }

    void pop_back()
    {
        if(isEmpty())
        {
            return;
        }
        --m_size;

        if(m_closing == m_head)
        {
            delete m_head;
            m_closing = nullptr;
            m_head = nullptr;
            return;
        }

        Element<S> *current_element = m_closing;
        m_closing = current_element->m_previous;
        m_closing->m_next = nullptr;
        delete current_element;
    }

    void clear()
    {

        while(m_head)
        {
            Element<S> *current_element = m_head;
            m_head = current_element->m_next;
            delete current_element;
        }

    }

    void show()
    {
        if(isEmpty())
        {
            std::cout << "Zero elements\n";
            return;
        }
        else
        {
            Element<S> *current_element = m_head;
            size_t current_size = m_size;

            while(current_size--)
            {
                std::cout << current_element->m_data << ' ';
                current_element = current_element->m_next;
            }

            std::cout << '\n';
        }
    }

    bool isEmpty() const
    {
        return m_head == 0;
    }

    size_t size() const
    {
        return m_size;
    }
};

#endif
