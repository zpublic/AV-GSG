#pragma once

template<typename T>
class Singleton
{
protected:
    static T* m_pInst;

    Singleton() {}
    virtual ~Singleton() {}

public:
    static T* SingletonCreate()
    {
        if (m_pInst == NULL)
        {
            m_pInst = new T();
        }
        return m_pInst;
    }

	static void SingletonDestroy()
    {
        if (m_pInst != NULL)
        {
            delete m_pInst;
        }
        m_pInst = NULL;
    }

    virtual bool SingletonInitialize() = 0;

private:
    Singleton(const Singleton &s);
    Singleton& operator=(const Singleton &s);
};
