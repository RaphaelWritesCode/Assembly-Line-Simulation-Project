// Name: Raphael Antioquia
// Seneca Student ID: 031379126
// Seneca email: rtantioquia@myseneca.ca
// Date of completion: Dec 2, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Utilities.h"

namespace sdds {
	char Utilities::m_delimiter = ',';

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        std::string token;

        // if there are more tokens to extract and the next position is within the string
        if (more && next_pos < str.length()) {
            size_t end_pos = str.find(m_delimiter, next_pos);

            // check if this is the last token
            if (end_pos == std::string::npos) {
                more = false;
                end_pos = str.length();
            }
            else {
                more = true;
            }

            // check if delimiter is at the next_pos
            if (next_pos == end_pos) {
                more = false;
                throw std::invalid_argument("Delimiter found at next_pos");
            }

            // extract the token
            token = str.substr(next_pos, end_pos - next_pos);
            next_pos = end_pos + 1; // update next_pos for the next call

            // trim the token and update m_widthField if necessary
            token = trim(token); 
            if (m_widthField < token.length()) {
                m_widthField = token.length();
            }
        }
        else {
            more = false;
        }

        return token;
    }


    
    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }


}