// Name: Raphael Antioquia
// Seneca Student ID: 031379126
// Seneca email: rtantioquia@myseneca.ca
// Date of completion: Dec 2, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station {
	private:
		std::deque<CustomerOrder> m_orders; //  is a double-ended-queue with CustomerOrders entering the back and exiting the front. 
											// These are orders that have been placed on this station to receive service (or already received service).

		Workstation* m_pNextStation{}; // a pointer to the next Workstation on the assembly line.
	public:
		Workstation(const std::string& src);

		// cannot be copied or moved
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;

		~Workstation();

		// this modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing.
		void fill(std::ostream& os);

		bool attemptToMoveOrder();

		void setNextStation(Workstation* station = nullptr);

		Workstation* getNextStation() const;

		void display(std::ostream& os) const;

		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}

#endif // !SDDS_WORKSTATION_H

