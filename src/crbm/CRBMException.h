#ifndef __CRBM_EXCEPTION_H__
#define __CRBM_EXCEPTION_H__

#include <exception>
#include <string>
#include <iostream>

class CRBMException : public std::exception
{
  public:
    explicit CRBMException(const std::string& what)
      :m_what(what)
    {}

    virtual ~CRBMException() throw() {}

    virtual const char * what() const throw()
    {
      return m_what.c_str();
    }

    virtual void message() const throw()
    {
      std::cout << "CRBMException: " << m_what << std::endl;
    }


  private:
    std::string m_what;
};


#endif // __CRBM_EXCEPTION_H__
