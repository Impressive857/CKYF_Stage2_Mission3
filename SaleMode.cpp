#include "SaleMode.h"

void SaleMode::Init()
{
}

void SaleMode::OnEnter()
{
}

void SaleMode::OnShow()
{
	while (true) {
		system("clear");
		mode_ = GetMode(menuText_, static_cast<int>(MenuMode::MIN), static_cast<int>(MenuMode::MAX));
		switch (static_cast<MenuMode>(mode_)) {
		case MenuMode::VIEW_SHOPPING_LIST: {
			this->ViewShoppingList();
			break;
		}
		case MenuMode::ADD_BOOK_TO_SHOPPING_LIST: {
			this->AddBookToShoppingList();
			break;
		}
		case MenuMode::EDIT_BOOK_IN_SHOPPING_LIST: {
			this->EditBookInShoppingList();
			break;
		}
		case MenuMode::REMOVE_BOOK_FROM_LIST: {
			this->RemoveBookFromList();
			break;
		}
		case MenuMode::RETURN_TO_MAIN_MENU: {
			return;
		}
		}
	}
}

void SaleMode::OnExit()
{
}

void SaleMode::PrintList() const
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm* tm = std::localtime(&now);
	std::ostringstream oss;
	oss << std::left
		<< std::setw(constant::intMaxLength) << "数量"
		<< std::setw(constant::isbnLength) << "ISBN号"
		<< std::setw(constant::bookTitleLength) << "书名"
		<< std::setw(constant::doubleMaxLength + 4) << "单价"
		<< std::setw(constant::doubleMaxLength + 4) << "金额"
		<< "\n";
	std::cout <<
		"日期：" << (tm->tm_year + 1900) << "年" << (tm->tm_mon + 1) << "月" << (tm->tm_mday) << "日\n"
		<< oss.str();
	DataManager::GetIntance()->GetShoppingTrolleyList().ForEach([&](std::list<BookData>::iterator book) {
		oss.str("");
		oss << std::left
			<< std::setw(constant::intMaxLength) << book->QtyOnHand()
			<< std::setw(constant::isbnLength) << book->Isbn()
			<< std::setw(constant::bookTitleLength) << book->BookTitle()
			<< "RMB " << std::setw(constant::doubleMaxLength) << book->Retail()
			<< "RMB " << std::setw(constant::doubleMaxLength) << static_cast<double>(book->QtyOnHand()) * book->Retail()
			<< "\n";
		std::cout << oss.str();
		}
	);
	std::cout << "-------------------------------------\n";
}

void SaleMode::ViewShoppingList() const
{
	if (DataManager::GetIntance()->GetShoppingTrolleyList().IsEmpty()) {
		std::cout << "购物车为空，无法查看！\n";
		system("pause");
		return;
	}
	system("clear");
	std::cout <<
		"		CKYF图书管理系统\n"
		"			购物车\n";
	double totalCost = 0.0;
	DataManager::GetIntance()->GetShoppingTrolleyList().ForEach([&](std::list<BookData>::iterator book) {
		totalCost += book->QtyOnHand() * book->Retail();
		}
	);
	this->PrintList();
	std::cout
		<< "销售合计：RMB " << totalCost << "\n"
		<< "零售税：RMB " << totalCost * constant::saleTax << "\n"
		<< "应付总额：RMB " << totalCost * (1.0 + constant::saleTax) << "\n"
		<< "\n"
		<< "谢谢光临！\n";
	std::cout << "是否提交订单？\n";
	char option;
	while (true) {
		GetData("请输入选择(Y/y是，N/n否）:", option);
		if (!('Y' == option || 'y' == option || 'N' == option || 'n' == option)) {
			continue;
		}
		break;
	}
	if ('Y' == option || 'y' == option) {
		DataManager::GetIntance()->GetShoppingTrolleyList().ForEach([](std::list<BookData>::iterator book) {
			auto bookInInventory = DataManager::GetIntance()->GetInventoryList().GetBookByIsbn(book->Isbn());
			(*bookInInventory)->SetQtyOnHand((*bookInInventory)->QtyOnHand() - book->QtyOnHand());
			}
		);
		std::cout << "提交订单成功！\n";
		system("pause");
	}
}

void SaleMode::AddBookToShoppingList()
{
	if (DataManager::GetIntance()->GetInventoryList().IsEmpty()) {
		std::cout << "书库为空，无法添加！\n";
		system("pause");
		return;
	}
	system("clear");
	char bookTitle[constant::bookTitleLength];
	while (true) {
		std::cout <<
			"		CKYF图书管理系统\n"
			"		  添加书到购物车\n";
		if (!DataManager::GetIntance()->GetShoppingTrolleyList().IsEmpty()) {
			this->PrintList();
		}
		if (DataManager::GetIntance()->AllBookIsInShoppingList()) {
			std::cout << "书库中所有书都已添加到购物车中，无法继续添加!\n";
			system("pause");
			return;
		}
		std::optional<std::list<BookData>::iterator> bookInInventoryList = std::nullopt;
		while (true) {
			GetData("请输入书名：（输入~退出）", bookTitle);
			if (!strncmp("~", bookTitle, sizeof(bookTitle - 1))) {
				return;
			}
			bookInInventoryList = DataManager::GetIntance()->GetInventoryList().GetBookByBookTitle(bookTitle);
			if (!bookInInventoryList) {
				std::cout << "未从书库中找到此书，请重新输入！\n";
				continue;
			}
			break;
		}
		(*bookInInventoryList)->PrintInfo();
		auto bookInShoppingTrolleyList = DataManager::GetIntance()->GetShoppingTrolleyList().GetBookByBookTitle(bookTitle);
		int amount = 0;
		while (true) {
			GetData("请输入购买数量：", amount);
			if (0 >= amount) {
				std::cout << "购买数不能小于等于零!\n";
				continue;
			}
			if ((bookInShoppingTrolleyList && ((*bookInInventoryList)->QtyOnHand() < amount + (*bookInShoppingTrolleyList)->QtyOnHand()))
				||
				((*bookInInventoryList)->QtyOnHand() < amount)) {
				std::cout << "购买数量大于库存量！\n";
				continue;
			}
			break;
		}
		if (bookInShoppingTrolleyList) {
			(*bookInShoppingTrolleyList)->SetQtyOnHand((*bookInShoppingTrolleyList)->QtyOnHand() + amount);
		}
		else {
			DataManager::GetIntance()->GetShoppingTrolleyList()
				.AddBook((*bookInInventoryList)->Isbn(), (*bookInInventoryList)->BookTitle(), (*bookInInventoryList)->Author(), (*bookInInventoryList)->Publisher(), (*bookInInventoryList)->DateAdded(), amount, (*bookInInventoryList)->Retail(), (*bookInInventoryList)->Wholesale());
		}
		std::cout << "添加成功！是否继续添加？\n";
		char option;
		while (true) {
			GetData("请输入选择(Y/y继续，N/n退出）:", option);
			if (!('Y' == option || 'y' == option || 'N' == option || 'n' == option)) {
				continue;
			}
			break;
		}
		if ('Y' == option || 'y' == option) {
			system("clear");
			continue;
		}
		break;
	}
}

void SaleMode::EditBookInShoppingList()
{
	if (DataManager::GetIntance()->GetShoppingTrolleyList().IsEmpty()) {
		std::cout << "购物车为空，无法修改！\n";
		system("pause");
		return;
	}
	system("clear");
	char bookTitle[constant::bookTitleLength];
	while (true) {
		std::cout <<
			"		CKYF图书管理系统\n"
			"		   修改购物车\n";
		if (!DataManager::GetIntance()->GetShoppingTrolleyList().IsEmpty()) {
			this->PrintList();
		}
		std::optional<std::list<BookData>::iterator> bookInShoppingTrolleyList = std::nullopt;
		while (true) {
			GetData("请输入书名：（输入~退出）", bookTitle);
			if (!strncmp("~", bookTitle, sizeof(bookTitle - 1))) {
				return;
			}
			bookInShoppingTrolleyList = DataManager::GetIntance()->GetShoppingTrolleyList().GetBookByBookTitle(bookTitle);
			if (!bookInShoppingTrolleyList) {
				std::cout << "未从购物车中找到此书，请重新输入！\n";
				continue;
			}
			break;
		}
		auto bookInInventoryList = DataManager::GetIntance()->GetShoppingTrolleyList().GetBookByBookTitle(bookTitle);
		(*bookInInventoryList)->PrintInfo();
		int amount = 0;
		while (true) {
			GetData("请输入新的购买数量：", amount);
			if (0 >= amount) {
				std::cout << "购买数不能小于等于零!\n";
				continue;
			}
			if ((*bookInInventoryList)->QtyOnHand() < amount) {
				std::cout << "购买数量大于库存量！\n";
				continue;
			}
			break;
		}
		(*bookInShoppingTrolleyList)->SetQtyOnHand(amount);
		std::cout << "修改成功！是否继续修改？\n";
		char option;
		while (true) {
			GetData("请输入选择(Y/y继续，N/n退出）:", option);
			if (!('Y' == option || 'y' == option || 'N' == option || 'n' == option)) {
				continue;
			}
			break;
		}
		if ('Y' == option || 'y' == option) {
			system("clear");
			continue;
		}
		break;
	}
}

void SaleMode::RemoveBookFromList()
{
	if (DataManager::GetIntance()->GetShoppingTrolleyList().IsEmpty()) {
		std::cout << "购物车为空，无法删除！\n";
		system("pause");
		return;
	}
	system("clear");
	char bookTitle[constant::bookTitleLength];
	while (true) {
		std::cout <<
			"		CKYF图书管理系统\n"
			"		 从购物车移除书\n";
		if (!DataManager::GetIntance()->GetShoppingTrolleyList().IsEmpty()) {
			this->PrintList();
		}
		std::optional<std::list<BookData>::iterator> bookInShoppingTrolleyList = std::nullopt;
		while (true) {
			GetData("请输入书名：（输入~退出）", bookTitle);
			if (!strncmp("~", bookTitle, sizeof(bookTitle - 1))) {
				return;
			}
			bookInShoppingTrolleyList = DataManager::GetIntance()->GetShoppingTrolleyList().GetBookByBookTitle(bookTitle);
			if (!bookInShoppingTrolleyList) {
				std::cout << "未从购物车中找到此书，请重新输入！\n";
				continue;
			}
			break;
		}
		DataManager::GetIntance()->GetShoppingTrolleyList().RemoveBook(*bookInShoppingTrolleyList);
		std::cout << "移除成功！是否继续移除？\n";
		char option;
		while (true) {
			GetData("请输入选择(Y/y继续，N/n退出, C/c清空购物车）:", option);
			if (!('Y' == option || 'y' == option || 'N' == option || 'n' == option || 'C' == option || 'c' == option)) {
				continue;
			}
			break;
		}
		if ('Y' == option || 'y' == option) {
			system("clear");
			continue;
		}
		else if ('C' == option || 'c' == option) {
			DataManager::GetIntance()->GetShoppingTrolleyList().Clear();
		}
		break;
	}
}