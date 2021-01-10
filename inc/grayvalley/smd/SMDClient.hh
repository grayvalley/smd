#ifndef GVT_SMD_CLIENT_HH
#define GVT_SMD_CLIENT_HH
#include <string>
#include <functional>
#include <vector>
#include <algorithm>
#include <grayvalley/core/Engine.hh>
#include <grayvalley/smd/SMD.hh>
#include <grayvalley/smd/SMDParser.hh>
#include <grayvalley/core/RFC6455.hh>

namespace RFC6455{
    class Frame;
}

namespace GVT {
    class Subscription {
    public:
        Subscription() = default;
        PREVENT_COPY(Subscription);
    public:

        /**
         * Add subscription item to subscription
         *
         * @param item: item representing <DataItem>:<Istrument>
         */
        void add_item(const std::string& item){
            if (item_exists(item)){
                return;
            }
            items.push_back(item);
        }

    private:
        /**
         * Return true if data item exists in the current subscription
         * @param item
         * @return
         */
        bool item_exists(const std::string& item){
            if (std::find(items.begin(), items.end(), item) != items.end()){
                return true;
            }
            return false;
        }

    public:

        /**
         * Vector containing subscribed data items
         */
        std::vector<std::string> items;
    };
}

namespace GVT::SMD {
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
        void send(const StringView& fragment);
    public:
        void connect(const RFC6455::Session& session);
        void open();
        void subscribe(const Subscription& subscription);
    };
}
#endif //GVT_SMD_CLIENT_HH
