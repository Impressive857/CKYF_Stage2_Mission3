#ifndef _TABLE_MODE_H_
#define _TABLE_MODE_H_

#include "Mode.h"

#include "DataManager.h"

class TableMode :public Mode
{
public:
	enum class MenuMode {
		SHOW_BOOK_LIST = 1,
		SHOW_RETAIL_LIST = 2,
		SHOW_WHOLESALE_LIST = 3,
		SHOW_DATE_ADDED_LIST = 4,
		RETURN_TO_MAIN_MENU = 5,
		MIN = SHOW_BOOK_LIST,
		MAX = RETURN_TO_MAIN_MENU
	};
	TableMode() = default;
	~TableMode() override = default;
	void Init() override;
	void OnEnter() override;
	void OnShow() override;
	void OnExit() override;
	void ShowBookList();
	void ShowRetailList();
	void ShowWholesaleList();
	void ShowDateAddedList();
private:
	const char* menuText_ =
		"		CKYF图书管理系统\n"
		"			报表模块\n"
		"\n"
		"1.书库列表\n"
		"2.零售价列表\n"
		"3.批发价列表\n"
		"4.进书日期列表\n"
		"5.返回到主菜单\n"
		"\n"
		"输入选择：";
};

#endif //!_TABLE_MODE_H_