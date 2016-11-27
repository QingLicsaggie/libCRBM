#ifndef __RBM_EXCEPTION_H__
#define __RBM_EXCEPTION_H__

#include <exception>
#include <string>
#include <iostream>

class RBMException : public std::exception
{
  public:
    explicit RBMException(const std::string& what)
      :m_what(what)
    {}

    virtual ~RBMException() throw() {}

    virtual const char * what() const throw()
    {
      return m_what.c_str();
    }

    virtual void message() const throw()
    {
      std::cout << "RBMException: " << m_what << std::endl;
    }


  private:
    std::string m_what;
};


#endif // __RBM_EXCEPTION_H__
