#include "Reservation.h"


// ctor:
Reservation::Reservation(
	const int& fID,
	const std::string& des,
	const std::tuple<char, int>& ter,
	const int& wt,
	const std::string dt,
	const bool& ot,
	const double& p,
	const bool& re,
	const int& r,
	const std::string& sec,
	const std::string& pref,
	const std::string& s) : passID(0000)
{
	flightID = fID;
	destination = des;
	terminal = ter;
	maxCarryOnWt = wt;
	departureTime = dt;
	onTime = ot;
	price = p;
	refundable = re;
	row = r;
	section = sec;
	preference = pref;
	side = s;
}


// dtor:
Reservation::~Reservation()
{

}


// gets:
const int
Reservation::getFlightID() const
{
	return flightID;
}


const std::string
Reservation::getDestination() const
{
	return destination;
}


const std::tuple<char, int>
Reservation::getTerminal() const
{
	return terminal;
}


const int
Reservation::getMaxCarryOnWt() const
{
	return maxCarryOnWt;
}


const std::string
Reservation::getDepartureTime() const
{
	return departureTime;
}


const bool
Reservation::isOnTime() const
{
	return onTime;
}


const std::string
Reservation::getSection() const
{
	return section;
}


const double
Reservation::getPrice() const
{
	return price;
}


const bool
Reservation::isRefundable() const
{
	return refundable;
}


const int
Reservation::getRow() const
{
	return row;
}


const std::string
Reservation::getPreference() const
{
	return preference;
}


const std::string
Reservation::getSide() const
{
	return side;
}