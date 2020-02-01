#include "Menu.h"
#include <iostream>


typedef int selection;


Menu::Menu() : m_ptr_server(new ReservationServer)
{

}


Menu::~Menu()
{
	delete m_ptr_server;
	m_ptr_server = nullptr;
}


void
Menu::displayOptions()
{
	std::cout << "\n[OPTIONS]:" << std::endl;
	std::cout << "1 : Add Passengers" << std::endl;
	std::cout << "2 : Show Seating" << std::endl;
	std::cout << "3 : Exit" << std::endl;
}


int
Menu::selectOption()
{
	int selection;
	std::cin >> selection;
	return  selection;
}


// software takes 3 cmds-> add pax, show seating, and quit:
bool
Menu::executeOption(const selection& s)
{
	bool retVal = true;

	// outer switch: 1=Add pax, 2=Show seats, 3=Exit
	switch (s)
	{
	case 1:
	{
		// initialize section option:
		int section = 0;
		// no_error is a trigger to prevent reservation from being created in the event of an error.
		bool no_error = true;
		do {
			std::cout << "Choose seating class\n( 1=First Class | 2=Economy ): ";
			std::cin >> section;
			if (section != 1 && section != 2)
				std::cout << "\nINVALID CHOICE.  Try again." << std::endl;
		} while (section != 1 && section != 2);
		int numberOfSeats = 0;
		int preference = 0;
		// inner switch: splits sections and executes passenger adding logic.
		switch (section)
		{
			// when pax added: 
				//prompt for the class, 
				//n of pax traveling together (1/2 in FC, 1/2/3 in E), 
				//and the seating pref (window/aisle in FC, window/aisle/center in E)
		case 1:
			// first class picked:
			std::cout << "How many adjacent seats would you like?\n( 1 | 2 ): ";
			std::cin >> numberOfSeats;
			// numberOfSeats validation (weak):
			if (numberOfSeats != 1 && numberOfSeats != 2) {
				std::cout << "\n[ERROR]: Invalid selection, please start over.";
				no_error = false;
				break;
			}
			if (numberOfSeats == 1)
			{
				std::cout << "Do you have a seating preference?\n( 1=Window | 2=Aisle ): ";
				std::cin >> preference;
				// preference validation (weak):
				if (preference != 1 && preference != 2) {
					std::cout << "\n[ERROR]: Invalid selection, please start over.";
					no_error = false;
					break;
				}
			}
			break;
		case 2:
			// economy class picked:
			std::cout << "How many adjacent seats would you like?\n( 1 | 2 | 3 ): ";
			std::cin >> numberOfSeats;
			// numberOfSeats validation (weak):
			if (numberOfSeats != 1 && numberOfSeats != 2 && numberOfSeats != 3) {
				std::cout << "\n[ERROR]: Invalid selection, please start over.";
				no_error = false;
				break;
			}
			if (numberOfSeats == 1 || numberOfSeats == 2)
			{
				std::cout << "Do you have a seating preference?\n( 1=Window | 2=Aisle | 3=Center): ";
				std::cin >> preference;
				// preference validation (weak):
				if (preference != 1 && preference != 2 && preference != 3) {
					std::cout << "\n[ERROR]: Invalid selection, please start over.";
					no_error = false;
					break;
				}
			}
			break;
		}
		// accesses server.  executes seat check.
		if (m_ptr_server != nullptr && no_error == true) {
			m_ptr_server->findSeat(section, numberOfSeats, preference);
		}
		no_error = true;
		break;
	}
	case 2:
	{
		// accesses server.  print seating for current flight.
		if (m_ptr_server != nullptr)
		m_ptr_server->printSeating();
		break;
	}
	case 3:
	{
		std::cout << "\nTHANK YOU FOR FLYING WITH US!" << std::endl;
		retVal = false;
		break;
	}
	default:
		std::cout << "Invalid Option #" << std::endl;
		retVal = false;
		break;
	}

	return retVal;
}


bool
Menu::run()
{
	bool continueProcessing = true;
	do
	{
		displayOptions();
		selection s = selectOption();
		continueProcessing = executeOption(s);

	} while (continueProcessing);
	return continueProcessing;
}