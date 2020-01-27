# wsjcpp-geoip

[![Build Status](https://api.travis-ci.org/wsjcpp/wsjcpp-geoip.svg?branch=master)](https://travis-ci.org/wsjcpp/wsjcpp-geoip) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp-geoip.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp-geoip) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp-geoip.svg)](https://github.com/wsjcpp/wsjcpp-geoip) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp-geoip.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp-geoip/network/members)

C++. Call request to another services for get location coordinates by IP-address

## Integrate to your c++ project
include files:

    src.wsjcpp/wsjcpp_core/wsjcpp_core.h
    src.wsjcpp/wsjcpp_core/wsjcpp_core.cpp
    src/wsjcpp_geoip.cpp
    src/wsjcpp_geoip.h

or use a wsjcpp: `wsjcpp install https://github.com/wsjcpp/wsjcpp-geoip:master`

## Example code usage:

```
WSJCppGeoIPResult res = WSJCppGeoIP::requestToIpApiCom("1.1.1.1");
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
```

Output:
```
Service Name: ip-api.com
IP Address: 1.1.1.1
Country: Australia
Region Name: New South Wales
City: Sydney
Latitude: -33.8688
Longitude: 151.209
```