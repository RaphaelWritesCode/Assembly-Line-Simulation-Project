// Name: Raphael Antioquia
// Seneca Student ID: 031379126
// Seneca email: rtantioquia@myseneca.ca
// Date of completion: Dec 2, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <vector>
#include <iomanip>
#include "CustomerOrder.h"


namespace sdds {

	size_t CustomerOrder::m_widthField = 1;

	CustomerOrder::CustomerOrder() {
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder(const std::string& record) {
		static Utilities utilObj;
		size_t next_pos = 0;
		bool more = true;

		try {
			m_name = utilObj.extractToken(record, next_pos, more);
			m_product = utilObj.extractToken(record, next_pos, more);

			std::vector<std::string> items;
			while (more) {
				std::string itemName = utilObj.extractToken(record, next_pos, more);
				if (!itemName.empty()) {
					items.push_back(itemName);
				}
			}

			m_cntItem = items.size();
			m_lstItem = new Item * [m_cntItem];

			for (size_t i = 0; i < m_cntItem; i++) {
				m_lstItem[i] = new Item(items[i]);
			}

			if (this->m_widthField < utilObj.getFieldWidth()) {
				this->m_widthField = utilObj.getFieldWidth();
			}
		}
		catch (...) {
			throw;
		}
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
		: m_name(std::move(other.m_name)),
		m_product(std::move(other.m_product)),
		m_cntItem(other.m_cntItem),
		m_lstItem(other.m_lstItem) {
		
		other.m_cntItem = 0;
		other.m_lstItem = nullptr;
	}


	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			m_name = std::move(src.m_name);
			m_product = std::move(src.m_product);
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;

			src.m_cntItem = 0;
			src.m_lstItem = nullptr;
		}

		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	
	bool CustomerOrder::isOrderFilled() const {
		bool allOrdersFilled = true;

		for (size_t i = 0; i < m_cntItem && allOrdersFilled; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				allOrdersFilled = false;
			}
		}

		return allOrdersFilled;
	}


	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool allItemsFilled = true;

		for (size_t i = 0; i < m_cntItem && allItemsFilled; i++) {
			if (itemName == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled) { // name match and NOT filled
				allItemsFilled = false;
			}
		}

		return allItemsFilled;
	}

	
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool oneItemFilled = false;

		// iterate through each item in the order
		for (size_t i = 0; i < m_cntItem && !oneItemFilled; i++) {

			// check if the item in the order matches the station's item
			if (m_lstItem[i]->m_itemName == station.getItemName()) {

				// check if the item is not already filled
				if (!m_lstItem[i]->m_isFilled) {

					// check if the station has at least one item in inventory
					if (station.getQuantity() > 0) {

						// fill the item
						station.updateQuantity(); // decrease station's inventory
						m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
						m_lstItem[i]->m_isFilled = true;

						os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
						oneItemFilled = true;
					}
					else {
						// print unable to fill message
						os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
					}
				}
			}
		}
	}



	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std:: right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
				<< std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED\n";
			}
			else {
				os << "TO BE FILLED\n";
			}
		}
	}
}