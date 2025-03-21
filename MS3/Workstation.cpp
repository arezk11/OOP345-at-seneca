// Name:Ali Rezk
// Seneca Student ID:105593222
// Seneca email:arezk1@myseneca.ca
// Date of completion:12-2-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"
using namespace std;
namespace sdds
{
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty())
        {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder() {
        
        bool move = false;

        //check if there are orders in the queue
        if (!m_orders.empty()) {
            if (m_orders.front().isItemFilled(getItemName())) {
                //if there is a next station then move the order to that station
                if (m_pNextStation) {
                    *m_pNextStation += std::move(m_orders.front());
                }
                //if there is no next station then check if the order is filled or incomplete and then move 
                else if (!m_orders.front().isOrderFilled()) {
                    g_incomplete.push_back(std::move(m_orders.front()));
                }
                else {
                    g_completed.push_back(std::move(m_orders.front()));
                }                
                m_orders.pop_front();
                move = true;
            }
            else if (this->getQuantity() <= 0) {
                //if there is a next station then move the order to that station
                if (m_pNextStation) {
                    *m_pNextStation += std::move(m_orders.front());
                }
                //if there is no next station then move the order to the incomplete queue
                else {
                    g_incomplete.push_back(std::move(m_orders.front()));
                }
                m_orders.pop_front();
                move = true;
            }
        }
        return move;
    }

    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const {

        os << this->getItemName() << " --> ";
        if (m_pNextStation) {
            os << m_pNextStation->getItemName();
        }
        else 
        {
                os << "End of Line";
        } 
        os << std::endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(move(newOrder));
        return *this;
    }
}
