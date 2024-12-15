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
		"		CKYFͼ�����ϵͳ\n"
		"			����ģ��\n"
		"\n"
		"1.����б�\n"
		"2.���ۼ��б�\n"
		"3.�������б�\n"
		"4.���������б�\n"
		"5.���ص����˵�\n"
		"\n"
		"����ѡ��";
};

#endif //!_TABLE_MODE_H_