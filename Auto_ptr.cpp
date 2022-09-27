template<class S>
class Auto_ptr
{
    S *m_ptr;

    public:

    Auto_ptr(S *ptr): m_ptr{ptr}
    {
    }

    ~Auto_ptr()
    {
        delete m_ptr;
    }

    Auto_ptr(const Auto_ptr &p) = delete;
    Auto_ptr& operator=(const Auto_ptr &p) = delete;

    Auto_ptr(Auto_ptr &&p): m_ptr{p.m_ptr}
    {
        p.m_ptr = nullptr;
    }

    Auto_ptr& operator=(Auto_ptr &&p)
    {
        if(this == &p)
        {
            return *this;
        }

        delete m_ptr;
        m_ptr = p.m_ptr;
        p.m_ptr = nullptr;

        return *this;
    }

    S* operator->() const
    {
        return m_ptr;
    }

    S& operator*() const
    {
        return *m_ptr;
    }

    operator bool()
    {
        return m_ptr != nullptr;
    }

    bool isNull() const
    {
        return !m_ptr;
    }

};
