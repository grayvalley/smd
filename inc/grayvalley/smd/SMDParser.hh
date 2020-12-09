#ifndef _SMDPARSER_HH
#define _SMDPARSER_HH
#include <grayvalley/smd/SMD.hh>
#include <grayvalley/smd/SMDListener.hh>
namespace GVT {
    class SMDParser
    {
    private:

        SMD::Message* m_p_message = nullptr;

        SMD::OrderAddMessage* m_p_orderAdd = nullptr;

        SMD::OrderModifyMessage* m_p_orderModify = nullptr;

        SMD::OrderRemoveMessage* m_p_orderRemove = nullptr;

        SMD::TradeMessage* m_p_Trade = nullptr;

        SMDListener* m_p_listener = nullptr;

    public:

        SMDParser() = delete;

        explicit SMDParser(GVT::SMDListener* p_listener);

        ~SMDParser();

        SMDParser(GVT::SMDParser& other) = delete;

        SMDParser& operator=(GVT::SMDParser& other) = delete;

    public:

        void parse(char* buffer, size_t len);
    };
}
#endif //_SMDPARSER_HH

