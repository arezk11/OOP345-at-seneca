// Name:Ali Rezk
// Seneca Student ID:105593222
// Seneca email:arezk1@myseneca.ca
// Date of completion:12-2-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <iostream>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {

       //a double ended queue with CustomerOrders
        std::deque<CustomerOrder> m_orders;     

        //a pointer to the next Workstation on the assembly line.
        Workstation* m_pNextStation{ nullptr }; 

    public:

        //one argument constructor
        Workstation(const std::string& src) : Station(src) {};
        //the object cannot be copied or moved. Make sure that this capability is deleted in your definition of the Workstation class.
        Workstation(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation& operator=(Workstation&&) = delete;


        //fills the order at the front of the queue if there are CustomerOrders in the queue
        void fill(std::ostream& os);

        //attempts to move the order order at the front of the queue to the next station in the assembly line:
        bool attemptToMoveOrder();

       //stores the address of the referenced Workstation object in the pointer to the m_pNextStation
        void setNextStation(Workstation* station);

        //returns the address of next Workstation
        Workstation* getNextStation() const;

        void display(std::ostream& os) const;

        //moves the CustomerOrder referenced in parameter newOrder to the back of the queue.
        Workstation& operator+=(CustomerOrder&& newOrder);
    };
}
#endif // !SDDS_WORKSTATION_H