#ifndef UNIT_TEST_COMPARE_IP_V4_H
#define UNIT_TEST_COMPARE_IP_V4_H

#include <wsjcpp_unit_tests.h>

class UnitTestCompareIpV4 : public WsjcppUnitTestBase {
    public:
        UnitTestCompareIpV4();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_COMPARE_IP_V4_H

