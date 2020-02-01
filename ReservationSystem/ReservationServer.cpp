#include "ReservationServer.h"
#include <iostream>
#include <iterator>


// reservation macros:
#define CREATE_F_RESERVATION() {\
saveReservation(\
flight_0->getFlightID(),\
flight_0->getDestination(),\
flight_0->getTerminal(),\
flight_0->getMaxCarryOnWt(),\
flight_0->getDepatureTime(),\
flight_0->isOnTime(),\
flight_0->getSeatF()->getPrice(),\
flight_0->getSeatF()->isRefundable(),\
currentRow, sec, pref, side); }
#define CREATE_E_RESERVATION() {\
saveReservation(\
flight_0->getFlightID(),\
flight_0->getDestination(),\
flight_0->getTerminal(),\
flight_0->getMaxCarryOnWt(),\
flight_0->getDepatureTime(),\
flight_0->isOnTime(),\
flight_0->getSeatE()->getPrice(),\
flight_0->getSeatE()->isRefundable(),\
currentRow, sec, pref, side); }


// iterators for vectors:
std::vector<FSeatRow>::iterator F_it;
std::vector<ESeatRow>::iterator E_it;


// ctor:
ReservationServer::ReservationServer()
{

}


// dtor:
ReservationServer::~ReservationServer()
{
	delete flight_0;
	delete[] reservations;
	reservations = nullptr;
}


// member functions:
void
ReservationServer::findSeat(int& sec, const int& seats, int& pref)
{
	// success used for printing message.
	bool success = false;
	// side used to specify L or R for saveReservation method (L=1, R=2).
	int side;
	// currentRow used for keeping track of row.
	int currentRow;
	// switch on choosen section and find a match, then assign seats:
	switch (sec)
	{
	case 1:
		///////////////////////////////////////////////////////////////////
		//	Single PAX first class seek logic: 
		///////////////////////////////////////////////////////////////////
		// first class:
		// #seats = 1 :
		if (seats == 1)
		{
			currentRow = 1;
			// single seat preference loop:
			for (F_it = flight_0->getFirst()->begin(); F_it < flight_0->getFirst()->end(); F_it++)
			{
				// window seat check:
				if (pref == 1)
				{
					// checks left window seat in current row for vacancy:
					if (F_it->LW == false)
					{
						// fills seat:
						F_it->LW = true;
						// creates reservation:
						/////////////////////////////////////////////////
						/// this is formatting code to adjust the section, preference,
						/// and side for the corresponding saveReservation call:
						sec = 1;	pref = 1;	side = 1;
						/////////////////////////////////////////////////
						CREATE_F_RESERVATION();
						printReservation();
						// success:
						success = true;
						break;
					}
					// checks right window seat in current row for vacancy:
					else if (F_it->RW == false)
					{
						// fills seat:
						F_it->RW = true;
						// creates reservation:
						/////////////////////////////////
						sec = 1;	pref = 1;	side = 2;
						/////////////////////////////////
						CREATE_F_RESERVATION();
						printReservation();
						// success:
						success = true;
						break;
					}
				}
				// aisle seat check:
				else
				{
					// checks left aisle seat in current row for vacancy:
					if (F_it->LA == false)
					{
						// fills seat:
						F_it->LA = true;
						// creates reservation:
						/////////////////////////////////
						sec = 1;	pref = 2;	side = 1;
						/////////////////////////////////
						CREATE_F_RESERVATION();
						printReservation();
						// success:
						success = true;
						break;
					}
					// checks right aisle seat in current row for vacancy:
					else if (F_it->RA == false)
					{
						// fills seat:
						F_it->RA = true;
						// creates reservation:
						/////////////////////////////////
						sec = 1;	pref = 2;	side = 2;
						/////////////////////////////////
						CREATE_F_RESERVATION();
						printReservation();
						// success:
						success = true;
						break;
					}
				}
				currentRow++;
			}
		}
		///////////////////////////////////////////////////////////////////
		//	Dual PAX first class seek logic: 
		///////////////////////////////////////////////////////////////////
		// #seats = 2 :
		else
		{
			currentRow = 1;
			// double seat preference loop:
			for (F_it = flight_0->getFirst()->begin(); F_it < flight_0->getFirst()->end(); F_it++)
			{
				static int currentRow = 1;
				// checks left window seat in current row for vacancy:
				if (F_it->LW == false)
				{
					// checks if left aisle seat right next to it is also vacant:
					if (F_it->LA == false)
					{
						// fills seats:
						F_it->LW = true;
						F_it->LA = true;
						// creates reservations:
						/////////////////////////////////
						sec = 1;	pref = 1;	side = 1;
						/////////////////////////////////
						CREATE_F_RESERVATION();
						printReservation();
						/////////////////////////////////
						sec = 1;	pref = 2;	side = 1;
						/////////////////////////////////
						CREATE_F_RESERVATION();
						printReservation();
						// success:
						success = true;
						break;
					}
				}
				// checks right aisle seat in current row for vacancy:
				else if (F_it->RA == false)
				{
					// checks if left aisle seat right next to it is also vacant:
					if (F_it->RW == false)
					{
						// fills seats:
						F_it->RA = true;
						F_it->RW = true;
						// creates reservations:
						/////////////////////////////////
						sec = 1;	pref = 2;	side = 2;
						/////////////////////////////////
						CREATE_F_RESERVATION();
						printReservation();
						/////////////////////////////////
						sec = 1;	pref = 1;	side = 2;
						/////////////////////////////////
						CREATE_F_RESERVATION();
						printReservation();
						// success:
						success = true;
						break;
					}
				}
				currentRow++;
			}
		}
		break;
	case 2:
		///////////////////////////////////////////////////////////////////
		//	Single PAX economy class seek logic: 
		///////////////////////////////////////////////////////////////////
		// economy class:
		// #seats = 1 :
		if (seats == 1)
		{
			currentRow = 1;
			// single seat preference loop:
			for (E_it = flight_0->getEconomy()->begin(); E_it < flight_0->getEconomy()->end(); E_it++)
			{
				static int currentRow = 1;
				// window seat check:
				if (pref == 1)
				{
					// checks left window seat in current row for vacancy:
					if (E_it->LW == false)
					{
						// fills seat:
						E_it->LW = true;
						// creates reservation:
						/////////////////////////////////
						sec = 2;	pref = 1;	side = 1;
						/////////////////////////////////
						CREATE_E_RESERVATION();
						printReservation();
						// success:
						success = true;
						break;
					}
					// checks right window seat in current row for vacancy:
					else if (E_it->RW == false)
					{
						// fills seat:
						E_it->RW = true;
						// creates reservation:
						/////////////////////////////////
						sec = 2;	pref = 1;	side = 2;
						/////////////////////////////////
						CREATE_E_RESERVATION();
						printReservation();
						// success:
						success = true;
						break;
					}
				}
				// aisle seat check:
				else if (pref == 2)
				{
					// checks left aisle seat in current row for vacancy:
					if (E_it->LA == false)
					{
						// fills seat:
						E_it->LA = true;
						// creates reservation:
						/////////////////////////////////
						sec = 2;	pref = 2;	side = 1;
						/////////////////////////////////
						CREATE_E_RESERVATION();
						printReservation();
						// success:
						success = true;
						break;
					}
					// checks right aisle seat in current row for vacancy:
					else if (E_it->RA == false)
					{
						// fills seat:
						E_it->RA = true;
						// creates reservation:
						/////////////////////////////////
						sec = 2;	pref = 2;	side = 2;
						/////////////////////////////////
						CREATE_E_RESERVATION();
						printReservation();
						// success:
						success = true;
						break;
					}
				}
				// center seat check:
				else
				{
					// checks left center seat in current row for vacancy:
					if (E_it->LC == false)
					{
						// fills seat:
						E_it->LC = true;
						// creates reservation:
						/////////////////////////////////
						sec = 2;	pref = 3;	side = 1;
						/////////////////////////////////
						CREATE_E_RESERVATION();
						printReservation();
						// success:
						success = true;
						break;
					}
					// checks right window seat in current row for vacancy:
					else if (E_it->RC == false)
					{
						// fills seat:
						E_it->RC = true;
						// creates reservation:
						/////////////////////////////////
						sec = 2;	pref = 3;	side = 2;
						/////////////////////////////////
						CREATE_E_RESERVATION();
						printReservation();
						// success:
						success = true;
						break;
					}
				}
				currentRow++;
			}
		}
		///////////////////////////////////////////////////////////////////
		//	Dual PAX economy class seek logic: 
		///////////////////////////////////////////////////////////////////
		// #seats = 2 :
		else if (seats == 2)
		{
			currentRow = 1;
			// single seat preference loop:
			for (E_it = flight_0->getEconomy()->begin(); E_it < flight_0->getEconomy()->end(); E_it++)
			{
				static int currentRow = 1;
				// window seat check:
				if (pref == 1)
				{
					// checks left window seat in current row for vacancy:
					if (E_it->LW == false)
					{
						// checks if left center seat right next to that seat is also vacant:
						if (E_it->LC == false)
						{
							// fills seat:
							E_it->LW = true;
							E_it->LC = true;
							// creates reservations:
							/////////////////////////////////
							sec = 2;	pref = 1;	side = 1;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							// creates reservations:
							/////////////////////////////////
							sec = 2;	pref = 3;	side = 1;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							// success:
							success = true;
							break;
						}
					}
					// checks right window seat in current row for vacancy:
					else if (E_it->RW == false)
					{
						// checks if right center seat right next to that seat is also vacant:
						if (E_it->LC == false)
						{
							// fills seat:
							E_it->RW = true;
							E_it->RC = true;
							// creates reservations:
							/////////////////////////////////
							sec = 2;	pref = 1;	side = 2;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							/////////////////////////////////
							sec = 2;	pref = 3;	side = 2;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							// success:
							success = true;
							break;
						}
					}
				}
				// aisle seat check:
				else if (pref == 2)
				{
					// checks left aisle seat in current row for vacancy:
					if (E_it->LA == false)
					{
						// checks if left center seat right next to that seat is also vacant:
						if (E_it->LC == false)
						{
							// fills seat:
							E_it->LA = true;
							E_it->LC = true;
							// creates reservations:
							/////////////////////////////////
							sec = 2;	pref = 2;	side = 1;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							/////////////////////////////////
							sec = 2;	pref = 3;	side = 1;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							// success:
							success = true;
							break;
						}
					}
					// checks right aisle seat in current row for vacancy:
					else if (E_it->RA == false)
					{
						// checks if right center seat right next to that seat is also vacant:
						if (E_it->RC == false)
						{
							// fills seat:
							E_it->RA = true;
							E_it->RC = true;
							// creates reservation:
							/////////////////////////////////
							sec = 2;	pref = 2;	side = 2;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							/////////////////////////////////
							sec = 2;	pref = 3;	side = 2;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							// success:
							success = true;
							break;
						}
					}
				}
				// center seat check:
				else
				{
					// checks left center seat in current row for vacancy:
					if (E_it->LC == false)
					{
						// checks if left window seat right next to that seat is also vacant:
						if (E_it->LW == false)
						{
							// fills seat:
							E_it->LC = true;
							E_it->LW = true;
							// creates reservations:
							/////////////////////////////////
							sec = 2;	pref = 3;	side = 1;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							/////////////////////////////////
							sec = 2;	pref = 1;	side = 1;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							// success:
							success = true;
							break;
						}
						// checks if left aisle seat right next to that seat is also vacant:
						else if (E_it->LA)
						{
							// fills seat:
							E_it->LC = true;
							E_it->LA = true;
							// creates reservations:
							/////////////////////////////////
							sec = 2;	pref = 3;	side = 1;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							/////////////////////////////////
							sec = 2;	pref = 2;	side = 1;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							// success:
							success = true;
							break;
						}
					}
					// checks right center seat in current row for vacancy:
					else if (E_it->RC == false)
					{
						// checks if right window seat right next to that seat is also vacant:
						if (E_it->RW == false)
						{
							// fills seat:
							E_it->RC = true;
							E_it->RW = true;
							// creates reservations:
							/////////////////////////////////
							sec = 2;	pref = 3;	side = 2;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							/////////////////////////////////
							sec = 2;	pref = 1;	side = 2;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							// success:
							success = true;
							break;
						}
						// checks if right aisle seat right next to that seat is also vacant:
						else if (E_it->RA == false)
						{
							// fills seat:
							E_it->RC = true;
							E_it->RA = true;
							// creates reservations:
							/////////////////////////////////
							sec = 2;	pref = 3;	side = 2;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							/////////////////////////////////
							sec = 2;	pref = 2;	side = 2;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							// success:
							success = true;
							break;
						}
					}
				}
				currentRow++;
			}
		}
		///////////////////////////////////////////////////////////////////
		//	Triple PAX economy class seek logic: 
		///////////////////////////////////////////////////////////////////
		// #seats = 3 :
		else
		{
			currentRow = 1;
			// triple seat preference loop:
			for (E_it = flight_0->getEconomy()->begin(); E_it < flight_0->getEconomy()->end(); E_it++)
			{
				static int currentRow = 1;
				// checks left window seat in current row for vacancy:
				if (E_it->LW == false)
				{
					// checks if left aisle seat right next to it is also vacant:
					if (E_it->LA == false)
					{
						// checks if left center seat between them is also vacant:
						if (E_it->LC == false)
						{
							// fills seats:
							E_it->LW = true;
							E_it->LA = true;
							E_it->LC = true;
							// creates reservations:
							/////////////////////////////////
							sec = 2;	pref = 1;	side = 1;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							/////////////////////////////////
							sec = 2;	pref = 2;	side = 1;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							/////////////////////////////////
							sec = 2;	pref = 3;	side = 1;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							// success:
							success = true;
							break;
						}
					}
				}
				// checks right aisle seat in current row for vacancy:
				else if (E_it->RA == false)
				{
					// checks if left aisle seat right next to it is also vacant:
					if (E_it->RW == false)
					{
						// checks if left center seat between them is also vacant:
						if (E_it->RC == false)
						{
							// fills seats:
							E_it->RA = true;
							E_it->RW = true;
							E_it->RC = true;
							// creates reservations:
							/////////////////////////////////
							sec = 2;	pref = 2;	side = 2;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							/////////////////////////////////
							sec = 2;	pref = 1;	side = 2;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							/////////////////////////////////
							sec = 2;	pref = 3;	side = 2;
							/////////////////////////////////
							CREATE_E_RESERVATION();
							printReservation();
							// success:
							success = true;
							break;
						}
					}
				}
				currentRow++;
			}
		}
		break;
	}
	///////////////////////////////////////////////////////////////////
	//	No matches: 
	///////////////////////////////////////////////////////////////////
	// if no match: prints message:
	if (!success)
	{
		std::cout << "\nWE'RE SORRY!\nYour request is unavailable for this flight.\nPlease make another request." << std::endl;
	}
}


void
ReservationServer::saveReservation(
	const int& fID,
	const std::string& des,
	const std::tuple<char, int>& ter,
	const int& wt,
	const std::string& dt,
	const bool& ot,
	const double& price,
	const bool& refund,
	const int& row,
	const int& sec,/// uses ternary operator to convert int->string 
	const int& pref,/// uses ternary operator to convert int->string
	const int& side/// uses ternary operator to convert int->string
)
{
	// Reservation is generated and pushed into a reservation vector.
	reservations->push_back(Reservation(
		fID,
		des,
		ter,
		wt,
		dt,
		ot,
		price,
		refund,
		row,
		((sec == 1) ? "First" : "Economy"),
		((pref == 1) ? "Window" : (pref == 2) ? "Aisle" : "Center"),
		((side == 1) ? "Left" : "Right")));
}


void
ReservationServer::printSeating() const
{
	// row marker:
	int row = 1;
	// prints from flight's vectors objects:
	// additional graphics:
	std::cout << "\n\t       ___" << std::endl;
	std::cout << "\t     _______" << std::endl;
	std::cout << "\t    _________" << std::endl;
	std::cout << "\t   /         \\" << std::endl;
	std::cout << "\t  -------------" << std::endl;
	std::cout << "\t /             \\" << std::endl;
	std::cout << "\t/               \\" << std::endl;
	std::cout << "\t-----------------" << std::endl;
	std::cout << "\t| (FIRST CLASS) |" << std::endl;
	std::cout << "\t|               |" << std::endl;

	// first class print loop:
	for (F_it = flight_0->getFirst()->begin(); F_it < flight_0->getFirst()->end(); F_it++)
	{
		// left-side:
		if (F_it->LW)
			std::cout << "\t|  x ";
		else
			std::cout << "\t|  _ ";
		if (F_it->LA)
			std::cout << " x";
		else
			std::cout << " _";
		// gap:
		std::cout << "\t  ";
		// right-side:
		if (F_it->RA)
			std::cout << "x ";
		else
			std::cout << "_ ";
		if (F_it->RW)
			std::cout << " x  | R: " << row;
		else
			std::cout << " _  | R: " << row;
		// next-row:
		std::cout << "\n";
		row++;
	}

	// additional graphics:
	std::cout << "\t|               |" << std::endl;
	std::cout << "\t|               |" << std::endl;
	std::cout << "\t-----------------" << std::endl;
	std::cout << "\t|(ECONOMY CLASS)|" << std::endl;
	std::cout << "\t|               |" << std::endl;


	// economy class print loop:
	for (E_it = flight_0->getEconomy()->begin(); E_it < flight_0->getEconomy()->end(); E_it++)
	{
		// left-side:
		if (E_it->LW)
			std::cout << "\t| x";
		else
			std::cout << "\t| _";
		if (E_it->LC)
			std::cout << " x";
		else
			std::cout << " _";
		if (E_it->LA)
			std::cout << " x";
		else
			std::cout << " _";
		// gap:
		std::cout << "\t  ";
		// right-side:
		if (E_it->RA)
			std::cout << "x";
		else
			std::cout << "_";
		if (E_it->RC)
			std::cout << " x";
		else
			std::cout << " _";
		if (E_it->RW)
			std::cout << " x | R: " << row;
		else
			std::cout << " _ | R: " << row;
		// next-row:
		std::cout << "\n";
		row++;
	}
	// additional graphics:
	std::cout << "\t|               |" << std::endl;
	std::cout << "\t|               |" << std::endl;
	std::cout << "\t-----------------" << std::endl;
	std::cout << "\t|               |" << std::endl;
	std::cout << "\t|               |" << std::endl;
	std::cout << "\t|               |\n\n" << std::endl;
}


void
ReservationServer::printReservation() const
{
	// working reference variable "r":
	Reservation& r = reservations->back();
	// print from vector
	std::cout << "\n\nSUCCESSFULLY found a match!\nHere is your reservation:" << std::endl;
	std::cout << "///////////////////////////////////////////////////" << std::endl;
	std::cout << "///\t\t\t\t\t\t///" << std::endl;
	std::cout << "///\t\t\t\t\t\t///" << std::endl;
	std::cout << "///\t_______FLIGHT INFORMATION________\t///" << std::endl;
	std::cout << "///" << "\tFLIGHT NUMBER:\t\t" << r.getFlightID() << "\t\t///" << std::endl;
	std::cout << "///" << "\tDESTINATION:\t\t" << r.getDestination() << "\t\t///" << std::endl;
	std::cout << "///" << "\tTERMINAL:\t\t" << std::get<0>(r.getTerminal()) << "-" <<
		std::get<1>(r.getTerminal()) << "\t\t///" << std::endl;
	std::cout << "///" << "\tMAXIMUM CARRY ON:\t" << r.getMaxCarryOnWt() << "\t\t///" << std::endl;
	std::cout << "///" << "\tDEPARTURE TIME:\t\t" << r.getDepartureTime() << "\t\t///" << std::endl;
	std::cout << "///" << "\tON SCHEDULE?:\t\t" << ((r.isOnTime()) ? "Yes" : "No") << "\t\t///" << std::endl;
	std::cout << "///" << "\tSEAT PRICE:\t\t$" << r.getPrice() << ".00\t\t///" << std::endl;
	std::cout << "///" << "\tREFUNDABLE?:\t\t" << ((r.isRefundable()) ? "Yes" : "No") << "\t\t///" << std::endl;
	std::cout << "///\t\t\t\t\t\t///" << std::endl;
	std::cout << "///\t_______SEATING INFORMATION________\t///" << std::endl;
	std::cout << "///" << "\tROW:\t\t\t" << r.getRow() << "\t\t///" << std::endl;
	std::cout << "///" << "\tSECTION:\t\t" << r.getSection() << "\t\t///" << std::endl;
	std::cout << "///" << "\tSEATING PREFERENCE:\t" << r.getPreference() << "\t\t///" << std::endl;
	std::cout << "///" << "\tSIDE:\t\t\t" << r.getSide() << "\t\t///" << std::endl;
	std::cout << "///\t\t\t\t\t\t///" << std::endl;
	std::cout << "///\t\t\t\t\t\t///" << std::endl;
	std::cout << "///////////////////////////////////////////////////\n" << std::endl;
}