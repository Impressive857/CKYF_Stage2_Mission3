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
		"		CKYFͼ�����ϵͳ\n"
		"			���˵�\n"
		"\n"
		"1.����ģ��\n"
		"2.������ģ��\n"
		"3.����ģ��\n"
		"4.�˳�ϵͳ\n"
		"\n"
		"������1-4֮�����\n"
		"����ѡ��";
};

#endif //!_SYSTEM_H_