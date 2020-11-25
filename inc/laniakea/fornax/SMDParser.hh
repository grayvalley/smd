#ifndef SMDPARSER_HH
#define SMDPARSER_HH
#include <laniakea/fornax/SMD.hh>
#include <laniakea/fornax/SMDListener.hh>
namespace SMD {
    class SMDParser
    {
    private:
        Message*       m_p_message       = nullptr;
        OrderAdd*      m_p_orderAdd      = nullptr;
        OrderModify*   m_p_orderModify   = nullptr;
        OrderRemove*   m_p_orderRemove   = nullptr;
        OrderExecuted* m_p_orderExecuted = nullptr;
        SMDListener*   m_p_listener      = nullptr;
    public:
        SMDParser() = delete;
        explicit SMDParser(SMDListener* p_listener);
        SMDParser(SMDParser& other) = delete;
        SMDParser& operator=(SMDParser& other) = delete;
        ~SMDParser();
    public:
        void parse(char* buffer, size_t len);
    };
}
#endif //SMDPARSER_HH

