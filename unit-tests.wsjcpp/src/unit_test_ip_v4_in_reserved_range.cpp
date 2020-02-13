#include "unit_test_ip_v4_in_reserved_range.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_geoip.h>

REGISTRY_UNIT_TEST(UnitTestIpV4InReservedRange)

UnitTestIpV4InReservedRange::UnitTestIpV4InReservedRange()
    : WSJCppUnitTestBase("UnitTestIpV4InReservedRange") {
}

// ---------------------------------------------------------------------

void UnitTestIpV4InReservedRange::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestIpV4InReservedRange::run() {
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
    tests.push_back(LTTest("0.0.0.0", true));
    tests.push_back(LTTest("0.0.0.30", true));
    tests.push_back(LTTest("0.10.0.30", true));
    tests.push_back(LTTest("0.255.255.255", true));

    tests.push_back(LTTest("10.0.0.0", true));
    tests.push_back(LTTest("10.1.0.0", true));
    tests.push_back(LTTest("10.0.1.0", true));
    tests.push_back(LTTest("10.0.0.1", true));
    tests.push_back(LTTest("10.255.255.255", true));

    tests.push_back(LTTest("100.63.0.0", false));

    tests.push_back(LTTest("100.64.0.0", true));
    tests.push_back(LTTest("100.67.0.0", true));
    tests.push_back(LTTest("100.127.255.255", true));

    tests.push_back(LTTest("100.128.255.255", false));

    tests.push_back(LTTest("127.0.0.0", true));
    tests.push_back(LTTest("127.255.255.255", true));

    tests.push_back(LTTest("169.254.0.0", true));
    tests.push_back(LTTest("169.254.255.255", true));
    
    tests.push_back(LTTest("172.16.0.0", true));
    tests.push_back(LTTest("172.31.255.255", true));
    
    tests.push_back(LTTest("192.0.0.0", true));
    tests.push_back(LTTest("192.0.0.255", true));
    
    tests.push_back(LTTest("192.0.2.0", true));
    tests.push_back(LTTest("192.0.2.255", true));
    
    tests.push_back(LTTest("192.88.99.0", true));
    tests.push_back(LTTest("192.88.99.255", true));
    
    tests.push_back(LTTest("192.168.0.0", true));
    tests.push_back(LTTest("192.168.255.255", true));

    tests.push_back(LTTest("198.18.0.0", true));
    tests.push_back(LTTest("198.19.255.255", true));

    tests.push_back(LTTest("198.51.100.0", false));
    tests.push_back(LTTest("198.51.100.255", false));

    tests.push_back(LTTest("203.0.113.0", false));
    tests.push_back(LTTest("203.0.113.255", false));
    
    tests.push_back(LTTest("224.0.0.0", true));
    tests.push_back(LTTest("239.255.255.255", true));
     
    tests.push_back(LTTest("240.0.0.0", true));
    tests.push_back(LTTest("255.255.255.254", true));
    
    tests.push_back(LTTest("240.0.0.0", true));
    tests.push_back(LTTest("255.255.255.254", true));
    
    tests.push_back(LTTest("255.255.255.255", true));
    tests.push_back(LTTest("255.255.255.255", true));

    for (int i = 0; i < tests.size(); i++) {
        std::string sIPv4 = tests[i].sIp;
        WSJCppGeoIPv4 ipV4; 
        bool bCorrectAddress = ipV4.fromString(sIPv4);
        compareB(bTestSuccess, "Invalid IPv4 Address: " + sIPv4, bCorrectAddress, true);
        if (bCorrectAddress) {
            std::string sError = "";
            bool bRes = WSJCppGeoIP::isIPv4InReservedRange(ipV4, sError);
            compareB(bTestSuccess, sIPv4, bRes, tests[i].bExpected);
        }
    }
    return bTestSuccess;
}

