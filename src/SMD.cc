#include <grayvalley/smd/SMD.hh>
#include <grayvalley/core/Events.hh>

namespace GVT::SMD {
    std::map<std::string, SMD::MESSAGE_TYPE> smd_enum_map = {
            {"A", SMD::MESSAGE_TYPE_ORDER_ADD},
            {"E", SMD::MESSAGE_TYPE_TRADE},
            {"X", SMD::MESSAGE_TYPE_ORDER_REMOVE},
            {"M", SMD::MESSAGE_TYPE_ORDER_MODIFY}

    };
}

namespace GVT::SMD {
    std::map<std::string, SIDE> map_side_char_enum = {
            {"B", SIDE::B},
            {"S", SIDE::S}
    };
}

/**
 * Populates the body of the message from a buffer
 *
 * @param buffer: pointer to the beginning of a buffer
 * @param len: length of the message
 */
namespace GVT::SMD {
    void Message::from(char* buffer, size_t len) {
        m_body = nlohmann::json::parse(buffer, buffer + len);
    }
}

/**
 * Return type id of the message
 *
 * @return: integer id
 */
namespace GVT::SMD {
    int Message::type() const {

        if(m_body.empty()){
            return MESSAGE_TYPE_EMPTY;
        }

        try {
            auto type_char = m_body["message-type"].get<std::string>();
            if(smd_enum_map.find(type_char) == smd_enum_map.end()){
                throw std::runtime_error("Message type not understood!");
            }
            return smd_enum_map[type_char];
        } catch (nlohmann::json::exception& e) {
            return MESSAGE_TYPE_INVALID;
        }
    }
}

/**
 * Return an item from the message body
 */
namespace GVT::SMD {
    template <typename T>
    T Message::get(std::string key) {
        return m_body[key].get<T>();
    }
}

namespace GVT::SMD {
    void Message::dump(){
        std::cout << m_body.dump() << std::endl;
    }
}

/**
 * Populate SMD::OrderAddMessage from SMD::Message
 */
namespace GVT::SMD {
    void OrderAddMessage::get(IMessage* p_imessage) {
        auto* p_message = reinterpret_cast<GVT::SMD::Message*>(p_imessage);
        Exchange = "sandbox";
        Instrument =  p_message->get<int>("instrument");
        OrderId  = p_message->get<int>("order-id");
        Price = p_message->get<int>("price");
        Quantity = p_message->get<int>("quantity");
        auto side = p_message->get<std::string>("side");
        Side = map_side_char_enum.find(side)->second;
        Snapshot = p_message->get<int>("snapshot");
    }
}

/**
 * Create OrderBookEvent from SMD::OrderAddMessage
 */
namespace GVT::SMD {
    void OrderAddMessage::put(IOrderBookEvent *p_event) {
        p_event->type = IOrderBookEvent::EVENT_TYPE::ADD;
        p_event->order_id = OrderId;
    }
}

/**
 * Populate SMD::OrderAddMessage from SMD::Message
 */
namespace GVT::SMD {
    void OrderModifyMessage::get(IMessage* p_imessage) {
        auto* p_message = reinterpret_cast<GVT::SMD::Message*>(p_imessage);
        Exchange = "sandbox";
        Instrument = p_message->get<int>("instrument");
        OrderId  = p_message->get<int>("order-id");
        Price = p_message->get<int>("price");
        Quantity = p_message->get<int>("quantity");
        auto side = p_message->get<std::string>("side");
        Side = map_side_char_enum.find(side)->second;
    }
}

namespace GVT::SMD {
    void OrderModifyMessage::put(IOrderBookEvent *p_event) {
        p_event->type = IOrderBookEvent::EVENT_TYPE::MODIFY;
        p_event->order_id = OrderId;
    }
}

namespace GVT::SMD {
    void OrderRemoveMessage::get(IMessage* p_imessage) {
        auto* p_message = reinterpret_cast<GVT::SMD::Message*>(p_imessage);
        Exchange = "sandbox";
        Instrument = p_message->get<int>("instrument");
        OrderId = p_message->get<int>("order-id");
    }
}

namespace GVT::SMD {
    void OrderRemoveMessage::put(IOrderBookEvent *p_event) {
        p_event->type = IOrderBookEvent::EVENT_TYPE::REMOVE;
        p_event->order_id = OrderId;
    }
}

namespace GVT::SMD {
    void TradeMessage::get(IMessage* p_imessage) {
        auto* p_message = reinterpret_cast<GVT::SMD::Message*>(p_imessage);
        Exchange = "sandbox";
        Instrument = p_message->get<int>("instrument");
        OrderId = p_message->get<int>("order-id");
        Price = p_message->get<int>("price");
        Quantity = p_message->get<int>("quantity");
    }
}

namespace GVT::SMD {
    void TradeMessage::put(ITradeEvent* p_event){
        p_event->Exchange = "sandbox";
        p_event->Instrument = Instrument;
        p_event->OrderId = OrderId;
        p_event->Price = Price;
        p_event->Quantity = Quantity;
        p_event->Side = Side;
    }
}

namespace GVT::SMD {
    std::ostream &operator<<(std::ostream& s, const OrderAddMessage& instance) {
        s << " --- [OrderAdd] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "Price: " << instance.Price << std::endl;
        s << "Quantity: " << instance.Quantity << std::endl;
        return s;
    }
}

namespace GVT::SMD {
    std::ostream &operator<<(std::ostream& s, const OrderModifyMessage& instance) {
        s << " --- [OrderModify] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "Price: " << instance.Price << std::endl;
        s << "Quantity: " << instance.Quantity << std::endl;
        return s;
    }
}

namespace GVT::SMD {
    std::ostream &operator<<(std::ostream& s, const OrderRemoveMessage& instance) {
        s << " --- [OrderRemove] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        return s;
    }
}

namespace GVT::SMD {
    std::ostream &operator<<(std::ostream& s, const TradeMessage& instance) {
        s << " --- [Trade] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "Price: " << instance.Price << std::endl;
        s << "Quantity: " << instance.Quantity << std::endl;
        return s;
    }
}