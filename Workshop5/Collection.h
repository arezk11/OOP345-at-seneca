/*
*****************************************************************************
                        Workshop 5 - Part 2
Full Name  : Ali Rezk
Student ID#: 105593222
Email      : arezk1@myseneca.ca
Section    : ZBB
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/
#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>
#include <string>


namespace sdds
{
    template <typename T>
    class Collection
    {
        T* m_item = nullptr;
        std::string m_name = "";
        size_t arrSize = 0u;

        void (*m_observer) (const Collection<T>&, const T&) { nullptr };

    public:
        Collection(const std::string& name) : m_name(name) {}

        Collection(const Collection&) = delete;

        Collection& operator=(const Collection&) = delete;

        ~Collection() 
        {
            if (m_item) 
            {
                delete[] m_item;
                m_item = nullptr;
            }
        }

        const std::string& name() const 
        {
            return m_name;
        }

        size_t size() const 
        {
            return arrSize;
        }

        void setObserver(void (*observer)(const Collection<T>&, const T&)) 
        {
            m_observer = observer;
        }

        Collection<T>& operator+=(const T& item) 
        {
            bool isValid = false;

            for (auto i = 0u; i < arrSize; ++i) 
            {
                if (m_item[i].title() == item.title())
                    isValid = true;
            }

            if (!isValid)
            {
                if (arrSize == 0u) 
                {
                    m_item = new T[++arrSize];
                    m_item[0] = item;
                }
                else
                {
                    //create a temp array to hold current items
                    T* temp = new T[arrSize];

                    for (auto i = 0u; i < arrSize; ++i)
                    {
                        //copy existing items to the temp array
                        temp[i] = m_item[i];
                    }

                    delete[] m_item;
                    m_item = nullptr;

                    
                    m_item = new T[++arrSize];

                    for (auto i = 0u; i < arrSize - 1u; ++i) 
                    {
                        //copy items from the temp array back to the new array
                        m_item[i] = temp[i];
                    }
                    //set the new item
                    m_item[arrSize - 1u] = item;

                    delete[] temp;
                    temp = nullptr;

                    if (m_observer)
                    {
                        m_observer(*this, item);
                    }
                }
            }

            return *this;
        }

        T& operator[](size_t idx) const 
        {
            if (idx >= size()) 
            {
                std::string err = "Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(size()) + "] items.";
                throw std::out_of_range(err);
            }

            return m_item[idx];
        }

        T* operator[](const std::string& title) const 
        {
            bool isFound{ false };
            size_t index{ 0u };

            for (auto i = 0u; i < arrSize && !isFound; ++i)
            {
                if (m_item[i].title() == title) 
                {
                    //record the index if the item is found
                    index = i;
                    isFound = true;
                }
            }

            if (!isFound)
            { 
                return nullptr; 
            }
            //return a pointer to the found item
            return &m_item[index];
        }
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Collection<T>& src)
    {
        for (auto i = 0u; i < src.size(); ++i)
        {
            os << src[i];
        }
        return os;
    }
}
#endif 