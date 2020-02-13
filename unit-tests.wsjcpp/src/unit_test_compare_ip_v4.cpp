#include "unit_test_compare_ip_v4.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_geoip.h>

REGISTRY_UNIT_TEST(UnitTestCompareIpV4)

UnitTestCompareIpV4::UnitTestCompareIpV4()
    : WSJCppUnitTestBase("UnitTestCompareIpV4") {
}

// ---------------------------------------------------------------------

void UnitTestCompareIpV4::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestCompareIpV4::run() {
    bool bTestSuccess = true;
    
    struct LTTest {
        LTTest(
            const WSJCppGeoIPv4 &left, 
            const WSJCppGeoIPv4 &right, 
            bool bEquals, 
            bool bMoreThen, 
            bool bLessThen, 
            bool bMoreOrEquals, 
            bool bLessOrEquals
        ) {
            this->left = left;
            this->right = right;
            this->bEquals = bEquals;
            this->bMoreThen = bMoreThen;
            this->bLessThen = bLessThen;
            this->bMoreOrEquals = bMoreOrEquals;
            this->bLessOrEquals = bLessOrEquals;
        }
        WSJCppGeoIPv4 left;
        WSJCppGeoIPv4 right;
        bool bEquals;
        bool bMoreThen; 
        bool bLessThen;
        bool bMoreOrEquals; 
        bool bLessOrEquals;
    };

    std::vector<LTTest> vTests;
    vTests.push_back(LTTest(WSJCppGeoIPv4(10, 10, 10, 10), WSJCppGeoIPv4(10, 10, 10, 10), true, false, false, true, true));
    vTests.push_back(LTTest(WSJCppGeoIPv4(11, 10, 10, 10), WSJCppGeoIPv4(10, 10, 10, 10), false, true, false, true, false));
    vTests.push_back(LTTest(WSJCppGeoIPv4(10, 255, 10, 10), WSJCppGeoIPv4(10, 10, 10, 10), false, true, false, true, false));
    vTests.push_back(LTTest(WSJCppGeoIPv4(10, 10, 12, 10), WSJCppGeoIPv4(10, 10, 10, 10), false, true, false, true, false));
    vTests.push_back(LTTest(WSJCppGeoIPv4(10, 10, 10, 11), WSJCppGeoIPv4(10, 10, 10, 10), false, true, false, true, false));
    vTests.push_back(LTTest(WSJCppGeoIPv4(1, 10, 10, 10), WSJCppGeoIPv4(10, 10, 10, 10), false, false, true, false, true));
    vTests.push_back(LTTest(WSJCppGeoIPv4(10, 0, 10, 10), WSJCppGeoIPv4(10, 10, 10, 10), false, false, true, false, true));
    vTests.push_back(LTTest(WSJCppGeoIPv4(10, 10, 10, 10), WSJCppGeoIPv4(10, 10, 255, 10), false, false, true, false, true));
    vTests.push_back(LTTest(WSJCppGeoIPv4(10, 10, 10, 1), WSJCppGeoIPv4(10, 10, 10, 10), false, false, true, false, true));
    vTests.push_back(LTTest(WSJCppGeoIPv4(0, 0, 0, 0), WSJCppGeoIPv4(255, 255, 255, 255), false, false, true, false, true));

    for (int i = 0; i < vTests.size(); i++) {
        LTTest test = vTests[i];
        WSJCppGeoIPv4 left = test.left;
        WSJCppGeoIPv4 right = test.right;
        compareB(bTestSuccess, left.toString() + " == " + right.toString(), left == right, test.bEquals);
        compareB(bTestSuccess, left.toString() + " < " + right.toString(), left < right, test.bLessThen);
        compareB(bTestSuccess, left.toString() + " > " + right.toString(), left > right, test.bMoreThen);
        compareB(bTestSuccess, left.toString() + " <= " + right.toString(), left <= right, test.bLessOrEquals);
        compareB(bTestSuccess, left.toString() + " >= " + right.toString(), left >= right, test.bMoreOrEquals);
    }
    return bTestSuccess;
}

