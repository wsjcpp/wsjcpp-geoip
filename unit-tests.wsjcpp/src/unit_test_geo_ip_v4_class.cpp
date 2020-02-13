#include "unit_test_geo_ip_v4_class.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_geoip.h>

REGISTRY_UNIT_TEST(UnitTestGeoIpV4Class)

UnitTestGeoIpV4Class::UnitTestGeoIpV4Class()
    : WSJCppUnitTestBase("UnitTestGeoIpV4Class") {
}

// ---------------------------------------------------------------------

void UnitTestGeoIpV4Class::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestGeoIpV4Class::run() {
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

    WSJCppGeoIPv4 someIp;
    for (int i = 0; i < tests.size(); i++) {
        std::string sIp = tests[i].sIp;
        bool bRes = someIp.fromString(sIp);
        compareB(bTestSuccess, sIp, bRes, tests[i].bExpected);
        if (bRes) {
            compareS(bTestSuccess, sIp, someIp.toString(), sIp);
        }
    }
    return bTestSuccess;
}

