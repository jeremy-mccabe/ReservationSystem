#pragma once
#include "ReservationServer.h"

typedef int selection;

class Menu
{
public:
	// ctor:
	Menu();
	// dtor:
	~Menu();
	// member fxs:
	void displayOptions();
	int  selectOption();
	bool executeOption(const selection& op);
	// run fx:
	bool run();

private:
	ReservationServer* m_ptr_server = nullptr;
};