// Name: Raphael Antioquia
// Seneca Student ID: 031379126
// Seneca email: rtantioquia@myseneca.ca
// Date of completion: Dec 2, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>

namespace sdds {
	class Station {
	private:
		int s_id;
		std::string s_itemName;
		std::string s_desc;
		size_t s_nextSerialNum;
		size_t s_itemsInStock;

		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string);

		// returns the name of the current Station object
		const std::string& getItemName() const;

		// returns the next serial number to be used on the assembly line and increments m_serialNumber
		size_t getNextSerialNumber();

		// returns the remaining quantity of items in the Station object
		size_t getQuantity() const;

		// subtracts 1 from the available quantity; should not drop below 0.
		void updateQuantity();

		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SDDS_STATION_H
