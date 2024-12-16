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
			"		CKYFͼ�����ϵͳ\n"
			"		  ������ģ��\n";
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
		std::cout << "���Ϊ�գ��޷����ң�\n";
		system("pause");
		return;
	}
	GetData("������Ҫ���ҵ�������������~�˳���", this->bookTitleBuffer_);
	if (!strncmp("~", this->bookTitleBuffer_, sizeof(this->bookTitleBuffer_ - 1))) {
		return;
	}
	auto book = DataManager::GetIntance()->GetInventoryList().GetBookByBookTitle(this->bookTitleBuffer_);
	if (!book) {
		std::cout << "�����δ��ѯ������\n";
	}
	else {
		(*book)->PrintInfo();
	}
	system("pause");
}

void ManagerMode::AddBook()
{
	while (true) {
		GetData("�����������ISBN�ţ�", this->isbnBuffer_);
		if (DataManager::GetIntance()->GetInventoryList().IsbnIsExist(this->isbnBuffer_)) {
			std::cout << "��ISBN���Ѵ��ڣ����������룡\n";
			continue;
		}
		break;
	}
	while (true) {
		GetData("��������������ƣ�", this->bookTitleBuffer_);
		if (!strncmp("~", this->bookTitleBuffer_, sizeof(this->bookTitleBuffer_ - 1))) {
			std::cout << "���������Ϸ������������룡\n";
			continue;
		}
		if (DataManager::GetIntance()->GetInventoryList().BookTitleIsExist(this->bookTitleBuffer_)) {
			std::cout << "�������Ѵ��ڣ����������룡\n";
			continue;
		}
		break;
	}
	GetData("��������������ߣ�", this->authorBuffer_);
	GetData("����������ĳ����磺", this->publisherBuffer_);
	std::tm date{};
	GetDate("�����������գ�����-�ָ�����", date);
	int qtyOnhand;
	GetData("����������Ŀ������", qtyOnhand);
	double retail;
	GetData("��������������ۼۣ�", retail);
	double wholesale;
	GetData("����������������ۣ�", wholesale);
	DataManager::GetIntance()->GetInventoryList().AddBook(this->isbnBuffer_, this->bookTitleBuffer_, this->authorBuffer_, this->publisherBuffer_, date, qtyOnhand, retail, wholesale);
	std::cout << "��ӳɹ���\n";
	system("pause");
}

void ManagerMode::EditBook()
{
	if (DataManager::GetIntance()->GetInventoryList().IsEmpty()) {
		std::cout << "���Ϊ�գ��޷��޸ģ�\n";
		system("pause");
		return;
	}
	GetData("������Ҫ�޸ĵ�������������~�˳���", this->bookTitleBuffer_);
	if (!strncmp("~", this->bookTitleBuffer_, sizeof(this->bookTitleBuffer_ - 1))) {
		return;
	}
	auto book = DataManager::GetIntance()->GetInventoryList().GetBookByBookTitle(this->bookTitleBuffer_);
	if (!book) {
		std::cout << "�����δ��ѯ������\n";
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
			"		CKYFͼ�����ϵͳ\n"
			"			�޸���\n";
		(*book)->PrintInfo();
		std::cout << "\n";
		mode_ = GetMode(editBookText_, static_cast<int>(EditMode::MIN), static_cast<int>(EditMode::MAX));
		switch (static_cast<EditMode>(mode_)) {
		case EditMode::EDIT_ISBN: {
			while (true) {
				GetData("�������µ�ISBN�ţ�", this->isbnBuffer_);
				if (DataManager::GetIntance()->GetInventoryList().IsbnIsExist(this->isbnBuffer_)) {
					std::cout << "��ISBN���Ѿ����ڣ�\n";
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
				GetData("�������µ�������", this->bookTitleBuffer_);
				if (!strncmp("~", this->bookTitleBuffer_, sizeof(this->bookTitleBuffer_ - 1))) {
					std::cout << "���������Ϸ������������룡\n";
					continue;
				}
				if (DataManager::GetIntance()->GetInventoryList().BookTitleIsExist(this->bookTitleBuffer_)) {
					std::cout << "�������Ѿ����ڣ�\n";
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
			GetData("�������µ����ߣ�", this->authorBuffer_);
			(*book)->SetAuthor(this->authorBuffer_);
			break;
		}
		case EditMode::EDIT_PUBLISHER: {
			GetData("�������µĳ����磺", this->publisherBuffer_);
			(*book)->SetPubliser(this->publisherBuffer_);
			break;
		}
		case EditMode::EDIT_DATE_ADDED: {
			GetDate("�������µĽ������ڣ�", newDateAdded);
			(*book)->SetDateAdded(newDateAdded);
			break;
		}
		case EditMode::EDIT_QTY: {
			GetData("�������µĿ������", newQtyOnhand);
			(*book)->SetQtyOnHand(newQtyOnhand);
			if (bookInShoppingList && (newQtyOnhand < (*bookInShoppingList)->QtyOnHand())) {
				std::cout << "�µĿ����С�ڹ��ﳵ�����������ﳵ�������Ѿ�������\n";
				(*bookInShoppingList)->SetQtyOnHand(newQtyOnhand);
			}
			break;
		}
		case EditMode::EDIT_RETAIL: {
			GetData("�������µ����ۼۣ�", newRetail);
			(*book)->SetRetail(newRetail);
			if (bookInShoppingList) {
				(*bookInShoppingList)->SetRetail(newRetail);
			}
			break;
		}
		case EditMode::EDIT_WHOLESALE: {
			GetData("�������µ������ۣ�", newWholesale);
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
		std::cout << "���Ϊ�գ��޷�ɾ����\n";
		system("pause");
		return;
	}
	GetData("������Ҫɾ����������������~�˳���", this->bookTitleBuffer_);
	if (!strncmp("~", this->bookTitleBuffer_, sizeof(this->bookTitleBuffer_ - 1))) {
		return;
	}
	auto book = DataManager::GetIntance()->GetInventoryList().GetBookByBookTitle(this->bookTitleBuffer_);
	if (!book) {
		std::cout << "�����δ��ѯ������\n";
	}
	else {
		DataManager::GetIntance()->GetInventoryList().RemoveBook((*book));
		auto bookInShoppingList = DataManager::GetIntance()->GetShoppingTrolleyList().GetBookByBookTitle(this->bookTitleBuffer_);
		if (bookInShoppingList) {
			DataManager::GetIntance()->GetShoppingTrolleyList().RemoveBook(*bookInShoppingList);
		}
		std::cout << "ɾ���ɹ�!";
	}
	system("pause");
}