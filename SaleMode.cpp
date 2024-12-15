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
	std::cout <<
		"���ڣ�" << (tm->tm_year + 1900) << "��" << (tm->tm_mon + 1) << "��" << (tm->tm_mday) << "��\n"
		<< std::format("{:<{}}{:<{}}{:<{}}{:<{}}{:<{}}\n",
			"����", constant::intMaxLength,
			"ISBN��", constant::isbnLength,
			"����", constant::bookTitleLength,
			"����", constant::doubleMaxLength + 4,
			"���", constant::doubleMaxLength + 4);
	DataManager::GetIntance()->GetShoppingTrolleyList().ForEach([](std::list<BookData>::iterator book) {
		std::cout
			<< std::format("{:<{}}{:<{}}{:<{}}RMB {:<{}}RMB {:<{}}\n",
				book->QtyOnHand(), constant::intMaxLength,
				book->Isbn(), constant::isbnLength,
				book->BookTitle(), constant::bookTitleLength,
				book->Retail(), constant::doubleMaxLength,
				static_cast<double>(book->QtyOnHand()) * book->Retail(), constant::doubleMaxLength);
		}
	);
	std::cout << "-------------------------------------\n";
}

void SaleMode::ViewShoppingList() const
{
	if (DataManager::GetIntance()->GetShoppingTrolleyList().IsEmpty()) {
		std::cout << "���ﳵΪ�գ��޷��鿴��\n";
		system("pause");
		return;
	}
	system("clear");
	std::cout <<
		"		CKYFͼ�����ϵͳ\n"
		"			���ﳵ\n";
	double totalCost = 0.0;
	DataManager::GetIntance()->GetShoppingTrolleyList().ForEach([&](std::list<BookData>::iterator book) {
		totalCost += book->QtyOnHand() * book->Retail();
		}
	);
	this->PrintList();
	std::cout
		<< "���ۺϼƣ�RMB " << totalCost << "\n"
		<< "����˰��RMB " << totalCost * constant::saleTax << "\n"
		<< "Ӧ���ܶRMB " << totalCost * (1.0 + constant::saleTax) << "\n"
		<< "\n"
		<< "лл���٣�\n";
	std::cout << "�Ƿ��ύ������\n";
	char option;
	while (true) {
		GetData("������ѡ��(Y/y�ǣ�N/n��:", option);
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
		std::cout << "�ύ�����ɹ���\n";
		system("pause");
	}
}

void SaleMode::AddBookToShoppingList()
{
	if (DataManager::GetIntance()->GetInventoryList().IsEmpty()) {
		std::cout << "���Ϊ�գ��޷���ӣ�\n";
		system("pause");
		return;
	}
	system("clear");
	char bookTitle[constant::bookTitleLength];
	while (true) {
		std::cout <<
			"		CKYFͼ�����ϵͳ\n"
			"		  ����鵽���ﳵ\n";
		if (!DataManager::GetIntance()->GetShoppingTrolleyList().IsEmpty()) {
			this->PrintList();
		}
		if (DataManager::GetIntance()->AllBookIsInShoppingList()) {
			std::cout << "����������鶼����ӵ����ﳵ�У��޷��������!\n";
			system("pause");
			return;
		}
		std::optional<std::list<BookData>::iterator> bookInInventoryList = std::nullopt;
		while (true) {
			GetData("������������", bookTitle);
			bookInInventoryList = DataManager::GetIntance()->GetInventoryList().GetBookByBookTitle(bookTitle);
			if (!bookInInventoryList) {
				std::cout << "δ��������ҵ����飬���������룡\n";
				continue;
			}
			break;
		}
		(*bookInInventoryList)->PrintInfo();
		auto bookInShoppingTrolleyList = DataManager::GetIntance()->GetShoppingTrolleyList().GetBookByBookTitle(bookTitle);
		int amount = 0;
		while (true) {
			GetData("�����빺��������", amount);
			if (0 >= amount) {
				std::cout << "����������С�ڵ�����!\n";
				continue;
			}
			if ((bookInShoppingTrolleyList && ((*bookInInventoryList)->QtyOnHand() < amount + (*bookInShoppingTrolleyList)->QtyOnHand()))
				||
				((*bookInInventoryList)->QtyOnHand() < amount)) {
				std::cout << "�����������ڿ������\n";
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
		std::cout << "��ӳɹ����Ƿ������ӣ�\n";
		char option;
		while (true) {
			GetData("������ѡ��(Y/y������N/n�˳���:", option);
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
		std::cout << "���ﳵΪ�գ��޷��޸ģ�\n";
		system("pause");
		return;
	}
	system("clear");
	char bookTitle[constant::bookTitleLength];
	while (true) {
		std::cout <<
			"		CKYFͼ�����ϵͳ\n"
			"		   �޸Ĺ��ﳵ\n";
		if (!DataManager::GetIntance()->GetShoppingTrolleyList().IsEmpty()) {
			this->PrintList();
		}
		std::optional<std::list<BookData>::iterator> bookInShoppingTrolleyList = std::nullopt;
		while (true) {
			GetData("������������", bookTitle);
			bookInShoppingTrolleyList = DataManager::GetIntance()->GetShoppingTrolleyList().GetBookByBookTitle(bookTitle);
			if (!bookInShoppingTrolleyList) {
				std::cout << "δ�ӹ��ﳵ���ҵ����飬���������룡\n";
				continue;
			}
			break;
		}
		auto bookInInventoryList = DataManager::GetIntance()->GetShoppingTrolleyList().GetBookByBookTitle(bookTitle);
		(*bookInInventoryList)->PrintInfo();
		int amount = 0;
		while (true) {
			GetData("�������µĹ���������", amount);
			if (0 >= amount) {
				std::cout << "����������С�ڵ�����!\n";
				continue;
			}
			if ((*bookInInventoryList)->QtyOnHand() < amount) {
				std::cout << "�����������ڿ������\n";
				continue;
			}
			break;
		}
		(*bookInShoppingTrolleyList)->SetQtyOnHand(amount);
		std::cout << "�޸ĳɹ����Ƿ�����޸ģ�\n";
		char option;
		while (true) {
			GetData("������ѡ��(Y/y������N/n�˳���:", option);
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
		std::cout << "���ﳵΪ�գ��޷�ɾ����\n";
		system("pause");
		return;
	}
	system("clear");
	char bookTitle[constant::bookTitleLength];
	while (true) {
		std::cout <<
			"		CKYFͼ�����ϵͳ\n"
			"		 �ӹ��ﳵ�Ƴ���\n";
		if (!DataManager::GetIntance()->GetShoppingTrolleyList().IsEmpty()) {
			this->PrintList();
		}
		std::optional<std::list<BookData>::iterator> bookInShoppingTrolleyList = std::nullopt;
		while (true) {
			GetData("������������", bookTitle);
			bookInShoppingTrolleyList = DataManager::GetIntance()->GetShoppingTrolleyList().GetBookByBookTitle(bookTitle);
			if (!bookInShoppingTrolleyList) {
				std::cout << "δ�ӹ��ﳵ���ҵ����飬���������룡\n";
				continue;
			}
			break;
		}
		DataManager::GetIntance()->GetShoppingTrolleyList().RemoveBook(*bookInShoppingTrolleyList);
		std::cout << "�Ƴ��ɹ����Ƿ�����Ƴ���\n";
		char option;
		while (true) {
			GetData("������ѡ��(Y/y������N/n�˳�, C/c��չ��ﳵ��:", option);
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