#include "crbm_trainer_test.h"

#include <crbm/CRBM.h>
#include <crbm/Random.h>
#include <crbm/Discretiser.h>
#include <entropy++/Container.h>

#include <iostream>
#include <string>
#include <math.h>
#include <random>

using namespace std;
using namespace libcrbm::binary;
using namespace libcrbm;
using namespace entropy;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( crbmTrainerTest );

void __copy(Matrix& dst, const Matrix& src, int index)
{
  for(int r = 0; r < dst.rows(); r++)
  {
    for(int c = 0; c < dst.cols(); c++)
    {
      dst(r,c) = src(index + c, r); // transposed
    }
  }
}

double __sigm(double v)
{
  return 1.0 / (1.0 + exp(-v));
}

void crbmTrainerTest::testTrain()
{
  Random::initialise();

  int data_points   = 200;
  int T             = 50;
  double step_width = (double)T;

  double sin_points[T+1];
  double cos_points[T+1];

  for(int i = 0; i < T+1; i++)
  {
    sin_points[i] = sin(-M_PI + (double)i * 2.0 * M_PI/step_width);
    cos_points[i] = cos(-M_PI + (double)i * 2.0 * M_PI/step_width);
  }

  DContainer Sraw(data_points, 12);
  DContainer Araw(data_points, 12);
  for(int i = 0; i < data_points; i++)
  {
    int j = (i + T) % (T+1);
    int k = ((int)(i + 1.5 * ((double)T))) % (T+1);

    int l = (i + T + 10) % (T+1);
    int m = ((int)(i + 10.0 + 1.5 * ((double)T))) % (T+1);

    Sraw << sin_points[j];
    Sraw << cos_points[j];
    Sraw << sin_points[k];
    Sraw << cos_points[k];
    Sraw << sin_points[k];
    Sraw << cos_points[k];
    Sraw << sin_points[j];
    Sraw << cos_points[j];
    Sraw << sin_points[j];
    Sraw << cos_points[j];
    Sraw << sin_points[k];
    Sraw << cos_points[k];

    Araw << sin_points[m];
    Araw << cos_points[m];
    Araw << sin_points[k];
    Araw << cos_points[k];
    Araw << sin_points[k];
    Araw << cos_points[k];
    Araw << sin_points[m];
    Araw << cos_points[m];
    Araw << sin_points[m];
    Araw << cos_points[m];
    Araw << sin_points[k];
    Araw << cos_points[k];
  }

  // initialisation

  int    bins         = 16;
  int    uditer       = 1;
  int    ne           = 5;
  int    bs           = 1;
  int    m            = 10;
  double alpha        = 1.0;
  double momentum     = 0.0;
  double weightcost   = 0.0;
  double perturbation = 0.0;


  Sraw.setBinSizes(bins);
  Sraw.setDomains(-1.0, 1.0);

  Araw.setBinSizes(bins);
  Araw.setDomains(-1.0, 1.0);

  entropy::ULContainer* sc = Sraw.discretiseByColumn();

  entropy::ULContainer* ac = Araw.discretiseByColumn();

  int nrOfSensors   = Sraw.columns();
  int nrOfActuators = Araw.columns();

  int unitPerSenAct = (int)ceil(log2(bins));

  int n = nrOfSensors   * unitPerSenAct;
  int k = nrOfActuators * unitPerSenAct;

  entropy::IContainer* binarisedInput  = new entropy::IContainer(sc->rows(), sc->columns() * unitPerSenAct);
  entropy::IContainer* binarisedOutput = new entropy::IContainer(ac->rows(), ac->columns() * unitPerSenAct);

  double values[unitPerSenAct];
  for(int r = 0; r < sc->rows(); r++)
  {
    for(int c = 0; c < sc->columns(); c++)
    {
      Discretiser::binarise(sc->get(r,c), values, unitPerSenAct);
      for(int v = 0; v < unitPerSenAct; v++)
      {
        *binarisedInput << values[v];
      }
    }
  }


  // CHECK BINEARISATION

  for(int r = 0; r < sc->rows(); r++)
  {
    for(int c = 0; c < sc->columns(); c++)
    {
      switch(sc->get(r,c))
      {
        case 0:
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 3));
          break;
        case 1:
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 3));
          break;
        case 2:
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 3));
          break;
        case 3:
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 3));
          break;
        case 4:
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 3));
          break;
        case 5:
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 3));
          break;
        case 6:
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 3));
          break;
        case 7:
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 3));
          break;
        case 8:
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 3));
          break;
        case 9:
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 3));
          break;
        case 10:
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 3));
          break;
        case 11:
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 3));
          break;
        case 12:
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 3));
          break;
        case 13:
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 3));
          break;
        case 14:
          CPPUNIT_ASSERT_EQUAL(0, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 3));
          break;
        case 15:
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 0));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 1));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 2));
          CPPUNIT_ASSERT_EQUAL(1, binarisedInput->get(r, c * 4 + 3));
          break;
      }
    }
  }

  for(int r = 0; r < ac->rows(); r++)
  {
    for(int c = 0; c < ac->columns(); c++)
    {
      Discretiser::binarise(ac->get(r,c), values, unitPerSenAct);
      for(int v = 0; v < unitPerSenAct; v++)
      {
        *binarisedOutput << values[v];
      }
    }
  }

  CRBM* crbm = new CRBM(n, m, k, uditer, bins);
  crbm->initRandomWeights(0.01);

  Matrix W  = crbm->W();
  Matrix V  = crbm->V();
  Matrix c  = crbm->c();
  Matrix Wt = W.T();

  Matrix vW;
  Matrix vV;
  Matrix vb;
  Matrix vc;

  Matrix b(n, 1);
  for(int c = 0; c < n; c++)
  {
    double p = 0.0;
    int colsum = binarisedInput->colSum(c);
    if(colsum == binarisedInput->rows())
    {
      p = ((float)(binarisedInput->rows()-1)/(float)(binarisedInput->rows()));
    }
    else if(colsum == 0)
    {
      p = 1.0/(float)(binarisedInput->rows());
    }
    else
    {
      p = ((float)colsum)/((float)binarisedInput->rows());
    }
    CPPUNIT_ASSERT(p > 0.0);
    b(c,0) = p;
  }
  crbm->setb(b);

  int length = binarisedInput->rows();

  Matrix S(binarisedInput->rows(),  binarisedInput->columns());
  Matrix A(binarisedOutput->rows(), binarisedOutput->columns());

  for(int r = 0; r < binarisedInput->rows(); r++)
  {
    for(int c = 0; c < binarisedInput->columns(); c++)
    {
      S(r,c) = binarisedInput->get(r,c);
    }
  }

  for(int r = 0; r < binarisedOutput->rows(); r++)
  {
    for(int c = 0; c < binarisedOutput->columns(); c++)
    {
      A(r,c) = binarisedOutput->get(r,c);
    }
  }

  Matrix SBatch(S.cols(),  bs);
  Matrix ABatch(A.cols(),  bs);
  Matrix ABinary(A.cols(), bs);

  Matrix Eb(n,1);
  Matrix Ec(m,1);
  Matrix EW(m,n);
  Matrix EV(m,k);
  Matrix newb(1,1);
  Matrix newc(1,1);
  Matrix newV(1,1);
  Matrix newW(1,1);

  crbm->initLearning(bs);

  Matrix bl = crbm->b();
  Matrix cl = crbm->c();

  for(int r = 0; r < bl.rows(); r++)
  {
    for(int c = 0; c < bl.cols(); c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(b(r,0), bl(r,c), 0.000001);
    }
  }

  for(int r = 0; r < cl.rows(); r++)
  {
    for(int col = 0; col < cl.cols(); col++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(c(r,0), cl(r,col), 0.000001);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(c(r,0), 0.0,       0.000001);
    }
  }

  Matrix tmp(0,0);

  vb.resize(n,1);
  vc.resize(m,1);
  vW.resize(m,n);
  vV.resize(m,k);

  for(int i = 0; i < ne; i++)
  {
    int dataStartIndex = Random::rand(0, length - bs);
    __copy(SBatch, S, dataStartIndex);

    // if(perturbation > 0.0)
    // {
      // std::default_random_engine generator;
      // std::normal_distribution<double> distribution(0.0, perturbation);
      // for(int r = 0; r < SBatch.rows(); r++)
      // {
        // for(int c = 0; c < SBatch.cols(); c++)
        // {
          // double number = distribution(generator);
          // double v      = SBatch(r,c);
          // double w      = v + number;
          // if(w >  1.0) w =  1.0;
          // if(w < -1.0) w = -1.0;
          // SBatch(r,c) = w;
        // }
      // }
    // }

    __copy(ABatch, A, dataStartIndex);

    for(int row = 0; row < ABinary.rows(); row++)
    {
      for(int col = 0; col < ABinary.cols(); col++)
      {
        ABinary(row,col) = (Random::unit() < 0.5)?1:0;
      }
    }

    Random::initialise(100 + i);
    crbm->up(SBatch, ABatch);
    Matrix z1 = crbm->z();

    // TEST Z
    Matrix z = cl + V * SBatch + W * ABatch;

    Random::initialise(100 + i);
    for(int r = 0; r < z.rows(); r++)
    {
      for(int col = 0; col < z.cols(); col++)
      {
        z(r,col) = (Random::unit() < __sigm(z(r,col)))?1.0:0.0;
        CPPUNIT_ASSERT_EQUAL(z1(r,col), z(r,col));
      }
    }

    Random::initialise(200 + i);
    crbm->learn(SBatch, ABinary);
    Matrix z2 = crbm->z();

    Random::initialise(200 + i);
    Matrix y = SBatch;
    Matrix x = ABinary;
    // up
    z = cl + V * SBatch + W * ABatch;

    for(int r = 0; r < z.rows(); r++)
    {
      for(int col = 0; col < z.cols(); col++)
      {
        z(r,col) = (Random::unit() < __sigm(z(r,col)))?1.0:0.0;
      }
    }

    for(int u = 0; u < uditer; u++)
    {
      // down
      x = bl + Wt * z;
      for(int r = 0; r < x.rows(); r++)
      {
        for(int c = 0; c < x.cols(); c++)
        {
          x(r, c) = (Random::unit() < __sigm(x(r, c)))?1.0:0.0;
        }
      }

      // up
      z = cl + V * y + W * x;
      for(int r = 0; r < z.rows(); r++)
      {
        for(int col = 0; col < z.cols(); col++)
        {
          z(r,col) = (Random::unit() < __sigm(z(r,col)))?1.0:0.0;
        }
      }
    }
    for(int r = 0; r < z.rows(); r++)
    {
      for(int col = 0; col < z.cols(); col++)
      {
        CPPUNIT_ASSERT_EQUAL(z2(r,col), z(r,col));
      }
    }


    // TEST Z

    // Eb = (ABatch.rowMean() - ABinary.rowMean());
    // Ec = (z1.rowMean()   - z2.rowMean());
    // EW = z1 * ABatch.T() - z2 * ABinary.T();
    // EV = z1 * SBatch.T() - z2 * SBatch.T();
    // tmp = alpha * Eb;
    // crbm->changeb(tmp);
    // tmp = alpha * Ec;
    // crbm->changec(tmp);
    // newW = crbm->W() + alpha * EW;
    // newV = crbm->V() + alpha * EV;

    // if(momentum > 0.0)
    // {
      // tmp = (alpha * momentum) * vb;
      // crbm->changeb(tmp);
      // tmp = (alpha * momentum) * vc;
      // crbm->changec(tmp);
      // newW = newW + alpha * momentum * vW;
      // newV = newV + alpha * momentum * vV;

      // vb = Eb;
      // vc = Ec;
      // vW = EW;
      // vV = EV;
    // }

    // if(weightcost > 0.0)
    // {
      // newW = (1.0 - weightcost) * newW;
      // newV = (1.0 - weightcost) * newV;
    // }

    // crbm->setW(newW);
    // crbm->setV(newV);
  }
}
