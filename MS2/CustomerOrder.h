#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <iostream>
#include "Station.h"

namespace sdds
{
    struct Item {

        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string& src) : m_itemName(src) {};
    };

    class CustomerOrder {

       //the name of the customer(e.g., John, Sara, etc)
        std::string m_name = ""; 

        //the name of the product being assembled
        std::string m_product = ""; 

       //a count of the number of items in the customer's order
        size_t m_cntItem = 0;

        // a dynamically allocated array of pointers.
        //Each element of the array points to a dynamically
        //allocated object of type Item
        Item** m_lstItem = nullptr; 

        // the maximum width of a field, used for display purposes
        static size_t m_widthField;        

    public:

        //default constructor
        CustomerOrder() {};

        //a custom 1-argument constructor that takes a reference to an unmodifiable string.
        CustomerOrder(const std::string& src);

       //The copy constructor should throw an exception if called and the copy operator= should be deleted.
        CustomerOrder(const CustomerOrder& src);

        //copy assignment
        CustomerOrder& operator=(const CustomerOrder& src) = delete;

        //a move constructor. This constructor should "promise" that it doesn't throw exceptions. 
        CustomerOrder(CustomerOrder&& src) noexcept;

        //a move assignment operator. This operator should "promise" that it doesn't throw exceptions
        CustomerOrder& operator=(CustomerOrder&& src) noexcept;

        //destructor
        ~CustomerOrder();

        //returns true if all the items in the order have been filled; false otherwise
        bool isOrderFilled() const;

        //returns true if all items specified by itemName have been filled.
        bool isItemFilled(const std::string& itemName) const;

        // this modifier fills one item in the current order that the Station specified in the first parameter handles.
        void fillItem(Station& station, std::ostream& os);

        void display(std::ostream& os) const;
    };
}
#endif 