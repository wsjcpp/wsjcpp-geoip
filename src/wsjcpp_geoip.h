#pragma once
#ifndef WSJCPP_GEOIP_H
#define WSJCPP_GEOIP_H

#include <string>
#include <json.hpp>

class WSJCppGeoIPResult {
    public:
        // ok
        WSJCppGeoIPResult(
            const std::string &sServiceName,
            const std::string &sIpAddress,
            const std::string &sCountry,
            const std::string &sRegionName,
            const std::string &sCity,
            double nLatitude,
            double nLongitude
        );
        // error
        WSJCppGeoIPResult(
            const std::string &sServiceName,
            const std::string &sIpAddress,
            const std::string &sErrorDescription
        );
        bool hasError();
        std::string getServiceName();
        std::string getIpAddress();
        std::string getErrorDescription();
        std::string getCountry();
        std::string getRegionName();
        std::string getCity();
        double getLatitude();
        double getLongitude();
        nlohmann::json toJson();

    private:
        std::string TAG;
        bool m_bHasError;
        std::string m_sServiceName;
        std::string m_sIpAddress;
        std::string m_sErrorDescription;
        std::string m_sCountry;
        std::string m_sRegionName;
        std::string m_sCity;
        double m_nLatitude;
        double m_nLongitude;    
};

// ---------------------------------------------------------------------

class WSJCppGeoIP {
    public:
        static WSJCppGeoIPResult requestToIpApiCom(const std::string &sIpAddress);
        static WSJCppGeoIPResult parseResponseIpApiCom(const std::string &sIpAddress, const std::string &sJson);
};


// ---------------------------------------------------------------------

#endif // WSJCPP_GEOIP_H