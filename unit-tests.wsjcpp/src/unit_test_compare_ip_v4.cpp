#include "unit_test_compare_ip_v4.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_geoip.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestCompareIpV4)

UnitTestCompareIpV4::UnitTestCompareIpV4()
    : WsjcppUnitTestBase("UnitTestCompareIpV4") {
}

// ---------------------------------------------------------------------

bool UnitTestCompareIpV4::doBeforeTest() {
    // nothing
    return true;
}

// ---------------------------------------------------------------------

void UnitTestCompareIpV4::executeTest() {
    
    struct LTTest {
        LTTest(
            const WsjcppGeoIPv4 &left, 
            const WsjcppGeoIPv4 &right, 
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
        WsjcppGeoIPv4 left;
        WsjcppGeoIPv4 right;
        bool bEquals;
        bool bMoreThen; 
        bool bLessThen;
        bool bMoreOrEquals; 
        bool bLessOrEquals;
    };

    std::vector<LTTest> vTests;
    vTests.push_back(LTTest(WsjcppGeoIPv4(10, 10, 10, 10), WsjcppGeoIPv4(10, 10, 10, 10), true, false, false, true, true));
    vTests.push_back(LTTest(WsjcppGeoIPv4(11, 10, 10, 10), WsjcppGeoIPv4(10, 10, 10, 10), false, true, false, true, false));
    vTests.push_back(LTTest(WsjcppGeoIPv4(10, 255, 10, 10), WsjcppGeoIPv4(10, 10, 10, 10), false, true, false, true, false));
    vTests.push_back(LTTest(WsjcppGeoIPv4(10, 10, 12, 10), WsjcppGeoIPv4(10, 10, 10, 10), false, true, false, true, false));
    vTests.push_back(LTTest(WsjcppGeoIPv4(10, 10, 10, 11), WsjcppGeoIPv4(10, 10, 10, 10), false, true, false, true, false));
    vTests.push_back(LTTest(WsjcppGeoIPv4(1, 10, 10, 10), WsjcppGeoIPv4(10, 10, 10, 10), false, false, true, false, true));
    vTests.push_back(LTTest(WsjcppGeoIPv4(10, 0, 10, 10), WsjcppGeoIPv4(10, 10, 10, 10), false, false, true, false, true));
    vTests.push_back(LTTest(WsjcppGeoIPv4(10, 10, 10, 10), WsjcppGeoIPv4(10, 10, 255, 10), false, false, true, false, true));
    vTests.push_back(LTTest(WsjcppGeoIPv4(10, 10, 10, 1), WsjcppGeoIPv4(10, 10, 10, 10), false, false, true, false, true));
    vTests.push_back(LTTest(WsjcppGeoIPv4(0, 0, 0, 0), WsjcppGeoIPv4(255, 255, 255, 255), false, false, true, false, true));

    for (int i = 0; i < vTests.size(); i++) {
        LTTest test = vTests[i];
        WsjcppGeoIPv4 left = test.left;
        WsjcppGeoIPv4 right = test.right;
        compare(left.toString() + " == " + right.toString(), left == right, test.bEquals);
        compare(left.toString() + " < " + right.toString(), left < right, test.bLessThen);
        compare(left.toString() + " > " + right.toString(), left > right, test.bMoreThen);
        compare(left.toString() + " <= " + right.toString(), left <= right, test.bLessOrEquals);
        compare(left.toString() + " >= " + right.toString(), left >= right, test.bMoreOrEquals);
    }
}

// ---------------------------------------------------------------------

bool UnitTestCompareIpV4::doAfterTest() {
    // nothing
    return true;
}

