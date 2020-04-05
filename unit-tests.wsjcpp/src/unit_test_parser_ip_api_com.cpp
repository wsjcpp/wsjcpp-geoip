#include "unit_test_parser_ip_api_com.h"
#include <wsjcpp_geoip.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestParserIpApiCom)

UnitTestParserIpApiCom::UnitTestParserIpApiCom() 
    : WsjcppUnitTestBase("UnitTestParserIpApiCom") {
    // 
}

// ---------------------------------------------------------------------

void UnitTestParserIpApiCom::init() {
}

// ---------------------------------------------------------------------

bool UnitTestParserIpApiCom::run() {
    std::string msg1 = "{\"status\":\"fail\",\"message\":\"reserved range\",\"query\":\"127.0.0.1\"}";
    std::string msg2 = "{\"status\":\"success\",\"country\":\"Russia\",\"countryCode\":\"RU\",\"region\":\"MOW\",\"regionName\":\"Moscow\",\"city\":\"Moscow\",\"zip\":\"144700\",\"lat\":55.7737,\"lon\":37.6055,\"timezone\":\"Europe/Moscow\",\"isp\":\"Net By Net Holding LLC\",\"org\":\"Net By Net Holding LLC\",\"as\":\"AS12714 Net By Net Holding LLC\",\"query\":\"79.120.78.1\"}";
    std::string msg3 = "{\"status\":\"success\",\"country\":\"Russia\",\"countryCode\":\"RU\",\"region\":\"MOW\",\"regionName\":\"Moscow\",\"city\":\"Moscow\",\"zip\":\"101194\",\"lat\":55.7315,\"lon\":37.6457,\"timezone\":\"Europe/Moscow\",\"isp\":\"CORBINA\",\"org\":\"\",\"as\":\"AS16345 Public Joint Stock Company \\\"Vimpel-Communications\\\"\",\"query\":\"213.234.222.81\"}";
    
    
    bool bTestSuccess = true;
    {
        WsjcppGeoIPResult result = WsjcppGeoIP::parseResponseIpApiCom("127.0.0.1", msg1);
        compareB(bTestSuccess, "msg1_status_fail", result.hasError(), true);
        compareS(bTestSuccess, "msg1_service_name", result.getServiceName(), "ip-api.com");
        compareS(bTestSuccess, "msg1_ip_address", result.getIpAddress(), "127.0.0.1");
    }
    

    WsjcppGeoIPResult result2 = WsjcppGeoIP::parseResponseIpApiCom("79.120.78.1", msg2);
    compareB(bTestSuccess, "msg2_status_success", result2.hasError(), false);
    compareS(bTestSuccess, "msg3_service_name", result2.getServiceName(), "ip-api.com");
    compareS(bTestSuccess, "msg3_ip_address", result2.getIpAddress(), "79.120.78.1");
    compareS(bTestSuccess, "msg2_country", result2.getCountry(), "Russia");
    compareS(bTestSuccess, "msg2_region", result2.getRegionName(), "Moscow");
    compareS(bTestSuccess, "msg2_city", result2.getCity(), "Moscow");
    compareD(bTestSuccess, "msg2_lat", result2.getLatitude(), 55.7737);
    compareD(bTestSuccess, "msg2_lon", result2.getLongitude(), 37.6055);

    WsjcppGeoIPResult result3 = WsjcppGeoIP::parseResponseIpApiCom("213.234.222.81", msg3);
    compareB(bTestSuccess, "msg3_status_success", result3.hasError(), false);
    compareS(bTestSuccess, "msg3_service_name", result3.getServiceName(), "ip-api.com");
    compareS(bTestSuccess, "msg3_ip_address", result3.getIpAddress(), "213.234.222.81");
    compareS(bTestSuccess, "msg3_country", result3.getCountry(), "Russia");
    compareS(bTestSuccess, "msg3_region", result3.getRegionName(), "Moscow");
    compareS(bTestSuccess, "msg3_city", result3.getCity(), "Moscow");
    compareD(bTestSuccess, "msg3_lat", result3.getLatitude(), 55.7315);
    compareD(bTestSuccess, "msg3_lon", result3.getLongitude(), 37.6457);

    return bTestSuccess;
}

// ---------------------------------------------------------------------
