#ifndef SMDCLIENT_HH
#define SMDCLIENT_HH
#include <string>
#include <functional>
#include <laniakea/virgo/epolling.hh>
#include <laniakea/virgo/fragment.hh>
#include "SMD.hh"
#include "SMDParser.hh"
#include "RFC6455.hh"

namespace RFC6455{
    class Frame;
}

namespace SMD {
    class SMDClient : public Epollable {
    private:
        RFC6455::Session m_session;
        SMDParser* m_p_parser;
    public:
        SMDClient() = delete;
        PREVENT_COPY(SMDClient);
    public:
        explicit SMDClient(SMDParser* p_parser);
        ~SMDClient();
    private:
        void recv(Epoller* p_epoller) override;
        void read();
        void read_handshake_response();
        void read_websocket_frame();
        void send(const FragmentView& fragment);
    public:
        void connect(const RFC6455::Session& session);
        void open();
    };
}
#endif //SMDCLIENT_HH
