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
		"		CKYF图书管理系统\n"
		"		  前台销售模块\n"
		"\n"
		"1.查看购物车\n"
		"2.添加书到购物车\n"
		"3.修改购物车\n"
		"4.从购物车移除书\n"
		"5.返回主菜单\n"
		"\n"
		"输入选择："
		;
};

#endif //!_SALE_MODE_H_