// Name:Ali Rezk
// Seneca Student ID:105593222
// Seneca email:arezk1@myseneca.ca
// Date of completion:12-2-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include "LineManager.h"
#include "Utilities.h"
using namespace std;

namespace sdds
{


    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
        //utilities object for extracting the tokens
        Utilities utilityObj;
        
        bool validRecord = true;

        //to track the file position
        size_t position = 0;

        //to store the found next station
        std::string foundStation{};

        //to store current and next station
        std::vector<std::string> currentStation;
        std::vector<std::string> nextStation;

     
        std::ifstream iFile(file);
        if (!iFile)
        {
            throw "Sorry, unable to open the file";
        }
        std::string line{};
       
        size_t startPos = position;

        //read each line from the file
        while (std::getline(iFile, line)) {

            //reset the position for each line
            position = startPos;

            //temp strings to store current and next station
            std::string tempCurrStation{}, tempNextStation{};
            tempCurrStation = utilityObj.extractToken(line, position, validRecord);

            if (!(position == startPos)) {
                tempNextStation = utilityObj.extractToken(line, position, validRecord);
                currentStation.push_back(tempCurrStation);
                nextStation.push_back(tempNextStation);
            }

            //find the current station in the collection
            auto currStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                return station->getItemName() == tempCurrStation;});

            //add the current station to the active line
            m_activeLine.push_back(*currStation);

            if (tempNextStation.length() > 0)
            {
                //find the next station in the collection
                auto nextStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                    return station->getItemName() == tempNextStation;});

                (*currStation)->setNextStation(*nextStation);
            }
        }
        iFile.close();

        std::for_each(currentStation.begin(), currentStation.end(), [&](std::string station) {

            bool found = false;

            std::for_each(nextStation.begin(), nextStation.end(), [&](std::string nStation) {
                if (station == nStation) 
                {
                    found = true;
                }
            });

            //if the current station is not found in nextStation then assign it to foundStation
            if (!found) 
            {
                foundStation = station;
            }
        });

        auto firstStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
            return station->getItemName() == foundStation;
        });

        m_firstStation = *firstStation;
        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations()
    {
        Workstation* currentWstaion = m_firstStation;
        vector<Workstation*>  activeLine;

        while (currentWstaion) 
        {
            activeLine.push_back(currentWstaion);
            currentWstaion = currentWstaion->getNextStation();
        }

        m_activeLine = activeLine;
    }

    bool LineManager::run(std::ostream& os) {

        //counter to keep track of the current iteration
        static size_t count = 0u;

        os << "Line Manager Iteration: " << ++count << std::endl;
        //if there are pending move the front order to the first station in the line
        if (!g_pending.empty()){
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        //for each station on the line, execute one fill operation
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto& i) { i->fill(os); });

        //for each station on the line, attempt to move an order down the line
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto& i) { i->attemptToMoveOrder(); });

        return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
    }

    void LineManager::display(std::ostream& os) const
    {
        for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* src) { src->display(os);});
    }
}