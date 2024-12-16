#define _CRT_SECURE_NO_WARNINGS

#ifndef _MODE_H_
#define _MODE_H_

#include <iostream>

inline int GetMode(const char* text, int min, int max) {
	int mode = 0;
	std::cout << text;
	while (true) {
		std::cin >> mode;
		if (std::cin.fail() || (mode < min) || (mode > max)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "输入不合法，请重新输入\n";
			continue;
		}
		break;
	}
	return mode;
}

class Mode {
public:
	Mode() = default;
	virtual ~Mode() = default;
	virtual void Init() = 0;
	virtual void OnEnter() = 0;
	virtual void OnShow() = 0;
	virtual void OnExit() = 0;
protected:
	int mode_ = 0;
};

#endif //!_MODE_H_