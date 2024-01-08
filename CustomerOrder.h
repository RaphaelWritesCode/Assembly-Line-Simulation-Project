// Name: Raphael Antioquia
// Seneca Student ID: 031379126
// Seneca email: rtantioquia@myseneca.ca
// Date of completion: Dec 2, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include "Utilities.h"
#include "Station.h"

namespace sdds {
	class CustomerOrder {
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};

	private:
		std::string m_name; // the name of the customer (e.g., John, Sara, etc)
		std::string m_product; // the name of the product being assembled (e.g., Desktop, Laptop, etc)
		size_t m_cntItem; // a count of the number of items in the customer's order
		Item** m_lstItem; // a dynamically allocated array of pointers. Each element of the array points to a dynamically allocated object of type Item (see below). This is the resource that your class must manage.
		static size_t m_widthField; // the maximum width of a field, used for display purposes

	public:
		CustomerOrder();

		CustomerOrder(const std::string&);

		// no copy operations allowed
		CustomerOrder(const CustomerOrder&) {
			throw std::runtime_error("Copy constructor is not allowed!");
		};

		CustomerOrder& operator=(const CustomerOrder&) = delete;

		CustomerOrder(CustomerOrder&&) noexcept;

		CustomerOrder& operator=(CustomerOrder&&) noexcept;

		~CustomerOrder();

		// returns true if all the items in the order have been filled; false otherwise
		bool isOrderFilled() const;

		// returns true if all items specified by itemName have been filled. 
		// If the item doesn't exist in the order, this query returns true.
		bool isItemFilled(const std::string& itemName) const;

		//  this modifier fills one item in the current order that the Station specified in the first parameter handles.
		void fillItem(Station& station, std::ostream& os);

		// this query displays the state of the current object in the format
		void display(std::ostream& os) const;
	};
}

#endif // !SDDS_CUSTOMERORDER_H

