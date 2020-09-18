#ifndef UNIT_TEST_PARSER_IP_API_COM_H
#define UNIT_TEST_PARSER_IP_API_COM_H

#include <wsjcpp_unit_tests.h>

class UnitTestParserIpApiCom : public WsjcppUnitTestBase {
    public:
        UnitTestParserIpApiCom();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;

    private:
        
};

#endif // UNIT_TEST_PARSER_IP_API_COM_H
