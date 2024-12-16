#include "ManagerMode.h"

ManagerMode::ManagerMode()
{
	memset(this->isbnBuffer_, 0, sizeof(this->isbnBuffer_));
	memset(this->bookTitleBuffer_, 0, sizeof(this->bookTitleBuffer_));
	memset(this->authorBuffer_, 0, sizeof(this->authorBuffer_));
	memset(this->publisherBuffer_, 0, sizeof(this->publisherBuffer_));
}

void ManagerMode::Init()
{
}

void ManagerMode::OnEnter()
{
}

void ManagerMode::OnShow()
{
	while (true) {
		system("clear");
		std::cout << 
			"		CKYF图书管理系统\n"
			"		  书库管理模块\n";
		mode_ = GetMode(menuText_, static_cast<int>(MenuMode::MIN), static_cast<int>(MenuMode::MAX));
		switch (static_cast<MenuMode>(mode_)) {
		case MenuMode::LOOK_UP_BOOK: {
			this->LookUpBook();
			break;
		}
		case MenuMode::ADD_BOOK: {
			this->AddBook();
			break;
		}
		case MenuMode::EDIT_BOOK: {
			this->EditBook();
			break;
		}
		case MenuMode::REMOVE_BOOK: {
			this->RemoveBook();
			break;
		}
		case MenuMode::RETURN_TO_MAIN_MENU: {
			return;
		}
		}
	}
}

void ManagerMode::OnExit()
{
	
}

void ManagerMode::LookUpBook()
{
	if (DataManager::GetIntance()->GetInventoryList().IsEmpty()) {
		std::cout << "书库为空，无法查找！\n";
		system("pause");
		return;
	}
	GetData("请输入要查找的书名：（输入~退出）", this->bookTitleBuffer_);
	if (!strncmp("~", this->bookTitleBuffer_, sizeof(this->bookTitleBuffer_ - 1))) {
		return;
	}
	auto book = DataManager::GetIntance()->GetInventoryList().GetBookByBookTitle(this->bookTitleBuffer_);
	if (!book) {
		std::cout << "书库中未查询到此书\n";
	}
	else {
		(*book)->PrintInfo();
	}
	system("pause");
}

void ManagerMode::AddBook()
{
	while (true) {
		GetData("请输入新书的ISBN号：", this->isbnBuffer_);
		if (DataManager::GetIntance()->GetInventoryList().IsbnIsExist(this->isbnBuffer_)) {
			std::cout << "此ISBN号已存在，请重新输入！\n";
			continue;
		}
		break;
	}
	while (true) {
		GetData("请输入新书的名称：", this->bookTitleBuffer_);
		if (!strncmp("~", this->bookTitleBuffer_, sizeof(this->bookTitleBuffer_ - 1))) {
			std::cout << "此书名不合法！请重新输入！\n";
			continue;
		}
		if (DataManager::GetIntance()->GetInventoryList().BookTitleIsExist(this->bookTitleBuffer_)) {
			std::cout << "此书名已存在，请重新输入！\n";
			continue;
		}
		break;
	}
	GetData("请输入新书的作者：", this->authorBuffer_);
	GetData("请输入新书的出版社：", this->publisherBuffer_);
	std::tm date{};
	GetDate("请输入年月日（请用-分隔）：", date);
	int qtyOnhand;
	GetData("请输入新书的库存量：", qtyOnhand);
	double retail;
	GetData("请输入新书的零售价：", retail);
	double wholesale;
	GetData("请输入新书的批发价：", wholesale);
	DataManager::GetIntance()->GetInventoryList().AddBook(this->isbnBuffer_, this->bookTitleBuffer_, this->authorBuffer_, this->publisherBuffer_, date, qtyOnhand, retail, wholesale);
	std::cout << "添加成功！\n";
	system("pause");
}

void ManagerMode::EditBook()
{
	if (DataManager::GetIntance()->GetInventoryList().IsEmpty()) {
		std::cout << "书库为空，无法修改！\n";
		system("pause");
		return;
	}
	GetData("请输入要修改的书名：（输入~退出）", this->bookTitleBuffer_);
	if (!strncmp("~", this->bookTitleBuffer_, sizeof(this->bookTitleBuffer_ - 1))) {
		return;
	}
	auto book = DataManager::GetIntance()->GetInventoryList().GetBookByBookTitle(this->bookTitleBuffer_);
	if (!book) {
		std::cout << "书库中未查询到此书\n";
		system("pause");
		return;
	}
	auto bookInShoppingList = DataManager::GetIntance()->GetShoppingTrolleyList().GetBookByBookTitle(this->bookTitleBuffer_);
	std::tm newDateAdded{};
	int newQtyOnhand = 0;
	double newRetail = 0.0;
	double newWholesale = 0.0;
	while (true) {
		system("clear");
		std::cout <<
			"		CKYF图书管理系统\n"
			"			修改书\n";
		(*book)->PrintInfo();
		std::cout << "\n";
		mode_ = GetMode(editBookText_, static_cast<int>(EditMode::MIN), static_cast<int>(EditMode::MAX));
		switch (static_cast<EditMode>(mode_)) {
		case EditMode::EDIT_ISBN: {
			while (true) {
				GetData("请输入新的ISBN号：", this->isbnBuffer_);
				if (DataManager::GetIntance()->GetInventoryList().IsbnIsExist(this->isbnBuffer_)) {
					std::cout << "此ISBN号已经存在！\n";
					continue;
				}
				break;
			}
			(*book)->SetIsbn(this->isbnBuffer_);
			if (bookInShoppingList) {
				(*bookInShoppingList)->SetIsbn(this->isbnBuffer_);
			}
			break;
		}
		case EditMode::EDIT_TITLE: {
			while (true) {
				GetData("请输入新的书名：", this->bookTitleBuffer_);
				if (!strncmp("~", this->bookTitleBuffer_, sizeof(this->bookTitleBuffer_ - 1))) {
					std::cout << "此书名不合法！请重新输入！\n";
					continue;
				}
				if (DataManager::GetIntance()->GetInventoryList().BookTitleIsExist(this->bookTitleBuffer_)) {
					std::cout << "此书名已经存在！\n";
					continue;
				}
				break;
			}
			(*book)->SetBookTitle(this->bookTitleBuffer_);
			if (bookInShoppingList) {
				(*bookInShoppingList)->SetBookTitle(this->bookTitleBuffer_);
			}
			break;
		}
		case EditMode::EDIT_AUTHOR: {
			GetData("请输入新的作者：", this->authorBuffer_);
			(*book)->SetAuthor(this->authorBuffer_);
			break;
		}
		case EditMode::EDIT_PUBLISHER: {
			GetData("请输入新的出版社：", this->publisherBuffer_);
			(*book)->SetPubliser(this->publisherBuffer_);
			break;
		}
		case EditMode::EDIT_DATE_ADDED: {
			GetDate("请输入新的进书日期：", newDateAdded);
			(*book)->SetDateAdded(newDateAdded);
			break;
		}
		case EditMode::EDIT_QTY: {
			GetData("请输入新的库存量：", newQtyOnhand);
			(*book)->SetQtyOnHand(newQtyOnhand);
			if (bookInShoppingList && (newQtyOnhand < (*bookInShoppingList)->QtyOnHand())) {
				std::cout << "新的库存量小于购物车中数量，购物车中数量已经调整！\n";
				(*bookInShoppingList)->SetQtyOnHand(newQtyOnhand);
			}
			break;
		}
		case EditMode::EDIT_RETAIL: {
			GetData("请输入新的零售价：", newRetail);
			(*book)->SetRetail(newRetail);
			if (bookInShoppingList) {
				(*bookInShoppingList)->SetRetail(newRetail);
			}
			break;
		}
		case EditMode::EDIT_WHOLESALE: {
			GetData("请输入新的批发价：", newWholesale);
			(*book)->SetWholesale(newWholesale);
			break;
		}
		case EditMode::EXIT: {
			return;
		}
		}
	}
}

void ManagerMode::RemoveBook()
{
	if (DataManager::GetIntance()->GetInventoryList().IsEmpty()) {
		std::cout << "书库为空，无法删除！\n";
		system("pause");
		return;
	}
	GetData("请输入要删除的书名：（输入~退出）", this->bookTitleBuffer_);
	if (!strncmp("~", this->bookTitleBuffer_, sizeof(this->bookTitleBuffer_ - 1))) {
		return;
	}
	auto book = DataManager::GetIntance()->GetInventoryList().GetBookByBookTitle(this->bookTitleBuffer_);
	if (!book) {
		std::cout << "书库中未查询到此书\n";
	}
	else {
		DataManager::GetIntance()->GetInventoryList().RemoveBook((*book));
		auto bookInShoppingList = DataManager::GetIntance()->GetShoppingTrolleyList().GetBookByBookTitle(this->bookTitleBuffer_);
		if (bookInShoppingList) {
			DataManager::GetIntance()->GetShoppingTrolleyList().RemoveBook(*bookInShoppingList);
		}
		std::cout << "删除成功!";
	}
	system("pause");
}