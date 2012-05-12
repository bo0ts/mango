#ifndef __COREVECTOR_H
#define __COREVECTOR_H

#include <cxxtest/TestSuite.h>
#include "mango.h"

using namespace Mango; 

class CoreVectorTest : public CxxTest::TestSuite
{
    
public:
    void setUp(){
      //Core::Engine = new Core::CoreEngine();
    }

    // Creation
    void testCreation(){
      Vector v;
      Vector w(1, 2, 3);
      Vector u(1, 3);
    }

    void testVectorDefaultsToZeroVector(){
      Vector v;
      TS_ASSERT_EQUALS(v[0], 0);
      TS_ASSERT_EQUALS(v[1], 0);
      TS_ASSERT_EQUALS(v[2], 0);
    }

    void testVectorRespectsConstructor(){
      Vector v(1, 2), w(3, 4, 5);
      TS_ASSERT_EQUALS(v[0], 1);
      TS_ASSERT_EQUALS(v[1], 2);
      TS_ASSERT_EQUALS(v[2], 0);

      TS_ASSERT_EQUALS(w[0], 3);
      TS_ASSERT_EQUALS(w[1], 4);
      TS_ASSERT_EQUALS(w[2], 5);
    }

    // Comparison
    void testEqualityWithNumbers(){
      Vector v;
      TS_ASSERT_EQUALS(v, 0);
      TS_ASSERT(v == 0);
    }
    
    void testNonzeroVectorsAreNotEqualToZero(){
      Vector v1(1, 0, 0);
      Vector v2(0, 1, 0);
      Vector v3(0, 0, 1);
      
      TS_ASSERT(v1 != 0);
      TS_ASSERT(v2 != 0);
      TS_ASSERT(v3 != 0);
    }

    
};

#endif // __COREVECTOR_H
