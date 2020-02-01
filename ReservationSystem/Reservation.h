#pragma once
#include <string>
#include <tuple>

class Reservation
{
public:
	// ctor:
	Reservation(
		const int&,
		const std::string&,
		const std::tuple<char, int>&,
		const int&,
		const std::string,
		const bool&,
		const double&,
		const bool&,
		const int&,
		const std::string&,
		const std::string&,
		const std::string&
	);
	// dtor:
	~Reservation();
	// gets:
	const int getFlightID() const;
	const std::string getDestination() const;
	const std::tuple<char, int> getTerminal() const;
	const int getMaxCarryOnWt() const;
	const std::string getDepartureTime() const;
	const bool isOnTime() const;
	const double getPrice() const;
	const bool isRefundable() const;
	const int getRow() const;
	const std::string getSection() const;
	const std::string getPreference() const;
	const std::string getSide() const;

private:
	int passID;
	int flightID;
	std::string destination;
	std::tuple<char, int> terminal;
	int maxCarryOnWt;
	std::string departureTime;
	bool onTime;
	double price;
	bool refundable;
	int row;
	std::string section;
	std::string preference;
	std::string side;
};