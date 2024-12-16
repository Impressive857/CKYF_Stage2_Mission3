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
		"1.����ĳ�������Ϣ\n"
		"2.������\n"
		"3.�޸������Ϣ\n"
		"4.ɾ����\n"
		"5.���ص����˵�\n"
		"\n"
		"����ѡ��";
	const char* editBookText_ =
		"1.�޸�ISBN��\n"
		"2.�޸�����\n"
		"3.�޸�����\n"
		"4.�޸ĳ�����\n"
		"5.�޸Ľ�������\n"
		"6.�޸Ŀ����\n"
		"7.�޸����ۼ�\n"
		"8.�޸�������\n"
		"9.�˳��޸�\n"
		"\n"
		"����ѡ��"
		;
};

#endif //!_MANAGER_MODE_H_