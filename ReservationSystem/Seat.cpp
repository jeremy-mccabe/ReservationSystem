#include "Seat.h"


Seat::Seat() : section('E'), price(0.0), refundable(false)
{

}


Seat::Seat(const char& s, const double& p, const bool& r)
{
	section = s;
	price = p;
	refundable = r;
}


Seat::~Seat()
{

}



// set:
void
Seat::setSeat(const char& sec, const double& p, const bool& ref)
{
	section = sec;
	price = p;
	refundable = ref;
}


// gets:
const char
Seat::getSection() const
{
	return section;
}


const double
Seat::getPrice() const
{
	return price;
}


const bool
Seat::isRefundable() const
{
	return refundable;
}