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

void __copy(CRBMMatrix& dst, const CRBMMatrix& src, int index)
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

    Araw << sin_points[l];
    Araw << cos_points[l];
    Araw << sin_points[m];
    Araw << cos_points[m];
    Araw << sin_points[m];
    Araw << cos_points[m];
    Araw << sin_points[l];
    Araw << cos_points[l];
    Araw << sin_points[l];
    Araw << cos_points[l];
    Araw << sin_points[m];
    Araw << cos_points[m];
  }

  // initialisation

  int    bins         = 16;
  int    uditer       = 1;
  int    ne           = 100;
  int    bs           = 10;
  int    m            = 70;
  double alpha        = 1.0;
  double momentum     = 0.01;
  double weightcost   = 0.1;
  double perturbation = -1.0;


  Sraw.setBinSizes(bins);
  Sraw.setDomains(-1.0, 1.0);

  Araw.setBinSizes(bins);
  Araw.setDomains(-1.0, 1.0);

  entropy::ULContainer* sc = Sraw.discretiseByColumn(false);
  entropy::ULContainer* ac = Araw.discretiseByColumn(false);
  // cout << Sraw << endl;
  // cout << *sc << endl;

  for(int row = 0; row < sc->rows(); row++)
  {
    CPPUNIT_ASSERT(sc->rowSum(row) > 0.0);
  }

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

  CPPUNIT_ASSERT_EQUAL(uditer, crbm->uditerations());

  CRBMMatrix W  = crbm->W();
  CRBMMatrix V  = crbm->V();
  CRBMMatrix c  = crbm->c();
  CRBMMatrix Wt = W.T();

  CRBMMatrix vW;
  CRBMMatrix vV;
  CRBMMatrix vb;
  CRBMMatrix vc;

  CRBMMatrix b(n, 1);
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

  CRBMMatrix S(binarisedInput->rows(),  binarisedInput->columns());
  CRBMMatrix A(binarisedOutput->rows(), binarisedOutput->columns());

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

  CRBMMatrix SBatch(S.cols(),  bs);
  CRBMMatrix ABatch(A.cols(),  bs);
  CRBMMatrix ABinary(A.cols(), bs);

  crbm->initLearning(bs);

  CRBMMatrix bl = crbm->b();
  CRBMMatrix cl = crbm->c();

  CPPUNIT_ASSERT_EQUAL(crbm->b(), bl);
  CPPUNIT_ASSERT_EQUAL(crbm->c(), cl);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(c(0,0), 0.0, 0.000001);

  CRBMMatrix tmp(0,0);

  vb.resize(n,1);
  vc.resize(m,1);
  vW.resize(m,n);
  vV.resize(m,k);

  for(int i = 0; i < ne; i++)
  {

    CRBMMatrix Eb(n,1);
    CRBMMatrix Ec(m,1);
    CRBMMatrix EW(m,n);
    CRBMMatrix EV(m,k);
    CRBMMatrix newb(1,1);
    CRBMMatrix newc(1,1);
    CRBMMatrix newV(1,1);
    CRBMMatrix newW(1,1);

    int dataStartIndex = i;
    __copy(SBatch, S, dataStartIndex);

    for(int row = 0; row < bs; row++)
    {
      for(int col = 0; col < n; col++)
      {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(SBatch(col, row), S(row+i, col), 0.000001);
      }
    }

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
    for(int row = 0; row < bs; row++)
    {
      for(int col = 0; col < 12*4; col++)
      {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(ABatch(col, row), A(row+i, col), 0.000001);
      }
    }

    for(int row = 0; row < ABinary.rows(); row++)
    {
      for(int col = 0; col < ABinary.cols(); col++)
      {
        ABinary(row,col) = (Random::unit() < 0.5)?1:0;
      }
    }

    Random::initialise(100 + i);
    crbm->up(SBatch, ABatch);
    CRBMMatrix z1 = crbm->z();

    // TEST up: crbm->up(SBatch, ABatch);
    CRBMMatrix z = cl + V * SBatch + W * ABatch;

    Random::initialise(100 + i);
    for(int r = 0; r < z.rows(); r++)
    {
      for(int col = 0; col < z.cols(); col++)
      {
        double rand = Random::unit();
        // cout << "up: " << rand << endl;
        z(r,col) = (rand < __sigm(z(r,col)))?1.0:0.0;
        CPPUNIT_ASSERT_EQUAL(z1(r,col), z(r,col));
      }
    }

    Random::initialise(200 + i);
    CRBMMatrix x = ABinary;
    crbm->learn(SBatch, ABinary);
    CRBMMatrix z2 = crbm->z();
    CPPUNIT_ASSERT(x != ABinary);

    Random::initialise(200 + i);
    CRBMMatrix y = SBatch;

    // up
    z = cl + V * y + W * x;
    CPPUNIT_ASSERT_EQUAL(bs, z.cols());
    CPPUNIT_ASSERT_EQUAL(m,  z.rows());
    for(int r = 0; r < z.rows(); r++)
    {
      for(int col = 0; col < z.cols(); col++)
      {
        double rand = Random::unit();
        // cout << "up: " << rand << endl;
        z(r,col) = (rand < __sigm(z(r,col)))?1.0:0.0;
      }
    }

    for(int u = 0; u < uditer; u++)
    {
      // down
      x = bl + Wt * z;
      CPPUNIT_ASSERT_EQUAL(bs, x.cols());
      CPPUNIT_ASSERT_EQUAL(n,  x.rows());

      for(int r = 0; r < x.rows(); r++)
      {
        for(int c = 0; c < x.cols(); c++)
        {
          double rand = Random::unit();
          // cout << "down: " << rand << endl;
          x(r, c) = (rand < __sigm(x(r, c)))?1.0:0.0;
        }
      }

      // up
      z = cl + V * y + W * x;
      CPPUNIT_ASSERT_EQUAL(bs, z.cols());
      CPPUNIT_ASSERT_EQUAL(m,  z.rows());
      for(int r = 0; r < z.rows(); r++)
      {
        for(int col = 0; col < z.cols(); col++)
        {
          double rand = Random::unit();
          // cout << "up: " << rand << endl;
          z(r,col) = (rand < __sigm(z(r,col)))?1.0:0.0;
        }
      }
    }

    CPPUNIT_ASSERT_EQUAL(ABinary, x);
    CPPUNIT_ASSERT_EQUAL(z2, z);

    // cout << "z1:      " << z1.rows()      << ", " << z1.cols()      << endl;
    // cout << "z2:      " << z2.rows()      << ", " << z2.cols()      << endl;
    // cout << "ABinary: " << ABinary.rows() << ", " << ABinary.cols() << endl;
    // cout << "SBatch:  " << SBatch.rows()  << ", " << SBatch.cols()  << endl;
    // cout << "ABatch:  " << ABatch.rows()  << ", " << ABatch.cols()  << endl;

    Eb = (ABatch.rowMean() - x.rowMean());
    Ec = (z1.rowMean()     - z2.rowMean());
    EW = z1 * ABatch.T()   - z2 * x.T();
    EV = z1 * SBatch.T()   - z2 * SBatch.T();
    EW /= (double)(bs);
    EV /= (double)(bs);

    CRBMMatrix aa = z1 * ABatch.T();
    CRBMMatrix ab = z2 * x.T();
    CRBMMatrix ac = aa - ab;
    CPPUNIT_ASSERT(aa.L2() > 0.0000001);
    CPPUNIT_ASSERT(ab.L2() > 0.0000001);
    CPPUNIT_ASSERT(ac.L2() > 0.0000001);
    CPPUNIT_ASSERT_EQUAL(ac.rows(), W.rows());
    CPPUNIT_ASSERT_EQUAL(ac.cols(), W.cols());

    // if(SBatch.sum() > 0.0)
    {
      CRBMMatrix ba = z1 * SBatch.T();
      CRBMMatrix bb = z2 * SBatch.T();
      CRBMMatrix bc = ba - bb;
      CPPUNIT_ASSERT(ba.L2() > 0.0000001); // FAIL
      CPPUNIT_ASSERT(bb.L2() > 0.0000001); // FAIL
      CPPUNIT_ASSERT(bc.L2() > 0.0000001);
      CPPUNIT_ASSERT_EQUAL(bc.rows(), V.rows());
      CPPUNIT_ASSERT_EQUAL(bc.cols(), V.cols());
      CPPUNIT_ASSERT(EV.L2() > 0.0000001);
    }

    CPPUNIT_ASSERT(Eb.L2() > 0.0000001);
    CPPUNIT_ASSERT(Ec.L2() > 0.0000001);
    CPPUNIT_ASSERT(EW.L2() > 0.0000001);

    CPPUNIT_ASSERT_EQUAL(b.rows(), Eb.rows());
    CPPUNIT_ASSERT_EQUAL(c.rows(), Ec.rows());

    CPPUNIT_ASSERT_EQUAL(EW.rows(), W.rows());
    CPPUNIT_ASSERT_EQUAL(EW.cols(), W.cols());
    CPPUNIT_ASSERT_EQUAL(EV.rows(), V.rows());
    CPPUNIT_ASSERT_EQUAL(EV.cols(), V.cols());

    tmp = alpha * Eb;
    CPPUNIT_ASSERT(tmp.L2() > 0.0000001);
    crbm->changeb(tmp);
    for(int r = 0; r < bl.rows(); r++)
    {
      for(int col = 0; col < bl.cols(); col++)
      {
        bl(r,col) += tmp(r,0);
      }
    }

    tmp = alpha * Ec;
    CPPUNIT_ASSERT(tmp.L2() > 0.0000001);
    crbm->changec(tmp);
    for(int r = 0; r < cl.rows(); r++)
    {
      for(int col = 0; col < cl.cols(); col++)
      {
        cl(r,col) += tmp(r,0);
      }
    }


    newW = crbm->W() + alpha * EW;
    newV = crbm->V() + alpha * EV;

    CRBMMatrix diffW = W - newW;
    CPPUNIT_ASSERT(diffW.L2() > 0.0000001);
    CRBMMatrix diffV = V - newV;
    // if(SBatch.sum() > 0.0)
    {
      CPPUNIT_ASSERT(diffV.L2() > 0.0000001);
    }

    if(momentum > 0.0)
    {
      tmp = (alpha * momentum) * vb;
      crbm->changeb(tmp);
      for(int r = 0; r < bl.rows(); r++)
      {
        for(int col = 0; col < bl.cols(); col++)
        {
          bl(r,col) += tmp(r,0);
        }
      }

      tmp = (alpha * momentum) * vc;
      crbm->changec(tmp);
      for(int r = 0; r < cl.rows(); r++)
      {
        for(int col = 0; col < cl.cols(); col++)
        {
          cl(r,col) += tmp(r,0);
        }
      }
      newW = newW + alpha * momentum * vW;
      newV = newV + alpha * momentum * vV;

      vb = Eb;
      vc = Ec;
      vW = EW;
      vV = EV;


    }

    if(weightcost > 0.0)
    {
      newW = (1.0 - weightcost) * newW;
      newV = (1.0 - weightcost) * newV;
    }

    crbm->setW(newW);
    crbm->setV(newV);

    W  = newW;
    V  = newV;
    Wt = W.T();

    CPPUNIT_ASSERT_EQUAL(W, crbm->W());
    CPPUNIT_ASSERT_EQUAL(V, crbm->V());

    CPPUNIT_ASSERT_EQUAL(bl, crbm->b());
    CPPUNIT_ASSERT_EQUAL(cl, crbm->c());
  }
}
