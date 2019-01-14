// cqplayer.cpp: 定义应用程序的入口点。
//

#include "cqplayer.h"

#include "playerImpl.h"

#include "coCreate.h"

using namespace std;

int main()
{
	cout << "Hello CMake。" << endl;
	cout << baseInterface::interface_id << endl;

	comPtr<playerInterface> playerPtr = coCreate<playerImpl, playerInterface>(nullptr, nullptr);
	playerPtr->open(nullptr, nullptr);
	playerPtr->play(false);
	std::this_thread::sleep_for(std::chrono::seconds(500));
	playerPtr->stop();
	playerPtr->close();

	return 0;
}
