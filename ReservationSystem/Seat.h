#pragma once

class Seat
{
public:
	// ctors:
	Seat();
	Seat(const char&, const double&, const bool&);
	// dtor:
	~Seat();
	// set:
	void setSeat(const char&, const double&, const bool&);
	// gets:
	const char getSection() const;
	const double getPrice() const;
	const bool isRefundable() const;

private:
	char section;
	double price;
	bool refundable;
};