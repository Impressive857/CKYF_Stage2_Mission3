#ifndef _SALE_MODE_H_
#define _SALE_MODE_H_

#include "Mode.h"

#include <chrono>

#include "DataManager.h"

class SaleMode : public Mode
{
public:
	enum class MenuMode {
		VIEW_SHOPPING_LIST = 1,
		ADD_BOOK_TO_SHOPPING_LIST = 2,
		EDIT_BOOK_IN_SHOPPING_LIST = 3,
		REMOVE_BOOK_FROM_LIST = 4,
		RETURN_TO_MAIN_MENU  = 5,
		MIN = VIEW_SHOPPING_LIST,
		MAX = RETURN_TO_MAIN_MENU
	};
	SaleMode() = default;
	~SaleMode() override = default;
	void Init() override;
	void OnEnter() override;
	void OnShow() override;
	void OnExit() override;
	void PrintList() const;
	void ViewShoppingList() const;
	void AddBookToShoppingList();
	void EditBookInShoppingList();
	void RemoveBookFromList();
private:
	const char* menuText_ =
		"		CKYFͼ�����ϵͳ\n"
		"		  ǰ̨����ģ��\n"
		"\n"
		"1.�鿴���ﳵ\n"
		"2.����鵽���ﳵ\n"
		"3.�޸Ĺ��ﳵ\n"
		"4.�ӹ��ﳵ�Ƴ���\n"
		"5.�������˵�\n"
		"\n"
		"����ѡ��"
		;
};

#endif //!_SALE_MODE_H_