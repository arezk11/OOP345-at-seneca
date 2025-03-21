// Name:Ali Rezk
// Seneca Student ID:105593222
// Seneca email:arezk1@myseneca.ca
// Date of completion:11-18-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
    size_t CustomerOrder::m_widthField = 0;

    
    CustomerOrder::CustomerOrder(const std::string& src)
        : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {

        Utilities utilityObj;

        bool validRecord = true;

        //starting posistion
        size_t position = 0;

        //extract customer name and order name 
        m_name = utilityObj.extractToken(src, position, validRecord);
        m_product = utilityObj.extractToken(src,position, validRecord);

        //count the number of items in the order
        m_cntItem = std::count(src.begin(), src.end(), utilityObj.getDelimiter()) - 1;

        //allocate memory for m_lstItem 
        if (m_cntItem > 0) 
        {
            m_lstItem = new Item * [m_cntItem];

            //populate the m_lstItem array with tem objects
            for (size_t i = 0; i < m_cntItem; ++i) 
            {
                m_lstItem[i] = new Item(utilityObj.extractToken(src, position, validRecord));
            }
        }

        //update CustomerOrder::m_widthField with the maximum width
        m_widthField = std::max(utilityObj.getFieldWidth(), m_widthField);
    }


    //a CustomerOrder object should not allow copy operations. The copy constructor should throw an exception if called
    CustomerOrder::CustomerOrder(const CustomerOrder& src) 
    {
        throw "copying operations is not allowed for CustomerOrder objects";
    }

  
    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept 
    {
        m_name = std::move(src.m_name);
        m_product = std::move(src.m_product);
        m_cntItem = src.m_cntItem;
        m_lstItem = std::move(src.m_lstItem);

        src.m_cntItem = 0;
        src.m_lstItem = nullptr;
    }


    //a move assignment operator. This operator should "promise" that it doesn't throw exceptions.
    //Use the noexcept keyword in the declaration and the definition.
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept 
    {
        if (this != &src) 
        {
            if (m_lstItem) 
            {
                for (auto i = 0u; i < m_cntItem; ++i)
                {
                   delete m_lstItem[i];
                } 

                delete[] m_lstItem;
            }

            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;
            src.m_name = "";
            src.m_product = "";
            src.m_cntItem = 0;
            src.m_lstItem = nullptr;
        }

        return *this;
    }
    //destructor
    CustomerOrder::~CustomerOrder() 
    {
        if (m_lstItem) 
        {
            for (auto i = 0u; i < m_cntItem; ++i)
            {
                delete m_lstItem[i];
            }

            delete[] m_lstItem;
            m_lstItem = nullptr;

        }
    }

    //returns true if all the items in the order have been filled; false otherwise
    bool CustomerOrder::isOrderFilled() const
    {
        bool result = true;

        for (auto i = 0u; i < m_cntItem; ++i) 
        {
            if (!m_lstItem[i]->m_isFilled) 
            {
                result = false;
            }
        }

        return result;
    }

    //returns true if all items specified by itemName have been filled. If the item doesn't exist in the order, this query returns true.
    bool CustomerOrder::isItemFilled(const std::string& itemName) const 
    {
        for (auto i = 0u; i < m_cntItem; ++i) 
        {

            if (m_lstItem[i]->m_itemName == itemName) 
            {
                return m_lstItem[i]->m_isFilled;
            }
        
        }

        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) 
    {
        //to track if an item has been filled to avoid printing the same item multiple times
        bool itemFilled = false;

        for (size_t i = 0; i < m_cntItem && !itemFilled; i++) 
        {
            //check if the item has already been filled and matches the current station
            if (!m_lstItem[i]->m_isFilled && station.getItemName() == m_lstItem[i]->m_itemName)
            {
                if (station.getQuantity() > 0) 
                {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;

                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;

                    itemFilled = true; 
                }
                else
                {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const 
    {
        os << m_name << " - " << m_product << endl;

        for (auto i = 0u; i < m_cntItem; ++i) 
        {
            os << "[" << right << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
            os << left << setw(m_widthField) << setfill(' ') << m_lstItem[i]->m_itemName;
            os << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
        }
    }
}