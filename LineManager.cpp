// Name: Raphael Antioquia
// Seneca Student ID: 031379126
// Seneca email: rtantioquia@myseneca.ca
// Date of completion: Dec 2, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include "LineManager.h"

namespace sdds {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) : m_cntCustomerOrder(0), m_firstStation(nullptr) {
        std::ifstream f(file);
        if (!f.is_open()) {
            throw std::runtime_error("Unable to open file: " + file);
        }

        std::string line;
        std::vector<std::string> nextStations; // track all 'next' stations
        while (getline(f, line)) {
            size_t next_pos = 0;
            bool more = true;
            Utilities util;

            std::string current = util.extractToken(line, next_pos, more);
            std::string next = more ? util.extractToken(line, next_pos, more) : ""; // if more is false, it means there is no next station

            // find current station in the stations param
            auto currentStn = std::find_if(stations.begin(), stations.end(),
                [&current](const Workstation* ws) { return ws->getItemName() == current; });

            // if current station isnt the last station, we can find the next station
            if (currentStn != stations.end()) {
                Workstation* currentWs = *currentStn;

                if (!next.empty()) {

                    // find next station in the stations param
                    auto nextStn = std::find_if(stations.begin(), stations.end(),
                        [&next](const Workstation* ws) { return ws->getItemName() == next; });

                    if (nextStn != stations.end()) {
                        // set current station's next station
                        currentWs->setNextStation(*nextStn);
                        nextStations.push_back(next); // add next station string to next stations vector to use later to find the first station
                    }
                }

                // add current station to m_activeLine if it isn't already in it
                if (std::find(m_activeLine.begin(), m_activeLine.end(), currentWs) == m_activeLine.end()) {
                    m_activeLine.push_back(currentWs);
                }
            }
        }

        // find the first station
        // if the station's name is not found in nextStations, it means that this station doesn't have a "next" station, making it the first station in the assembly line or the last station
        auto firstStn = std::find_if(stations.begin(), stations.end(),
            [&nextStations](const Workstation* station) {
                return std::find(nextStations.begin(), nextStations.end(), station->getItemName()) == nextStations.end();
            });

        // assign first station if it's not the last station
        if (firstStn != stations.end()) {
            m_firstStation = *firstStn;
        }

        m_cntCustomerOrder = g_pending.size();
    }



    void LineManager::reorderStations() {
        std::vector<Workstation*> reordered;
        Workstation* currentStation = m_firstStation;

        while (currentStation != nullptr) {
            reordered.push_back(currentStation);
            currentStation = currentStation->getNextStation();
        }

        m_activeLine = std::move(reordered);
    }


bool LineManager::run(std::ostream& os) {
    static size_t iteration = 0;
    iteration++;
    os << "Line Manager Iteration: " << iteration << std::endl;

    // move one order from g_pending to m_firstStation
    if (!g_pending.empty()) {
        *m_firstStation += std::move(g_pending.front());
        g_pending.pop_front();
    }

    // fill 1st orders from each station in the line
    for (auto& station : m_activeLine) {
        station->fill(os);
    }

    // attempt to move orders down the line for each station
    for (auto& station : m_activeLine) {
        station->attemptToMoveOrder();
    }

    // Check if all customer orders have been filled or cannot be filled
    bool allOrdersFilled = g_incomplete.size() + g_completed.size() == m_cntCustomerOrder;

    return allOrdersFilled;
}





    void LineManager::display(std::ostream& os) const {
        for (const auto& station : m_activeLine) {
            station->display(os);
        }
    }



}