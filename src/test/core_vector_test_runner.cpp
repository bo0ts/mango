/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "src/test/core_vector.h"

static CoreVectorTest suite_CoreVectorTest;

static CxxTest::List Tests_CoreVectorTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CoreVectorTest( "src/test/core_vector.h", 9, "CoreVectorTest", suite_CoreVectorTest, Tests_CoreVectorTest );

static class TestDescription_CoreVectorTest_testCreation : public CxxTest::RealTestDescription {
public:
 TestDescription_CoreVectorTest_testCreation() : CxxTest::RealTestDescription( Tests_CoreVectorTest, suiteDescription_CoreVectorTest, 18, "testCreation" ) {}
 void runTest() { suite_CoreVectorTest.testCreation(); }
} testDescription_CoreVectorTest_testCreation;

static class TestDescription_CoreVectorTest_testVectorDefaultsToZeroVector : public CxxTest::RealTestDescription {
public:
 TestDescription_CoreVectorTest_testVectorDefaultsToZeroVector() : CxxTest::RealTestDescription( Tests_CoreVectorTest, suiteDescription_CoreVectorTest, 24, "testVectorDefaultsToZeroVector" ) {}
 void runTest() { suite_CoreVectorTest.testVectorDefaultsToZeroVector(); }
} testDescription_CoreVectorTest_testVectorDefaultsToZeroVector;

static class TestDescription_CoreVectorTest_testVectorRespectsConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_CoreVectorTest_testVectorRespectsConstructor() : CxxTest::RealTestDescription( Tests_CoreVectorTest, suiteDescription_CoreVectorTest, 31, "testVectorRespectsConstructor" ) {}
 void runTest() { suite_CoreVectorTest.testVectorRespectsConstructor(); }
} testDescription_CoreVectorTest_testVectorRespectsConstructor;

static class TestDescription_CoreVectorTest_testEqualityWithNumbers : public CxxTest::RealTestDescription {
public:
 TestDescription_CoreVectorTest_testEqualityWithNumbers() : CxxTest::RealTestDescription( Tests_CoreVectorTest, suiteDescription_CoreVectorTest, 43, "testEqualityWithNumbers" ) {}
 void runTest() { suite_CoreVectorTest.testEqualityWithNumbers(); }
} testDescription_CoreVectorTest_testEqualityWithNumbers;

static class TestDescription_CoreVectorTest_testNonzeroVectorsAreNotEqualToZero : public CxxTest::RealTestDescription {
public:
 TestDescription_CoreVectorTest_testNonzeroVectorsAreNotEqualToZero() : CxxTest::RealTestDescription( Tests_CoreVectorTest, suiteDescription_CoreVectorTest, 49, "testNonzeroVectorsAreNotEqualToZero" ) {}
 void runTest() { suite_CoreVectorTest.testNonzeroVectorsAreNotEqualToZero(); }
} testDescription_CoreVectorTest_testNonzeroVectorsAreNotEqualToZero;

#include <cxxtest/Root.cpp>
