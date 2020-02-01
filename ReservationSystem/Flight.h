#pragma once
#include "Seat.h"
#include <string>
#include <vector>
#include <tuple>

// first class seat struct:
struct FSeatRow
{
	// 4 ROWS:
	// left-window:
	bool LW = false;
	// left-aisle:
	bool LA = false;
	// right-aisle:
	bool RA = false;
	// right-window:
	bool RW = false;
};

// economy class seat struct:
struct ESeatRow
{
	// 6 ROWS:
	// left-window:
	bool LW = false;
	// left-center:
	bool LC = false;
	// left-aisle:
	bool LA = false;
	// right-aisle:
	bool RA = false;
	// right-center:
	bool RC = false;
	// right-window:
	bool RW = false;
};

class Flight
{
public:
	// mandatory ctor:
	Flight(
		const int&, 
		const std::string&, 
		const std::string&, 
		const std::string&, 
		const int&, 
		const std::tuple<char, int>&, 
		const std::string&,
		const bool&
		);
	// dtor:
	~Flight();
	// sets:
	void setTerminal(const std::tuple<char, int>&);
	void setDepartureTime(const std::string&);
	void setOnTime(const bool&);
	void setFPrice(const char&, const double&, const bool&);
	void setEPrice(const char&, const double&, const bool&);
	// gets:
	const int getFlightID() const;
	const std::string getDestination() const;
	const std::string getAirline() const;
	const std::string getAircaftType() const;
	int getMaxCarryOnWt() const;
	const std::tuple<char, int> getTerminal() const;
	const std::string getDepatureTime() const;
	const bool isOnTime() const;
	const Seat* getSeatF() const;
	const Seat* getSeatE() const;
	std::vector<FSeatRow>* getFirst() const;
	std::vector<ESeatRow>* getEconomy() const;

private:
	int flightID;
	std::string destination;
	std::string airline;
	std::string aircraftType;
	int maxCarryOnWt;
	std::tuple<char, int> terminal;
	std::string departureTime;
	bool onTime;
	// Seat class data members:
	Seat* seatF = nullptr;
	Seat* seatE = nullptr;
	// boolean "seat's taken" vectors:
	// F = 20 seats:
	std::vector<FSeatRow>* first = nullptr;
	// E = 180 seats:
	std::vector<ESeatRow>* economy = nullptr;
};