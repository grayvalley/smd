#include <grayvalley/smd/SMDParser.hh>
#include <iostream>
namespace SMD {
    SMDParser::SMDParser(SMD::SMDListener* p_listener) {
        m_p_listener      = p_listener;
        m_p_message       = new Message();
        m_p_orderAdd      = new OrderAdd();
        m_p_orderRemove   = new OrderRemove();
        m_p_orderModify   = new OrderModify();
        m_p_orderExecuted = new OrderExecuted();
    }
}

namespace SMD {
    SMDParser::~SMDParser() {
        delete m_p_orderAdd;
        delete m_p_orderRemove;
        delete m_p_orderModify;
        delete m_p_orderExecuted;
        delete m_p_listener;
    }
}

namespace SMD {
    void SMDParser::parse(char* buffer, size_t len) {
        m_p_message->from(buffer, len);
        int type = m_p_message->messageType();
        switch (type)
        {
            case MESSAGE_TYPE_EMPTY: {
                return;
            }
            case MESSAGE_TYPE_INVALID: {
                return;
            }
            case MESSAGE_TYPE_ORDER_ADD: {
                m_p_orderAdd->get(m_p_message);
                m_p_listener->onOrderAdd(m_p_orderAdd);
                break;
            }
            case MESSAGE_TYPE_ORDER_EXECUTED: {
                m_p_orderExecuted->get(m_p_message);
                m_p_listener->onOrderExecuted(m_p_orderExecuted);
                break;
            }
            case MESSAGE_TYPE_ORDER_REMOVE: {
                m_p_orderRemove->get(m_p_message);
                m_p_listener->onOrderRemove(m_p_orderRemove);
                break;
            }
            case MESSAGE_TYPE_ORDER_MODIFY: {
                m_p_orderModify->get(m_p_message);
                m_p_listener->onOrderModify(m_p_orderModify);
                break;
            }
        }
    }
}