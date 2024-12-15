#include "TableMode.h"

void TableMode::Init()
{
}

void TableMode::OnEnter()
{
}

void TableMode::OnShow()
{
	while (true) {
		mode_ = GetMode(menuText_, static_cast<int>(MenuMode::MIN), static_cast<int>(MenuMode::MAX));
		switch (static_cast<MenuMode>(mode_)) {
		case MenuMode::SHOW_BOOK_LIST: {
			this->ShowBookList();
			break;
		}
		case MenuMode::SHOW_RETAIL_LIST: {
			this->ShowRetailList();
			break;
		}
		case MenuMode::SHOW_WHOLESALE_LIST: {
			this->ShowWholesaleList();
			break;
		}
		case MenuMode::SHOW_DATE_ADDED_LIST: {
			this->ShowDateAddedList();
			break;
		}
		case MenuMode::RETURN_TO_MAIN_MENU: {
			return;
		}
		}
	}
}

void TableMode::OnExit()
{
}

void TableMode::ShowBookList()
{
	if (DataManager::GetIntance()->GetInventoryList().IsEmpty()) {
		std::cout << "书库为空！\n";
		system("pause");
		return;
	}
	while (true) {
		system("clear");
		std::cout <<
			"		CKYF图书管理系统\n"
			"		   书库列表\n"
			<< std::format("{:<{}}{:<{}}{:<{}}{:<{}}{:<{}}\n",
				"ISBN号", constant::isbnLength,
				"书名", constant::bookTitleLength,
				"库存量", constant::intMaxLength,
				"零售价", constant::doubleMaxLength + 4,
				"批发价", constant::doubleMaxLength + 4);
		DataManager::GetIntance()->GetInventoryList().ForEach([](std::list<BookData>::iterator book)
			{
				std::cout 
					<< std::format("{:<{}}{:<{}}{:<{}}RMB {:<{}}RMB {:<{}}\n",
						book->Isbn(), constant::isbnLength,
						book->BookTitle(), constant::bookTitleLength,
						book->QtyOnHand(), constant::intMaxLength,
						book->Retail(), constant::doubleMaxLength,
						book->Wholesale(), constant::doubleMaxLength);
			}
		);
		char option;
		while (true) {
			GetData("按A/a升序排列，按D/d降序排列，按Q/q退出", option);
			if (!('A' == option || 'a' == option || 'D' == option || 'd' == option || 'Q' == option || 'q' == option)) {
				continue;
			}
			break;
		}
		if ('A' == option || 'a' == option) {
			DataManager::GetIntance()->GetInventoryList().Sort([](const BookData& book1, const BookData& book2)->bool {
				return book1.QtyOnHand() < book2.QtyOnHand();
				}
			);
		}
		else if ('D' == option || 'd' == option) {
			DataManager::GetIntance()->GetInventoryList().Sort([](const BookData& book1, const BookData& book2)->bool {
				return book1.QtyOnHand() > book2.QtyOnHand();
				}
			);
		}
		else {
			return;
		}
	};
}

void TableMode::ShowRetailList()
{
	if (DataManager::GetIntance()->GetInventoryList().IsEmpty()) {
		std::cout << "书库为空！\n";
		system("pause");
		return;
	}
	while (true) {
		system("clear");
		std::cout <<
			"		CKYF图书管理系统\n"
			"		   书库列表\n"
			<< std::format("{:<{}}{:<{}}{:<{}}{:<{}}{:<{}}\n",
				"ISBN号", constant::isbnLength,
				"书名", constant::bookTitleLength,
				"库存量", constant::intMaxLength,
				"零售价", constant::doubleMaxLength + 4,
				"零售价总额", constant::doubleMaxLength + 4);
		double totalCost = 0.0;
		DataManager::GetIntance()->GetInventoryList().ForEach([&](std::list<BookData>::iterator book)
			{
				std::cout
					<< std::format("{:<{}}{:<{}}{:<{}}RMB {:<{}}RMB {:<{}}\n",
						book->Isbn(), constant::isbnLength,
						book->BookTitle(), constant::bookTitleLength,
						book->QtyOnHand(), constant::intMaxLength,
						book->Retail(), constant::doubleMaxLength,
						book->Retail() * static_cast<double>(book->QtyOnHand()), constant::doubleMaxLength);
				totalCost += book->Retail() * static_cast<double>(book->QtyOnHand());
			}
		);
		std::cout << "零售价总额：RMB" << totalCost << "\n";
		char option;
		while (true) {
			GetData("按A/a升序排列，按D/d降序排列，按Q/q退出", option);
			if (!('A' == option || 'a' == option || 'D' == option || 'd' == option || 'Q' == option || 'q' == option)) {
				continue;
			}
			break;
		}
		if ('A' == option || 'a' == option) {
			DataManager::GetIntance()->GetInventoryList().Sort([](const BookData& book1, const BookData& book2)->bool {
				return book1.Retail() * static_cast<double>(book1.QtyOnHand()) < book2.Retail() * static_cast<double>(book2.QtyOnHand());
				}
			);
		}
		else if ('D' == option || 'd' == option) {
			DataManager::GetIntance()->GetInventoryList().Sort([](const BookData& book1, const BookData& book2)->bool {
				return book1.Retail() * static_cast<double>(book1.QtyOnHand()) > book2.Retail() * static_cast<double>(book2.QtyOnHand());
				}
			);
		}
		else {
			return;
		}
	}
}

void TableMode::ShowWholesaleList()
{
	if (DataManager::GetIntance()->GetInventoryList().IsEmpty()) {
		std::cout << "书库为空！\n";
		system("pause");
		return;
	}
	while (true) {
		system("clear");
		std::cout <<
			"		CKYF图书管理系统\n"
			"		   书库列表\n"
			<< std::format("{:<{}}{:<{}}{:<{}}{:<{}}{:<{}}\n",
				"ISBN号", constant::isbnLength,
				"书名", constant::bookTitleLength,
				"库存量", constant::intMaxLength,
				"批发价", constant::doubleMaxLength + 4,
				"批发价总额", constant::doubleMaxLength + 4);
		double totalCost = 0.0;
		DataManager::GetIntance()->GetInventoryList().ForEach([&](std::list<BookData>::iterator book)
			{
				std::cout
					<< std::format("{:<{}}{:<{}}{:<{}}RMB {:<{}}RMB {:<{}}\n",
						book->Isbn(), constant::isbnLength,
						book->BookTitle(), constant::bookTitleLength,
						book->QtyOnHand(), constant::intMaxLength,
						book->Wholesale(), constant::doubleMaxLength,
						book->Wholesale() * static_cast<double>(book->QtyOnHand()), constant::doubleMaxLength);
				totalCost += book->Wholesale() * static_cast<double>(book->QtyOnHand());
			}
		);
		std::cout << "批发价总额：RMB" << totalCost << "\n";
		char option;
		while (true) {
			GetData("按A/a升序排列，按D/d降序排列，按Q/q退出", option);
			if (!('A' == option || 'a' == option || 'D' == option || 'd' == option || 'Q' == option || 'q' == option)) {
				continue;
			}
			break;
		}
		if ('A' == option || 'a' == option) {
			DataManager::GetIntance()->GetInventoryList().Sort([](const BookData& book1, const BookData& book2)->bool {
				return book1.Wholesale() * static_cast<double>(book1.QtyOnHand()) < book2.Wholesale() * static_cast<double>(book2.QtyOnHand());
				}
			);
		}
		else if ('D' == option || 'd' == option) {
			DataManager::GetIntance()->GetInventoryList().Sort([](const BookData& book1, const BookData& book2)->bool {
				return book1.Wholesale() * static_cast<double>(book1.QtyOnHand()) > book2.Wholesale() * static_cast<double>(book2.QtyOnHand());
				}
			);
		}
		else {
			return;
		}
	}
}

void TableMode::ShowDateAddedList()
{
	if (DataManager::GetIntance()->GetInventoryList().IsEmpty()) {
		std::cout << "书库为空！\n";
		system("pause");
		return;
	}
	while (true) {
		system("clear");
		std::cout <<
			"		CKYF图书管理系统\n"
			"		   书库列表\n"
			<< std::format("{:<{}}{:<{}}{:<{}}{:<{}}\n",
				"ISBN号", constant::isbnLength,
				"书名", constant::bookTitleLength,
				"库存量", constant::intMaxLength,
				"进书日期", constant::dateMaxLength);
		DataManager::GetIntance()->GetInventoryList().ForEach([&](std::list<BookData>::iterator book)
			{
				std::cout
					<< std::format("{:<{}}{:<{}}{:<{}}{:<{}}\n",
						book->Isbn(), constant::isbnLength,
						book->BookTitle(), constant::bookTitleLength,
						book->QtyOnHand(), constant::intMaxLength,
						book->GetDateString(), constant::dateMaxLength);
			}
		);
		char option;
		while (true) {
			GetData("按A/a升序排列，按D/d降序排列，按Q/q退出", option);
			if (!('A' == option || 'a' == option || 'D' == option || 'd' == option || 'Q' == option || 'q' == option)) {
				continue;
			}
			break;
		}
		if ('A' == option || 'a' == option) {
			DataManager::GetIntance()->GetInventoryList().Sort([](const BookData& book1, const BookData& book2)->bool {
				auto status = DateCompare(book1.DateAdded(), book2.DateAdded());
				return status == DateStatus::EARLIER_THAN;
				}
			);
		}
		else if ('D' == option || 'd' == option) {
			DataManager::GetIntance()->GetInventoryList().Sort([](const BookData& book1, const BookData& book2)->bool {
				auto status = DateCompare(book1.DateAdded(), book2.DateAdded());
				return status == DateStatus::LATER_THAN;
				}
			);
		}
		else {
			return;
		}
	}
}