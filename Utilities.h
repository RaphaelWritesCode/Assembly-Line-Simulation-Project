// Name: Raphael Antioquia
// Seneca Student ID: 031379126
// Seneca email: rtantioquia@myseneca.ca
// Date of completion: Dec 2, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

namespace sdds {
	class Utilities {
	private:
		size_t m_widthField{ 1 }; // specifies the length of the token extracted; used for display purposes; default value is 1
		static char m_delimiter; // separates the tokens in any given std::string object. All Utilities objects in the system share the same delimiter.

		static std::string trim(const std::string& str) {
			size_t start = str.find_first_not_of(' ');
			if (start == std::string::npos) return "";
			size_t end = str.find_last_not_of(' ');
			return str.substr(start, end - start + 1);
		}

	public:
		// sets the field width of the current object to the value of parameter newWidth
		void setFieldWidth(size_t newWidth);
		
		// returns the field width of the current object
		size_t getFieldWidth() const; 

		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		// sets the delimiter for this class to the character received
		static void setDelimiter(char newDelimiter);

		// returns the delimiter for this class.
		static char getDelimiter();
	};

}

#endif // !SDDS_UTILITIES_H