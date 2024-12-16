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
		system("clear");
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
	std::ostringstream oss;
	while (true) {
		system("clear");
		oss.str("");
		oss << std::left
			<< std::setw(constant::isbnLength) << "ISBN号"
			<< std::setw(constant::bookTitleLength) << "书名"
			<< std::setw(constant::intMaxLength) << "库存量"
			<< std::setw(constant::doubleMaxLength + 4) << "零售价"
			<< std::setw(constant::doubleMaxLength + 4) << "批发价"
			<< "\n";
		std::cout <<
			"		CKYF图书管理系统\n"
			"		   书库列表\n"
			<< oss.str();
		DataManager::GetIntance()->GetInventoryList().ForEach([&](std::list<BookData>::iterator book)
			{
				oss.str("");
				oss << std::left
					<< std::setw(constant::isbnLength) << book->Isbn()
					<< std::setw(constant::bookTitleLength) << book->BookTitle()
					<< std::setw(constant::intMaxLength) << book->QtyOnHand()
					<< "RMB " << std::setw(constant::doubleMaxLength) << book->Retail()
					<< "RMB " << std::setw(constant::doubleMaxLength) << book->Wholesale()
					<< "\n";
				std::cout << oss.str();
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
	std::ostringstream oss;
	while (true) {
		system("clear");
		oss.str("");
		oss << std::left
			<< std::setw(constant::isbnLength) << "ISBN号"
			<< std::setw(constant::bookTitleLength) << "书名"
			<< std::setw(constant::intMaxLength) << "库存量"
			<< std::setw(constant::doubleMaxLength + 4) << "零售价"
			<< std::setw(constant::doubleMaxLength + 4) << "零售价总额"
			<< "\n";
		std::cout <<
			"		CKYF图书管理系统\n"
			"		   书库列表\n"
			<< oss.str();
		double totalCost = 0.0;
		DataManager::GetIntance()->GetInventoryList().ForEach([&](std::list<BookData>::iterator book)
			{
				oss.str("");
				double thisBookCost = book->Retail() * static_cast<double>(book->QtyOnHand());
				oss << std::left
					<< std::setw(constant::isbnLength) << book->Isbn()
					<< std::setw(constant::bookTitleLength) << book->BookTitle()
					<< std::setw(constant::intMaxLength) << book->QtyOnHand()
					<< "RMB " << std::setw(constant::doubleMaxLength) << book->Retail()
					<< "RMB " << std::setw(constant::doubleMaxLength) << thisBookCost
					<< "\n";
				std::cout << oss.str();
				totalCost += thisBookCost;
			}
		);
		std::cout << "零售价总额：RMB " << totalCost << "\n";
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
	std::ostringstream oss;
	while (true) {
		system("clear");
		oss.str("");
		oss << std::left
			<< std::setw(constant::isbnLength) << "ISBN号"
			<< std::setw(constant::bookTitleLength) << "书名"
			<< std::setw(constant::intMaxLength) << "库存量"
			<< std::setw(constant::doubleMaxLength + 4) << "批发价"
			<< std::setw(constant::doubleMaxLength + 4) << "批发价总额"
			<< "\n";
		std::cout <<
			"		CKYF图书管理系统\n"
			"		   书库列表\n"
			<< oss.str();
		double totalCost = 0.0;
		DataManager::GetIntance()->GetInventoryList().ForEach([&](std::list<BookData>::iterator book)
			{
				oss.str("");
				double thisBookCost = book->Wholesale() * static_cast<double>(book->QtyOnHand());
				oss << std::left
					<< std::setw(constant::isbnLength) << book->Isbn()
					<< std::setw(constant::bookTitleLength) << book->BookTitle()
					<< std::setw(constant::intMaxLength) << book->QtyOnHand()
					<< "RMB " << std::setw(constant::doubleMaxLength) << book->Wholesale()
					<< "RMB " << std::setw(constant::doubleMaxLength) << thisBookCost
					<< "\n";
				std::cout << oss.str();
				totalCost += thisBookCost;
			}
		);
		std::cout << "批发价总额：RMB " << totalCost << "\n";
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
	std::ostringstream oss;
	while (true) {
		system("clear");
		oss.str("");
		oss << std::left
			<< std::setw(constant::isbnLength) << "ISBN号"
			<< std::setw(constant::bookTitleLength) << "书名"
			<< std::setw(constant::intMaxLength) << "库存量"
			<< std::setw(constant::dateMaxLength) << "进书日期"
			<< "\n";
		std::cout <<
			"		CKYF图书管理系统\n"
			"		   书库列表\n"
			<< oss.str();
		DataManager::GetIntance()->GetInventoryList().ForEach([&](std::list<BookData>::iterator book)
			{
				oss.str("");
				oss << std::left
					<< std::setw(constant::isbnLength) << book->Isbn()
					<< std::setw(constant::bookTitleLength) << book->BookTitle()
					<< std::setw(constant::intMaxLength) << book->QtyOnHand()
					<< std::setw(constant::dateMaxLength) << book->GetDateString()
					<< "\n";
				std::cout << oss.str();
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