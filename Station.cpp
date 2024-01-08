// Name: Raphael Antioquia
// Seneca Student ID: 031379126
// Seneca email: rtantioquia@myseneca.ca
// Date of completion: Dec 2, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"


namespace sdds {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string record) {
		static Utilities utilObj; // local utilities object
		size_t next_pos = 0;
		bool more = true;

		try {
			s_itemName = utilObj.extractToken(record, next_pos, more);
			// update station m_widthField to the size of name
			if (Station::m_widthField < s_itemName.length()) {
				Station::m_widthField = s_itemName.length();
			}

			if (more) {
				s_nextSerialNum = std::stoul(utilObj.extractToken(record, next_pos, more));
			}
			if (more) {
				s_itemsInStock = std::stoul(utilObj.extractToken(record, next_pos, more));
			}
			if (more) {
				s_desc = utilObj.extractToken(record, next_pos, more);
			}

			s_id = ++id_generator;
		}
		catch (...) {
			throw;
		}
	}

	const std::string& Station::getItemName() const {
		return s_itemName;
	}

	size_t Station::getNextSerialNumber() {
		return s_nextSerialNum++;
	}

	size_t Station::getQuantity() const {
		return s_itemsInStock;
	}

	void Station::updateQuantity() {
		if (s_itemsInStock > 0) {
			s_itemsInStock--;
		}
	}

	void Station::display(std::ostream& os, bool full) const {
		os << std::right << std::setw(3) << std::setfill('0') << s_id << " | ";
		os << std::left << std::setw(Station::m_widthField) << std::setfill(' ') << s_itemName << " | ";
		os << std::setw(6) << std::setfill('0') << std::right << s_nextSerialNum << " | ";
		if (full) {
			os << std::setw(4) << std::setfill(' ') << s_itemsInStock << " | ";
			os << s_desc;
		}
		os << std::endl;
	}

}
