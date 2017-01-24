#ifndef __CRBMMATRIX_H__
#define __CRBMMATRIX_H__

#include <vector>
#include <string>
#include <iostream>

class CRBMMatrixException : public std::exception
{
  public:
    explicit CRBMMatrixException(const std::string& what)
      :m_what(what)
    {}

    virtual ~CRBMMatrixException() throw() {}

    virtual const char * what() const throw()
    {
      return m_what.c_str();
    }

    virtual void message() const throw()
    {
      std::cout << "CRBMMatrixException: " << m_what << std::endl;
    }


  private:
    std::string m_what;
};

class CRBMMatrix
{
  public:
    /** Most simple constructor. Every cell is initialised with 0.*/
    CRBMMatrix();
    CRBMMatrix(CRBMMatrix &m);
    CRBMMatrix(const CRBMMatrix &m);
    CRBMMatrix(int rows, int cols);

    /** Most simple constructor. Every cell is initialised with the given
     * value.*/
    CRBMMatrix(int rows, int cols, double initialValue);

    /** Most simple constructor. The cells are initialised with the values of
     * the vector. If the vector is smaller than the numbers of cells, the
     * remaining cells are filled with 0. The filling occurs rows first.
     */
    CRBMMatrix(int rows, int cols, std::vector<double> initialValues);

    /** Destructor. */
    ~CRBMMatrix();

    /** Allows to access and modification of the values by indexing */
    double&   operator()(int row, int col) throw(CRBMMatrixException);
    double    operator()(int row, int col) const throw(CRBMMatrixException);
    CRBMMatrix&   operator+=(const CRBMMatrix &m)  throw(CRBMMatrixException);
    CRBMMatrix&   operator-=(const CRBMMatrix &m)  throw(CRBMMatrixException);

    // TODO: CRBMMatrix A(10,10); CRBMMatrix A = B; does not work
    const CRBMMatrix operator*(const double factor);
    CRBMMatrix&      operator*=(const double factor);

    bool         operator==(const CRBMMatrix&) const;
    bool         operator!=(const CRBMMatrix& b) const;

    CRBMMatrix&      operator= (const CRBMMatrix &m);
    CRBMMatrix&      operator*=(const CRBMMatrix &m) throw(CRBMMatrixException);

    CRBMMatrix&      operator= (const double d);
    CRBMMatrix&      operator-=(const double d);
    CRBMMatrix&      operator/=(const double d);

    const CRBMMatrix operator-(const CRBMMatrix &m) const;
    const CRBMMatrix operator+(const CRBMMatrix &m) const;
    const CRBMMatrix operator*(const CRBMMatrix &m);

    double L2();

    int    cols() const;
    int    rows() const;

    void   setDiagonalCRBMMatrix(double value);

    double rowSum(const int row);
    double colSum(const int col);
    double sum();

    void   reset(int rows, int cols, double value = (double)0.0);
    void   rescaleRows(double value, bool verbose);

    double det() throw(CRBMMatrixException);
    void   invert();
    void   transpose();
    CRBMMatrix T();
    CRBMMatrix colMean();
    CRBMMatrix rowMean();
    void   adjunct();
    void   cut(int r_index = -1, int c_index = -1);
    double get(const int row, const int col);

    void   resize(int rows, int columns);

    friend CRBMMatrix operator*(double, const CRBMMatrix&);

    friend std::ostream& operator<<(std::ostream& str, const CRBMMatrix& m)
    {
      str << m._rows << "x" << m._cols << std::endl;
      str.precision(10);
      str.setf(std::ios::fixed,std::ios::floatfield);
      for(int r = 0; r < m._rows; r++)
      {
        for(int c = 0; c < m._cols - 1; c++)
        {
          str << m._cell[r][c] << " ";
        }
        str << m._cell[r][m._cols -1] << std::endl;
      }
      return str;
    };

  protected:
    void     __set(const  int row, const int col, const  double value);
    double   __get(const  int row, const int col);
    void     __add(const  int row, const int col, const  double value);
    void     __deleteCells();
    void     __copy(const CRBMMatrix &m);
    void     __init(const int rows, const int cols, double initialValue);
    void     __check(int  row, int col) throw(CRBMMatrixException);
    int      _rows;
    int      _cols;
    double** _cell;

};

#endif // __CRBMMATRIX_H__
