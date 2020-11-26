#include <grayvalley/smd/SMD.hh>

namespace QVT::SMD {
    std::map<std::string, SMD::MESSAGE_TYPE> smd_enum_map = {
            {"A", SMD::MESSAGE_TYPE_ORDER_ADD},
            {"E", SMD::MESSAGE_TYPE_ORDER_EXECUTED},
            {"R", SMD::MESSAGE_TYPE_ORDER_REMOVE},
            {"M", SMD::MESSAGE_TYPE_ORDER_MODIFY}

    };
}

namespace QVT::SMD {
    std::map<std::string, SIDE> map_side_char_enum = {
            {"B", SIDE::B},
            {"S", SIDE::S}
    };
}

namespace QVT::SMD {
    SMD::MESSAGE_TYPE Message::messageType() {
        if(m_body.empty()){
            return MESSAGE_TYPE_EMPTY;
        }
        try{
            auto value = m_body["message-type"].get<std::string>();
            return smd_enum_map.find(value)->second;
        } catch (nlohmann::json::exception& e){
            return MESSAGE_TYPE_INVALID;
        }
    }
}

namespace QVT::SMD {
    void Message::from(char* buffer, size_t len) {
        m_body = nlohmann::json::parse(buffer, buffer + len);
    }
}

namespace QVT::SMD {
    template <typename T>
    T Message::get(std::string key) {
        return m_body[key].get<T>();
    }
}

namespace QVT::SMD {
    void OrderAdd::get(Message* message) {
        OrderId  = message->get<int>("order-id");
        Price    = message->get<int>("price");
        Quantity = message->get<int>("quantity");
        std::string side = message->get<std::string>("side");
        Side = map_side_char_enum.find(side)->second;
    }
}

namespace QVT::SMD {
    void OrderModify::get(Message* message) {
        OrderId  = message->get<int>("order-id");
        Price    = message->get<int>("price");
        Quantity = message->get<int>("quantity");
        std::string side = message->get<std::string>("side");
        Side = map_side_char_enum.find(side)->second;
    }
}

namespace QVT::SMD {
    void OrderRemove::get(Message* message) {
        OrderId  = message->get<int>("order-id");
    }
}

namespace QVT::SMD {
    void OrderExecuted::get(Message* message) {
        OrderId  = message->get<int>("order-id");
        Price    = message->get<int>("price");
        Quantity = message->get<int>("quantity");
    }
}

namespace QVT::SMD {
    std::ostream &operator<<(std::ostream& s, const OrderAdd& instance) {
        s << " --- [OrderAdd] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "Price: " << instance.Price << std::endl;
        s << "Quantity: " << instance.Quantity << std::endl;
        return s;
    }
}

namespace QVT::SMD {
    std::ostream &operator<<(std::ostream& s, const OrderModify& instance) {
        s << " --- [OrderModify] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "Price: " << instance.Price << std::endl;
        s << "Quantity: " << instance.Quantity << std::endl;
        return s;
    }
}

namespace QVT::SMD {
    std::ostream &operator<<(std::ostream& s, const OrderRemove& instance) {
        s << " --- [OrderRemove] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        return s;
    }
}

namespace QVT::SMD {
    std::ostream &operator<<(std::ostream& s, const OrderExecuted& instance) {
        s << " --- [OrderExecuted] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "Price: " << instance.Price << std::endl;
        s << "Quantity: " << instance.Quantity << std::endl;
        return s;
    }
}