#include <grayvalley/smd/SMD.hh>

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

namespace GVT::SMD {
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

namespace GVT::SMD {
    void Message::from(char* buffer, size_t len) {
        m_body = nlohmann::json::parse(buffer, buffer + len);
    }
}

namespace GVT::SMD {
    template <typename T>
    T Message::get(std::string key) {
        return m_body[key].get<T>();
    }
}

namespace GVT::SMD {
    void OrderAdd::get(Message* message) {
        OrderId  = message->get<int>("order-id");
        Price    = message->get<int>("price");
        Quantity = message->get<int>("quantity");
        std::string side = message->get<std::string>("side");
        Side = map_side_char_enum.find(side)->second;
        Snapshot = message->get<int>("snapshot");
    }
}

namespace GVT::SMD {
    void OrderModify::get(Message* message) {
        OrderId  = message->get<int>("order-id");
        Price    = message->get<int>("price");
        Quantity = message->get<int>("quantity");
        std::string side = message->get<std::string>("side");
        Side = map_side_char_enum.find(side)->second;
    }
}

namespace GVT::SMD {
    void OrderRemove::get(Message* message) {
        OrderId  = message->get<int>("order-id");
    }
}

namespace GVT::SMD {
    void Trade::get(Message* message) {
        OrderId  = message->get<int>("order-id");
        Price    = message->get<int>("price");
        Quantity = message->get<int>("quantity");
    }
}

namespace GVT::SMD {
    std::ostream &operator<<(std::ostream& s, const OrderAdd& instance) {
        s << " --- [OrderAdd] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "Price: " << instance.Price << std::endl;
        s << "Quantity: " << instance.Quantity << std::endl;
        return s;
    }
}

namespace GVT::SMD {
    std::ostream &operator<<(std::ostream& s, const OrderModify& instance) {
        s << " --- [OrderModify] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "Price: " << instance.Price << std::endl;
        s << "Quantity: " << instance.Quantity << std::endl;
        return s;
    }
}

namespace GVT::SMD {
    std::ostream &operator<<(std::ostream& s, const OrderRemove& instance) {
        s << " --- [OrderRemove] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        return s;
    }
}

namespace GVT::SMD {
    std::ostream &operator<<(std::ostream& s, const Trade& instance) {
        s << " --- [Trade] ---" << std::endl;
        s << "OrderId: " << instance.OrderId << std::endl;
        s << "Price: " << instance.Price << std::endl;
        s << "Quantity: " << instance.Quantity << std::endl;
        return s;
    }
}