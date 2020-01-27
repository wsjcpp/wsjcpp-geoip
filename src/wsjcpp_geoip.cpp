#include "wsjcpp_geoip.h"
#include <json.hpp>
#include <wsjcpp_core.h>

// ----------------------------------------------------------------------

WSJCppGeoIPResult::WSJCppGeoIPResult(
    const std::string &sServiceName,
    const std::string &sIpAddress,
    const std::string &sCountry,
    const std::string &sRegionName,
    const std::string &sCity,
    double nLatitude,
    double nLongitude
) {
    TAG = "WSJCppGeoIPResult-" + sServiceName;
    m_bHasError = false;
    m_sErrorDescription = "";
    m_sServiceName = sServiceName;
    m_sIpAddress = sIpAddress;
    m_sCountry = sCountry;
    m_sRegionName = sRegionName;
    m_sCity = sCity;
    m_nLatitude = nLatitude;
    m_nLongitude = nLongitude;
}

// ----------------------------------------------------------------------

WSJCppGeoIPResult::WSJCppGeoIPResult(
    const std::string &sServiceName,
    const std::string &sIpAddress,
    const std::string &sErrorDescription
) {
    TAG = "WSJCppGeoIPResult-" + sServiceName;
    m_bHasError = true;
    m_sIpAddress = sIpAddress;
    m_sErrorDescription = sErrorDescription;
    m_sServiceName = sServiceName;
    m_sCountry = "";
    m_sRegionName = "";
    m_sCity = "";
    m_nLatitude = 0;
    m_nLongitude = 0;
}

// ----------------------------------------------------------------------

bool WSJCppGeoIPResult::hasError() {
    return m_bHasError;
}

// ----------------------------------------------------------------------

std::string WSJCppGeoIPResult::getServiceName() {
    return m_sServiceName;
}

// ----------------------------------------------------------------------

std::string WSJCppGeoIPResult::getIpAddress() {
    return m_sIpAddress;
}

// ----------------------------------------------------------------------

std::string WSJCppGeoIPResult::getErrorDescription() {
    if (!m_bHasError) {
        WSJCppLog::warn(TAG, "getErrorDescription, Result hasn't error");
    }
    return m_sErrorDescription;
}

// ----------------------------------------------------------------------

std::string WSJCppGeoIPResult::getCountry() {
    if (m_bHasError) {
        WSJCppLog::warn(TAG, "getCountry, result has error");
    }
    return m_sCountry;
}

// ----------------------------------------------------------------------

std::string WSJCppGeoIPResult::getRegionName() {
    if (m_bHasError) {
        WSJCppLog::warn(TAG, "getRegionName, result has error");
    }
    return m_sRegionName;
}

// ----------------------------------------------------------------------

std::string WSJCppGeoIPResult::getCity() {
    if (m_bHasError) {
        WSJCppLog::warn(TAG, "getCity, result has error");
    }
    return m_sCity;
}

// ----------------------------------------------------------------------

double WSJCppGeoIPResult::getLatitude() {
    if (m_bHasError) {
        WSJCppLog::warn(TAG, "getLatitude, result has error");
    }
    return m_nLatitude;
}

// ----------------------------------------------------------------------

double WSJCppGeoIPResult::getLongitude() {
    if (m_bHasError) {
        WSJCppLog::warn(TAG, "getLongitude, result has error");
    }
    return m_nLongitude;
}

// ----------------------------------------------------------------------

nlohmann::json WSJCppGeoIPResult::toJson() {
    nlohmann::json jsonRet;
    jsonRet["serviceName"] = m_sServiceName;
    jsonRet["ip"] = m_sIpAddress;
    if (m_bHasError) {
        jsonRet["error"] = m_sErrorDescription;
    } else {
        jsonRet["longitude"] = m_nLongitude;
        jsonRet["latitude"] = m_nLatitude;
        jsonRet["longitude"] = m_sCountry;
        jsonRet["regionName"] = m_sRegionName;
        jsonRet["city"] = m_sCity;
    }
    return jsonRet;
}

// ----------------------------------------------------------------------

WSJCppGeoIPResult WSJCppGeoIP::requestToIpApiCom(const std::string &sIpAddress) {
    std::string sServiceName = "ip-api.com";
    std::string TAG = "requestToIpApiCom";

    // TODO check is ip address v4 v6 in WSJCppCore
    // TODO check ip reserved range
    return WSJCppGeoIPResult("ipapi.com", sIpAddress, "Not implemented");
}

// ----------------------------------------------------------------------

WSJCppGeoIPResult WSJCppGeoIP::parseResponseIpApiCom(const std::string &sIpAddress, const std::string &sJson) {
    std::string sServiceName = "ip-api.com";
    std::string TAG = "parseResponseIpApiCom";
    std::string sRequestUrl = "ip-api.com/json/" + sIpAddress;
    std::string sCountry;
    std::string sRegionName;
    std::string sCity;
    double nLatitude;
    double nLongitude;
    std::string sStatus = "";

    if (!nlohmann::json::accept(sJson)) {
        WSJCppLog::err(TAG, sRequestUrl + ", Expected json: " + sJson);
        return WSJCppGeoIPResult(sServiceName, sIpAddress, "Expected json");
    }

    nlohmann::json obj = nlohmann::json::parse(sJson);
    
    try {
        sStatus = obj.at("status").get<std::string>();
    } catch (const std::exception &e) {
        std::string sError = sRequestUrl + " -> wrong field 'status' in struct \n" + sJson + "\n" + std::string(e.what()); 
        WSJCppLog::err(TAG, sError);
        return WSJCppGeoIPResult(sServiceName, sIpAddress, sError);
    }

    if (sStatus == "fail") {
        std::string sErrorMessage = "";
        try {
            sErrorMessage = obj.at("message").get<std::string>();
        } catch (const std::exception &e) {
            std::string sError = sRequestUrl + " -> wrong field 'message' in struct \n" + sJson + "\n" + std::string(e.what()); 
            WSJCppLog::err(TAG, sError);
            return WSJCppGeoIPResult(sServiceName, sIpAddress, sError);
        }
        WSJCppLog::err(TAG, sRequestUrl + " -> fail: " + sErrorMessage);
        return WSJCppGeoIPResult(sServiceName, sIpAddress, sErrorMessage);
    }

    try {
        sCountry = obj.at("country").get<std::string>();
    } catch (const std::exception &e) {
        WSJCppLog::err(TAG, sRequestUrl + " -> wrong field 'country' in struct \n" + sJson + "\n" + std::string(e.what()));
        sCountry = "";
    }

    try {
        sRegionName = obj.at("regionName").get<std::string>();
    } catch (const std::exception &e) {
        WSJCppLog::err(TAG, sRequestUrl + " -> wrong field 'regionName' in struct \n" + sJson + "\n" + std::string(e.what()));
        sRegionName = "";
    }

    try {
        sCity = obj.at("city").get<std::string>();
    } catch (const std::exception &e) {
        WSJCppLog::err(TAG, sRequestUrl + " -> wrong field 'city' in struct \n" + sJson + "\n" + std::string(e.what()));
        sCity = "";
    }

    try {
        nLatitude = obj.at("lat").get<double>();
    } catch (const std::exception &e) {
        WSJCppLog::err(TAG, sRequestUrl + " -> wrong field 'lat' in struct \n" + sJson + "\n" + std::string(e.what()));
        nLatitude = 0.0;
    }

    try {
        nLongitude = obj.at("lon").get<double>();
    } catch (const std::exception &e) {
        WSJCppLog::err(TAG, sRequestUrl + " -> wrong field 'lon' in struct \n" + sJson + "\n" + std::string(e.what()));
        nLongitude = 0.0;
    }
    // ok
    return WSJCppGeoIPResult(
        sServiceName, 
        sIpAddress,
        sCountry,
        sRegionName,
        sCity,
        nLatitude,
        nLongitude
    );
}

// ----------------------------------------------------------------------