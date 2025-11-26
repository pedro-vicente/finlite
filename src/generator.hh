#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "lite.hh"

class html_generator
{
public:
  static std::string generate_dashboard(finmart_db& db);
};


#endif
