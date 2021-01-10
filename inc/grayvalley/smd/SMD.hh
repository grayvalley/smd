#ifndef _SMD_HH
#define _SMD_HH
#include <nlohmann/json.hpp>
#include <grayvalley/core/Engine.hh>
#include <grayvalley/core/macros.hh>
#include <grayvalley/core/enums.hh>
#include <grayvalley/core/Events.hh>
#include <grayvalley/core/Messages.hh>

namespace GVT::SMD {
    enum MESSAGE_TYPE: int {
        MESSAGE_TYPE_EMPTY,
        MESSAGE_TYPE_INVALID,
        MESSAGE_TYPE_ORDER_ADD,
        MESSAGE_TYPE_TRADE,
        MESSAGE_TYPE_ORDER_REMOVE,
        MESSAGE_TYPE_ORDER_MODIFY
    };
}


namespace GVT::SMD {

    class Message: public IMessage {

    public:

        Message() = default;

        PREVENT_COPY(Message);

    public:

        /**
         * Populates the body of the message from a buffer
         *
         * @param buffer: pointer to the beginning of a buffer
         * @param len: length of the message
         */
        void from(char* buffer, size_t len) override;

        /**
         * Return type id of the message
         *
         * @return: integer id
         */
        [[nodiscard]] int type() const override;

        /**
         * Get value from a key
         *
         * @tparam T: desired output type
         * @param key: string key
         *
         * @return: value
         */
        template<typename T>
        T get(std::string key);

        /**
         * Print the message
         */
        void dump();

    protected:

        nlohmann::json m_body;

    };
}


namespace GVT::SMD {

    class OrderAddMessage: public IOrderAddMessage, public IInboundMessage {
    public:
        uint64_t Snapshot = false;
    public:
        OrderAddMessage() = default;
        PREVENT_COPY(OrderAddMessage);
    public:
        void get(IMessage* p_imessage) override;
        void put(IOrderBookEvent* p_event) override;
        friend std::ostream &operator<<(std::ostream& s, const OrderAddMessage& instance);
    };
}

namespace GVT::SMD {
    class OrderModifyMessage: public IOrderModifyMessage, public IInboundMessage {
    public:
        OrderModifyMessage() = default;
        PREVENT_COPY(OrderModifyMessage);
    public:
        void get(IMessage* message) override;
        void put(IOrderBookEvent* p_event) override;
        friend std::ostream &operator<<(std::ostream& s, const OrderModifyMessage& instance);
    };
}

namespace GVT::SMD {
    class OrderRemoveMessage: public IOrderRemoveMessage, public IInboundMessage {
    public:
        OrderRemoveMessage() = default;
        PREVENT_COPY(OrderRemoveMessage);
    public:
        void get(IMessage* message) override;
        void put(IOrderBookEvent* p_event) override;

        friend std::ostream &operator<<(std::ostream& s, const OrderRemoveMessage& instance);
    };
}

namespace GVT::SMD {
    class TradeMessage: public ITradeMessage, public IInboundMessage {
    public:
        TradeMessage() = default;
        PREVENT_COPY(TradeMessage);
    public:
        void get(IMessage* message) override;
        void put(ITradeEvent* p_event) override;
        friend std::ostream &operator<<(std::ostream& s, const TradeMessage& instance);
    };
}
#endif //SMD_HH
