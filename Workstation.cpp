// Name: Raphael Antioquia
// Seneca Student ID: 031379126
// Seneca email: rtantioquia@myseneca.ca
// Date of completion: Dec 2, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

namespace sdds {

	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;


	Workstation::Workstation(const std::string& src) : Station(src), m_pNextStation(nullptr) {};


	Workstation::~Workstation() {}

	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}



	bool Workstation::attemptToMoveOrder() {
		bool orderMoved = false;

		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
				// check if the order can be moved to the next station
				if (m_pNextStation) {
					m_pNextStation->m_orders.push_back(std::move(m_orders.front()));
				}
				else {
					// if there is no next station, move it to g_completed or g_incomplete
					if (m_orders.front().isOrderFilled()) {
						g_completed.push_back(std::move(m_orders.front()));
					}
					else {
						g_incomplete.push_back(std::move(m_orders.front()));
					}
				}
				// remove the the 1st order
				m_orders.pop_front();
				orderMoved = true;
			}
		}

		return orderMoved;
	}

	void Workstation::setNextStation(Workstation* station) {
		if (station) {
			m_pNextStation = station;
		}
	}

	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const {
		os << getItemName();
		if (m_pNextStation) { // if next station exsits
			os << " --> " << m_pNextStation->getItemName();
		}
		else {
			os << " --> End of Line";
		}
		os << '\n';
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));

		return *this;
	}
}