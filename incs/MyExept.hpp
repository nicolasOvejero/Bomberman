//
// myExept.hpp for Avm in /home/ovejer_n/cpp_abstractvm/includes
//
// Made by nicolas ovejero
// Login   <ovejer_n@epitech.net>
//
// Started on  Sat Feb 28 21:23:49 2015 nicolas ovejero
// Last update Sat Feb 28 21:23:50 2015 nicolas ovejero
//

#ifndef __MYEXCEPTN_HPP__
# define __MYEXCEPT_HPP__

# include <string>
# include <exception>

class myExcep : public std::exception
{
public:
  myExcep(std::string const&) throw();
  virtual ~myExcep() throw();

  virtual const char* what() const throw();

private:
  std::string _msg;
};

#endif
