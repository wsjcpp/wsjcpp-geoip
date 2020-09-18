#ifndef UNIT_TEST_GEO_IP_V4_CLASS_H
#define UNIT_TEST_GEO_IP_V4_CLASS_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestGeoIpV4Class : public WsjcppUnitTestBase {
    public:
        UnitTestGeoIpV4Class();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_GEO_IP_V4_CLASS_H

