#ifndef _SMD_HH
#define _SMD_HH

#include <nlohmann/json.hpp>
#include <grayvalley/core/fragment.hh>
#include <grayvalley/core/macros.hh>
#include <grayvalley/core/enums.hh>


namespace SMD {
    enum MESSAGE_TYPE: int {
        MESSAGE_TYPE_EMPTY,
        MESSAGE_TYPE_INVALID,
        MESSAGE_TYPE_ORDER_ADD,
        MESSAGE_TYPE_ORDER_EXECUTED,
        MESSAGE_TYPE_ORDER_REMOVE,
        MESSAGE_TYPE_ORDER_MODIFY
    };
}

namespace SMD {
    class Message {
    protected:
        nlohmann::json m_body;
    public:
        Message() = default;
        PREVENT_COPY(Message);
    public:
        void from(char* buffer, size_t len);
        MESSAGE_TYPE messageType();
        template<typename T>
        T get(std::string key);
    };
}

namespace SMD {
    class InboundMessage {
    public:
        InboundMessage() = default;
        PREVENT_COPY(InboundMessage);
    public:
        virtual void get(Message* message) = 0;
    };
}

namespace SMD {
    class OrderAdd: public InboundMessage {
        int OrderId;
        int Price;
        int Quantity;
        SIDE Side;
    public:
        OrderAdd() = default;
        PREVENT_COPY(OrderAdd);
    public:
        void get(Message* message) override;
        friend std::ostream &operator<<(std::ostream& s, const OrderAdd& instance);
    };
}

namespace SMD {
    class OrderModify: public InboundMessage {
        int OrderId;
        int Price;
        int Quantity;
        SIDE Side;
    public:
        OrderModify() = default;
        PREVENT_COPY(OrderModify);
    public:
        void get(Message* message) override;
        friend std::ostream &operator<<(std::ostream& s, const OrderModify& instance);
    };
}

namespace SMD {
    class OrderRemove: public InboundMessage {
        int OrderId;
    public:
        OrderRemove() = default;
        PREVENT_COPY(OrderRemove);
    public:
        void get(Message* message) override;
        friend std::ostream &operator<<(std::ostream& s, const OrderRemove& instance);
    };
}

namespace SMD {
    class OrderExecuted: public InboundMessage {
        int OrderId;
        int Price;
        int Quantity;
    public:
        OrderExecuted() = default;
        PREVENT_COPY(OrderExecuted);
    public:
        void get(Message* message) override;
        friend std::ostream &operator<<(std::ostream& s, const OrderExecuted& instance);
    };
}

#endif //SMD_HH
