#ifndef _MANAGER_MODE_H_
#define _MANAGWE_MODE_H_

#include "Mode.h"

#include "DataManager.h"

class ManagerMode :public Mode
{
public:
	enum class MenuMode {
		LOOK_UP_BOOK = 1,
		ADD_BOOK = 2,
		EDIT_BOOK = 3,
		REMOVE_BOOK = 4,
		RETURN_TO_MAIN_MENU = 5,
		MIN = LOOK_UP_BOOK,
		MAX = RETURN_TO_MAIN_MENU
	};
	enum class EditMode {
		EDIT_ISBN = 1,
		EDIT_TITLE = 2,
		EDIT_AUTHOR = 3,
		EDIT_PUBLISHER = 4,
		EDIT_DATE_ADDED = 5,
		EDIT_QTY = 6,
		EDIT_RETAIL = 7,
		EDIT_WHOLESALE = 8,
		EXIT = 9,
		MIN = EDIT_ISBN,
		MAX = EXIT
	};
	ManagerMode();
	~ManagerMode() override = default;
	void Init() override;
	void OnEnter() override;
	void OnShow() override;
	void OnExit() override;
	void LookUpBook();
	void AddBook();
	void EditBook();
	void RemoveBook();
private:
	char isbnBuffer_[constant::isbnLength];
	char bookTitleBuffer_[constant::bookTitleLength];
	char authorBuffer_[constant::authorLength];
	char publisherBuffer_[constant::publisherLength];
	const char* menuText_ =
		"1.查找某本书的信息\n"
		"2.增加书\n"
		"3.修改书的信息\n"
		"4.删除书\n"
		"5.返回到主菜单\n"
		"\n"
		"输入选择：";
	const char* editBookText_ =
		"1.修改ISBN号\n"
		"2.修改书名\n"
		"3.修改作者\n"
		"4.修改出版社\n"
		"5.修改进书日期\n"
		"6.修改库存量\n"
		"7.修改零售价\n"
		"8.修改批发价\n"
		"9.退出修改\n"
		"\n"
		"输入选择："
		;
};

#endif //!_MANAGER_MODE_H_