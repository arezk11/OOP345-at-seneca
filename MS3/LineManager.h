// Name:Ali Rezk
// Seneca Student ID:105593222
// Seneca email:arezk1@myseneca.ca
// Date of completion:12-2-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <vector>
#include "Workstation.h"

namespace sdds {
    class LineManager {

        //the collection of workstations for the current assembly line.
        std::vector<Workstation*> m_activeLine;
        
        //the total number of CustomerOrder objects the total number of CustomerOrder objects
        size_t  m_cntCustomerOrder{ 0u };

        //points to the first active station on the current line
        Workstation* m_firstStation; 

    public:

        //receives the name of the file that identifies the active stations on the assembly line
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);

        //reorders the workstations present in the instance variable m_activeLine 
        //(loaded by the constructor) and stores the reordered collection in the same instance variable. 
        void reorderStations();

        //performs one iteration of operations on all of the workstations in the current assembly line
        bool run(std::ostream& os);

        void display(std::ostream& os) const;
    };
}
#endif 