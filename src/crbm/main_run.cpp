#include <crbm/CRBMController.h>
#include <crbm/CRBMIO.h>
#include <entropy++/Container.h>
#include <entropy++/Csv.h>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include <fstream> 

using namespace std;

DEFINE_string(S,  "",    "sensor file (CSV)");
DEFINE_string(C,  "",    "CRBM");
DEFINE_string(o,  "",    "output");
DEFINE_int64(ns, -1, "nr. of sensors");
DEFINE_int64(na, -1, "nr. of actuators");
DEFINE_bool(lerr, false, "also log to stderr");

int main(int argc, char** argv)
{
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  if(FLAGS_lerr == true) FLAGS_alsologtostderr = 1;
  FLAGS_log_dir = ".";

  CRBMController* crbm = new CRBMController(FLAGS_C);
  entropy::DContainer* sensorData = entropy::Csv::read(FLAGS_S);

  double* sensors   = new double[FLAGS_ns];
  double* actuators = new double[FLAGS_na];

  ofstream log(FLAGS_o.c_str());

  for(int i = 0; i < sensorData->rows(); i++)
  {
    for(int s = 0; s < FLAGS_ns; s++)
    {
      sensors[s] = (*sensorData)(i,s);
    }
    crbm->update(sensors, actuators);
    for(int s = 0; s < FLAGS_ns; s++)
    {
      log << sensors[s] << ",";
    }
    for(int a = 0; a < FLAGS_na-1; a++)
    {
      log << actuators[a] << ",";
    }
    log << actuators[FLAGS_na-1] << endl;
  }

  log.close();

  return 0;
}
