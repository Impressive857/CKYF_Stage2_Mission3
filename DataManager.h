#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include <mutex>
#include <iostream>
#include <type_traits>
#include <ctime>

#include "BookDataList.h"

template<typename _Ty>
inline void GetData(const char* text, _Ty& data) {
	static_assert(!(std::is_const_v<_Ty> || std::is_rvalue_reference_v<_Ty>), "要获取的值不能为常量或者右值引用！");
	while (true) {
		std::cout << text;
		std::cin >> data;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "输入不合法，请重新输入！\n";
			continue;
		}
		break;
	}
}

inline bool IsLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

inline bool IsValidDate(int year, int month, int day) {
	if (year < 1900 || month < 1 || month > 12 || day < 1) {
		return false;
	}
	const int daysInMonth[] = { 31,28 + IsLeapYear(year), 31,30,31,30,31,31,30,31,30,31 };
	return day <= daysInMonth[month - 1];
}

enum class DateStatus {
	EARLIER_THAN = 0,
	SAME = 1,
	LATER_THAN = 2
};

inline DateStatus DateCompare(const std::tm& date1, const std::tm& date2) {
	if (date1.tm_year < date2.tm_year) return DateStatus::EARLIER_THAN;
	if (date1.tm_year > date2.tm_year) return DateStatus::LATER_THAN;

	if (date1.tm_mon < date2.tm_mon) return DateStatus::EARLIER_THAN;
	if (date1.tm_mon > date2.tm_mon) return DateStatus::LATER_THAN;

	if (date1.tm_mday < date2.tm_mday) return DateStatus::EARLIER_THAN;
	if (date1.tm_mday > date2.tm_mday) return DateStatus::LATER_THAN;

	return DateStatus::SAME;
}

inline void GetDate(const char* text, int& year, int& month, int& day) {
	std::string line;
	std::istringstream iss;
	char delimiter;
	while (true) {
		std::cout << text;
		std::cin >> line;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "输入不合法，请重新输入！\n";
			continue;
		}
		iss.clear();
		iss.str(line);
		if (!(iss >> year >> delimiter >> month >> delimiter >> day)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "输入不合法，请重新输入！\n";
			continue;
		}
		if (!IsValidDate(year, month, day)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "输入不合法，请重新输入！\n";
			continue;
		}
		break;
	}
}

inline void GetDate(const char* text, std::tm& date) {
	std::string line;
	std::istringstream iss;
	char delimiter;
	while (true) {
		std::cout << text;
		std::cin >> line;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "输入不合法，请重新输入！\n";
			continue;
		}
		iss.clear();
		iss.str(line);
		if (!(iss >> date.tm_year >> delimiter >> date.tm_mon >> delimiter >> date.tm_mday)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "输入不合法，请重新输入！\n";
			continue;
		}
		if (!IsValidDate(date.tm_year, date.tm_mon, date.tm_mday)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "输入不合法，请重新输入！\n";
			continue;
		}
		date.tm_year -= 1900;
		date.tm_mon -= 1;
		break;
	}
}

class DataManager
{
public:
	DataManager(const DataManager&) = delete;
	DataManager& operator=(const DataManager&) = delete;
	static DataManager* GetIntance();
	void DestoryInstance();
	BookDataList& GetInventoryList();
	BookDataList& GetShoppingTrolleyList();
	bool AllBookIsInShoppingList();
private:
	explicit DataManager() = default;
	~DataManager() = default;
	static DataManager* instance_;
	static std::mutex mutex_;
	BookDataList inventoryList_;
	BookDataList shoppingTrolleyList_;
};

#endif //!_DATA_MANAGER_H_