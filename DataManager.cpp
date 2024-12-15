#include "DataManager.h"

std::mutex DataManager::mutex_{};
DataManager* DataManager::instance_ = nullptr;

DataManager* DataManager::GetIntance() 
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (!instance_) {
		instance_ = new DataManager();
	}
	return instance_;
}

void DataManager::DestoryInstance()
{
	if (nullptr != instance_) {
		delete instance_;
		instance_ = nullptr;
	}
}

BookDataList& DataManager::GetInventoryList()
{
	return this->inventoryList_;
}

BookDataList& DataManager::GetShoppingTrolleyList()
{
	return this->shoppingTrolleyList_;
}

bool DataManager::AllBookIsInShoppingList()
{
	if (shoppingTrolleyList_.IsEmpty()) {
		return false;
	}
	bool res = true;
	this->shoppingTrolleyList_.ForEach([&](std::list<BookData>::iterator bookInShoppingList) {
		if (bookInShoppingList->QtyOnHand() != (*this->inventoryList_.GetBookByIsbn(bookInShoppingList->Isbn()))->QtyOnHand()) {
			res = false;
			return;
		}
		}
	);
	return res;
}