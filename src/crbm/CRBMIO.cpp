#include <crbm/CRBMIO.h>

#include <string>
#include <fstream>

using namespace std;

void CRBMIO::write(string filename, CRBM *crbm)
{
  ofstream output;
  output.open(filename, std::ofstream::trunc);
  output << "k,n,m,u: " << crbm->k() << "," << crbm->n() << "," << crbm->m() << "," << crbm->uditerations() << endl;
  output << "b:" << endl << (crbm->b()) << endl;
  output << "c:" << endl << (crbm->c()) << endl;
  output << "W:" << endl << (crbm->W()) << endl;
  output << "V:" << endl << (crbm->V()) << endl;
  output.close();
}

void CRBMIO::read(string filename, CRBM *crbm)
{
}
