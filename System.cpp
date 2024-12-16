#include "System.h"

System::System()
	:currentMode_(nullptr),onExit_(false)
{
	modeList_ = {
		new SaleMode(),
		new ManagerMode(),
		new TableMode(),
	};
	for (auto& mode : modeList_) {
		mode->Init();
	}
	if(!DataManager::GetIntance()->GetInventoryList().ReadFormFile("inventoryList.txt")
		||
		!DataManager::GetIntance()->GetShoppingTrolleyList().ReadFormFile("shoppingTrolleyList.txt")) {
		this->onExit_ = true;
	}
}

void System::SelectMode()
{
	system("clear");
	int mode = GetMode(menuText_, static_cast<int>(SystemMode::MIN), static_cast<int>(SystemMode::MAX));
	if (static_cast<int>(SystemMode::EXIT) == mode) {
		onExit_ = true;
	}
	else {
		SwitchTo(static_cast<SystemMode>(mode));
	}
}

void System::SwitchTo(SystemMode mode)
{
	this->currentMode_ = modeList_[static_cast<size_t>(mode) - 1];
}

void System::Run()
{
	while (!onExit_) {
		if (nullptr != this->currentMode_) {
			this->currentMode_->OnEnter();
			this->currentMode_->OnShow();
			this->currentMode_->OnExit();
		}
		SelectMode();
	}
}

System::~System()
{
	DataManager::GetIntance()->GetInventoryList().SaveToFile("inventoryList.txt");
	DataManager::GetIntance()->GetShoppingTrolleyList().SaveToFile("shoppingTrolleyList.txt");
	for (auto& mode : modeList_) {
		delete mode;
	}
}