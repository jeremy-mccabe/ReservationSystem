#include "Flight.h"
#include <iterator>
#include <time.h>
#include <iostream>


// defines amount of seats already taken:
#define SEAT_FILL_PERCENT 30
// defines craft specifics:
#define NUM_OF_F_ROWS 5
#define NUM_OF_E_ROWS 30


// ctor:
Flight::Flight(
	const int& fID,
	const std::string& des,
	const std::string& al,
	const std::string& ac,
	const int& wt,
	const std::tuple<char, int>& ter,
	const std::string& dt,
	const bool& ot
	)
{
	// data member initialization:
	flightID = fID;
	destination = des;
	airline = al;
	aircraftType = ac;
	maxCarryOnWt = wt;
	terminal = ter;
	departureTime = dt;
	onTime = ot;
	seatF = new Seat('F', 775.00, false);
	seatE = new Seat('E', 325.00, false);
	first = new std::vector<FSeatRow>(NUM_OF_F_ROWS);
	economy = new std::vector<ESeatRow>(NUM_OF_E_ROWS);


	// random first class fill seeding:
	srand(time(NULL));


	// declare iterator for vector:
	std::vector<FSeatRow>::iterator F_it;
	// declare iterator for vector:
	std::vector<ESeatRow>::iterator E_it;


	// (each seat has ~SEAT_FILL_PERCENT% chance of being filled)
	for (F_it = first->begin(); F_it < first->end(); F_it++)
	{
		// left-side:
		if (rand() % 100 < SEAT_FILL_PERCENT)
			F_it->LW = true;
		if (rand() % 100 < SEAT_FILL_PERCENT)
			F_it->LA = true;
		// right-side:
		if (rand() % 100 < SEAT_FILL_PERCENT)
			F_it->RA = true;
		if (rand() % 100 < SEAT_FILL_PERCENT)
			F_it->RW = true;
	}


	// random economy class fill seeding:
	// (each seat has ~SEAT_FILL_PERCENT% chance of being filled)
	for (E_it = economy->begin(); E_it < economy->end(); E_it++)
	{
		// left-side:
		if ((rand() % 100) < SEAT_FILL_PERCENT)
			E_it->LW = true;
		if (rand() % 100 < SEAT_FILL_PERCENT)
			E_it->LC = true;
		if (rand() % 100 < SEAT_FILL_PERCENT)
			E_it->LA = true;
		// right-side:
		if (rand() % 100 < SEAT_FILL_PERCENT)
			E_it->RA = true;
		if (rand() % 100 < SEAT_FILL_PERCENT)
			E_it->RC = true;
		if (rand() % 100 < SEAT_FILL_PERCENT)
			E_it->RW = true;
	}
}


// dtor:
Flight::~Flight()
{
	// releases heap allocation:
	delete seatF;
	delete seatE;
	delete[] first;
	delete[] economy;
	seatF = nullptr;
	seatE = nullptr;
	first = nullptr;
	economy = nullptr;
}


// sets:
void
Flight::setTerminal(const std::tuple<char, int>& ter)
{
	terminal = ter;
}


void
Flight::setDepartureTime(const std::string& dt)
{
	departureTime = dt;
}


void
Flight::setOnTime(const bool& ot)
{
	onTime = ot;
}


void
Flight::setFPrice(const char& sec, const double& price, const bool& refund)
{
	seatF->setSeat(sec, price, refund);
}


void
Flight::setEPrice(const char& sec, const double& price, const bool& refund)
{
	seatE->setSeat(sec, price, refund);
}


// gets:
const int
Flight::getFlightID() const
{
	return flightID;
}


const std::string
Flight::getDestination() const
{
	return destination;
}


const std::string
Flight::getAirline() const
{
	return airline;
}


const std::string
Flight::getAircaftType() const
{
	return aircraftType;
}


int
Flight::getMaxCarryOnWt() const
{
	return maxCarryOnWt;
}


const std::tuple<char, int>
Flight::getTerminal() const
{
	return terminal;
}


const std::string
Flight::getDepatureTime() const
{
	return departureTime;
}


const bool
Flight::isOnTime() const
{
	return onTime;
}


const Seat*
Flight::getSeatF() const
{
	return seatF;
}


const Seat*
Flight::getSeatE() const
{
	return seatE;
}


std::vector<FSeatRow>*
Flight::getFirst() const
{
	return first;
}


std::vector<ESeatRow>*
Flight::getEconomy() const
{
	return economy;
}