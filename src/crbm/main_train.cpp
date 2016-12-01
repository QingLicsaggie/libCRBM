#include <crbm/CRBMTrainer.h>

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(S,  "",    "sensor file (CSV)");
DEFINE_string(A,  "",    "actuator file (CSV)");
DEFINE_string(o,  "",    "output filename");

DEFINE_int64(b,   16,    "bins");
DEFINE_int64(m,   16,    "nr. of hidden units");
DEFINE_int64(ud,  10,    "up-down iterations");
DEFINE_int64(ne,  20000, "number of epochs");
DEFINE_int64(bs,  50,    "batch size");
DEFINE_double(a,  0.01,  "alpha");
DEFINE_double(mo, 0.01,  "momentum");
DEFINE_double(wc, 0.01,  "weight cost");
DEFINE_double(p,  0.01,  "perturbation");
DEFINE_bool(lerr, false, "also log to stderr");
DEFINE_bool(pb,   false, "show progress bar");


int main(int argc, char** argv)
{
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  if(FLAGS_lerr == true) FLAGS_alsologtostderr = 1;
  FLAGS_log_dir = ".";

  CRBMTrainer* trainer = new CRBMTrainer(FLAGS_b,
                                         FLAGS_ud,
                                         FLAGS_ne,
                                         FLAGS_bs,
                                         FLAGS_a,
                                         FLAGS_m,
                                         FLAGS_wc,
                                         FLAGS_p);

  trainer->setUseProgressBar(FLAGS_pb);
  trainer->train(FLAGS_S, FLAGS_A, FLAGS_o, FLAGS_m);

  return 0;
}
