
#include <string.h>
#include <iostream>
#include <algorithm>
#include <wsjcpp_core.h>
#include <wsjcpp_geoip.h>

int main(int argc, const char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_NAME);
    std::string appVersion = std::string(WSJCPP_VERSION);
    if (!WSJCppCore::dirExists(".wsjcpp")) {
        WSJCppCore::makeDir(".wsjcpp");
    }
    std::string appLogPath = ".wsjcpp/logs";
    if (!WSJCppCore::dirExists(appLogPath)) {
        WSJCppCore::makeDir(appLogPath);
    }
    WSJCppLog::setPrefixLogFile("wsjcpp");
    WSJCppLog::setLogDirectory(".wsjcpp/logs");

    std::vector<std::string> vArgs;

    for (int i = 0; i < argc; i++) {
        vArgs.push_back(std::string(argv[i]));
    }

    if (vArgs.size() != 2) {
        std::cout << "Usage: " << vArgs[0] << " <ip-adderss>" << std::endl;
        return -1;
    }

    std::string sIpAddress = vArgs[1];
    WSJCppGeoIPResult res = WSJCppGeoIP::requestToIpApiCom(sIpAddress);
    if (res.hasError()) {
        std::cout << "FAILED: " << res.getErrorDescription() << std::endl;
    } else {
        std::cout << "Service Name: " << res.getServiceName() << std::endl;
        std::cout << "IP Address: " << res.getIpAddress() << std::endl;
        std::cout << "Country: " << res.getCountry() << std::endl;
        std::cout << "Region Name: " << res.getRegionName() << std::endl;
        std::cout << "City: " << res.getCity() << std::endl;
        std::cout << "Latitude: " << res.getLatitude() << std::endl;
        std::cout << "Longitude: " << res.getLongitude() << std::endl;
    }
    // std::cout << "" << nDistance << std::endl;
    return 0;
}