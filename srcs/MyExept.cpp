#include "MyExept.hpp"

myExcep::myExcep(std::string const& str) throw()
{
  this->_msg = str;
}

myExcep::~myExcep() throw()
{ }

const char* myExcep::what() const throw()
{
  return (this->_msg.c_str());
}
