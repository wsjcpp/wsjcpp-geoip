#include "unit_test_geo_ip_v4_class.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_geoip.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestGeoIpV4Class)

UnitTestGeoIpV4Class::UnitTestGeoIpV4Class()
    : WsjcppUnitTestBase("UnitTestGeoIpV4Class") {
}

// ---------------------------------------------------------------------

bool UnitTestGeoIpV4Class::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestGeoIpV4Class::executeTest() {
    bool bTestSuccess = true;

    struct LTTest {
        LTTest(const std::string &sIp, bool bExpected) {
            this->sIp = sIp;
            this->bExpected = bExpected;
        }
        std::string sIp;
        bool bExpected;
    };

    
    std::vector<LTTest> tests;
    tests.push_back(LTTest("10.10.10.10", true));
    tests.push_back(LTTest("10.-10.10.10", false));
    tests.push_back(LTTest("10.-10.10.10.1", false));
    tests.push_back(LTTest("0.0.0.0", true));
    tests.push_back(LTTest("255.255.255.255", true));

    WsjcppGeoIPv4 someIp;
    for (int i = 0; i < tests.size(); i++) {
        std::string sIp = tests[i].sIp;
        bool bRes = someIp.fromString(sIp);
        compare(sIp, bRes, tests[i].bExpected);
        if (bRes) {
            compare(sIp, someIp.toString(), sIp);
        }
    }
}

// ---------------------------------------------------------------------

bool UnitTestGeoIpV4Class::doAfterTest() {
    // nothing
    return true;
}

