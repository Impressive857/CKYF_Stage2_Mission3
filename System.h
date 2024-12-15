#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <vector>
#include <iostream>
#include <cstdlib>
#include <limits>

#include "DataManager.h"
#include "Mode.h"
#include "SaleMode.h"
#include "ManagerMode.h"
#include "TableMode.h"

class System
{
public:
	enum class SystemMode {
		SALE = 1,
		MANAGER = 2,
		TABLE = 3,
		EXIT = 4,
		MIN = SALE,
		MAX = EXIT
	};
	System();
	void SelectMode();
	void SwitchTo(SystemMode mode);
	void Run();
	~System();
private:
	std::vector<Mode*> modeList_;
	Mode* currentMode_;
	bool onExit_;
	const char* menuText_ =
		"		CKYF图书管理系统\n"
		"			主菜单\n"
		"\n"
		"1.收银模块\n"
		"2.书库管理模块\n"
		"3.报表模块\n"
		"4.退出系统\n"
		"\n"
		"请输入1-4之间的数\n"
		"输入选择：";
};

#endif //!_SYSTEM_H_