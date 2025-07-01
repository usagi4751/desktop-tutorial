#pragma once
#include <list>
#include "main.h"
class UDPManager
{
private:
	std::list < std::string > m_MassagePool;//サーバーからのデータを貯めておく場所

public:
	UDPManager() {};
	~UDPManager() {};



};

