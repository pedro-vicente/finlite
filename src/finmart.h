#ifndef FINMART_HH
#define FINMART_HH

#include <string>

/////////////////////////////////////////////////////////////////////////////////////////////////////
// a single financial transaction in the FinLite system
/////////////////////////////////////////////////////////////////////////////////////////////////////

struct transaction 
{
  int id;                    // unique identifier for the transaction
  std::string date;          // when the transaction occurred
  std::string department;    // which department made the purchase
  std::string category;      // type of expense
  std::string vendor;        // who was paid
  double amount;             // how much money (in dollars)
  std::string status;        // approval status
  std::string source_system; // which system it came from
};

#endif
