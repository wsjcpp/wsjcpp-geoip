#ifndef UNIT_TEST_IP_V4_IN_RESERVED_RANGE_H
#define UNIT_TEST_IP_V4_IN_RESERVED_RANGE_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestIpV4InReservedRange : public WsjcppUnitTestBase {
    public:
        UnitTestIpV4InReservedRange();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_IP_V4_IN_RESERVED_RANGE_H

