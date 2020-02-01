#pragma once
#include "Flight.h"
#include "Reservation.h"
#include <vector>


class ReservationServer
{
public:
	// ctor:
	ReservationServer();
	// dtor:
	~ReservationServer();
	// member functions:
	void findSeat(int&, const int&, int&);
	void saveReservation(
		const int& fID,
		const std::string& des,
		const std::tuple<char, int>& ter,
		const int& wt,
		const std::string& dt,
		const bool& ot,
		const double& price,
		const bool& refund,
		const int& row,
		const int& sec,
		const int& pref,
		const int& side
	);
	void printSeating() const;
	void printReservation() const;

private:
	// flights for the day from an "incoming source" (only one flight for intents and purposes):
	Flight* flight_0 = new Flight(927445, "LAS", "American Airlines", "Airbus A321-V2", 40, std::make_tuple('A', 30), "04:32", true);
	// catalogs all passenger information:
	std::vector<Reservation>* reservations = new std::vector<Reservation>;
};