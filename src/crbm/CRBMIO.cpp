#include <crbm/CRBMIO.h>

#include <string>
#include <fstream>

#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

#include <stdlib.h>

using namespace std;
using namespace boost;


void CRBMIO::write(string filename, CRBM *crbm)
{
  Matrix b(crbm->n(), 1);
  Matrix c(crbm->m(), 1);
  for(int i = 0; i < crbm->n(); i++) b(i, 0) = crbm->b(i);
  for(int i = 0; i < crbm->m(); i++) c(i, 0) = crbm->c(i);
  ofstream output;
  output.open(filename, std::ofstream::trunc);
  output.precision(10);
  output.setf(ios::fixed,ios::floatfield);
  output << "k,n,m,u,b: "
    << crbm->k() << ","
    << crbm->n() << ","
    << crbm->m() << ","
    << crbm->uditerations() << ","
    << crbm->bins() << endl;
  output << "b:" << endl << b;
  output << "c:" << endl << c;
  output << "W:" << endl << crbm->W();
  output << "V:" << endl << crbm->V();
  output.close();
}

CRBM* CRBMIO::read(string filename)
{
  string line;
  ifstream input(filename);
  getline(input, line);

  line = line.substr(11, string::npos);

  vector<string> v;
  char_separator<char> sep(",");
  tokenizer< char_separator<char> > tokens(line, sep);
  BOOST_FOREACH (const string& t, tokens)
  {
    v.push_back(t);
  }

  int k    = atoi(v[0].c_str());
  int n    = atoi(v[1].c_str());
  int m    = atoi(v[2].c_str());
  int u    = atoi(v[3].c_str());
  int bins = atoi(v[4].c_str());

  CRBM* crbm = new CRBM(k,m,n,u,bins);

  getline(input, line); // "b:"
  getline(input, line); // "rows x cols:"

  Matrix b(n, 1);
  for(int i = 0; i < n; i++)
  {
    getline(input, line);
    v.clear();
    char_separator<char> bsep(" ");
    tokenizer< char_separator<char> > btokens(line, bsep);
    BOOST_FOREACH (const string& t, btokens)
    {
      v.push_back(t);
    }
    b(i, 0) = atof(v[0].c_str());
  }
  crbm->setb(b);

  getline(input, line); // "c:"
  getline(input, line); // "rows x cols"

  Matrix c(m, 1);
  for(int i = 0; i < m; i++)
  {
    getline(input, line);
    v.clear();
    char_separator<char> csep(" ");
    tokenizer< char_separator<char> > ctokens(line, csep);
    BOOST_FOREACH (const string& t, ctokens)
    {
      v.push_back(t);
    }
    c(i, 0) = atof(v[0].c_str());
  }
  crbm->setc(c);

  getline(input, line); // "W:"
  getline(input, line); // "rows x cols"

  Matrix W(m,n);
  for(int i = 0; i < m; i++)
  {
    getline(input, line);
    v.clear();
    char_separator<char> Wsep(" ");
    tokenizer< char_separator<char> > Wtokens(line, Wsep);
    BOOST_FOREACH (const string& t, Wtokens)
    {
      v.push_back(t);
    }
    for(int j = 0; j < (int)v.size(); j++)
    {
      W(i,j) = atof(v[j].c_str());
    }
  }
  crbm->setW(W);

  getline(input, line); // "V:"
  getline(input, line); // "rows x cols"

  Matrix V(m,k);
  for(int i = 0; i < m; i++)
  {
    getline(input, line);
    v.clear();
    char_separator<char> Vsep(" ");
    tokenizer< char_separator<char> > Vtokens(line, Vsep);
    BOOST_FOREACH (const string& t, Vtokens)
    {
      v.push_back(t);
    }
    for(int j = 0; j < (int)v.size(); j++)
    {
      V(i,j) = atof(v[j].c_str());
    }
  }
  crbm->setV(V);

  return crbm;
}
