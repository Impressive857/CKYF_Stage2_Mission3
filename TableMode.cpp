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
		std::cout << "���Ϊ�գ�\n";
		system("pause");
		return;
	}
	while (true) {
		system("clear");
		std::cout <<
			"		CKYFͼ�����ϵͳ\n"
			"		   ����б�\n"
			<< std::format("{:<{}}{:<{}}{:<{}}{:<{}}{:<{}}\n",
				"ISBN��", constant::isbnLength,
				"����", constant::bookTitleLength,
				"�����", constant::intMaxLength,
				"���ۼ�", constant::doubleMaxLength + 4,
				"������", constant::doubleMaxLength + 4);
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
			GetData("��A/a�������У���D/d�������У���Q/q�˳�", option);
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
		std::cout << "���Ϊ�գ�\n";
		system("pause");
		return;
	}
	while (true) {
		system("clear");
		std::cout <<
			"		CKYFͼ�����ϵͳ\n"
			"		   ����б�\n"
			<< std::format("{:<{}}{:<{}}{:<{}}{:<{}}{:<{}}\n",
				"ISBN��", constant::isbnLength,
				"����", constant::bookTitleLength,
				"�����", constant::intMaxLength,
				"���ۼ�", constant::doubleMaxLength + 4,
				"���ۼ��ܶ�", constant::doubleMaxLength + 4);
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
		std::cout << "���ۼ��ܶRMB" << totalCost << "\n";
		char option;
		while (true) {
			GetData("��A/a�������У���D/d�������У���Q/q�˳�", option);
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
		std::cout << "���Ϊ�գ�\n";
		system("pause");
		return;
	}
	while (true) {
		system("clear");
		std::cout <<
			"		CKYFͼ�����ϵͳ\n"
			"		   ����б�\n"
			<< std::format("{:<{}}{:<{}}{:<{}}{:<{}}{:<{}}\n",
				"ISBN��", constant::isbnLength,
				"����", constant::bookTitleLength,
				"�����", constant::intMaxLength,
				"������", constant::doubleMaxLength + 4,
				"�������ܶ�", constant::doubleMaxLength + 4);
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
		std::cout << "�������ܶRMB" << totalCost << "\n";
		char option;
		while (true) {
			GetData("��A/a�������У���D/d�������У���Q/q�˳�", option);
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
		std::cout << "���Ϊ�գ�\n";
		system("pause");
		return;
	}
	while (true) {
		system("clear");
		std::cout <<
			"		CKYFͼ�����ϵͳ\n"
			"		   ����б�\n"
			<< std::format("{:<{}}{:<{}}{:<{}}{:<{}}\n",
				"ISBN��", constant::isbnLength,
				"����", constant::bookTitleLength,
				"�����", constant::intMaxLength,
				"��������", constant::dateMaxLength);
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
			GetData("��A/a�������У���D/d�������У���Q/q�˳�", option);
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