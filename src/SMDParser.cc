#include <iostream>
#include <grayvalley/smd/SMDParser.hh>

namespace GVT {
    SMDParser::SMDParser(SMDListener* p_listener) {
        m_p_listener      = p_listener;
        m_p_message       = new SMD::Message();
        m_p_orderAdd      = new SMD::OrderAddMessage();
        m_p_orderRemove   = new SMD::OrderRemoveMessage();
        m_p_orderModify   = new SMD::OrderModifyMessage();
        m_p_Trade         = new SMD::TradeMessage();
    }
}

namespace GVT {
    SMDParser::~SMDParser() {
        delete m_p_orderAdd;
        delete m_p_orderRemove;
        delete m_p_orderModify;
        delete m_p_Trade;
        delete m_p_listener;
    }
}

namespace GVT {
    void SMDParser::parse(char* buffer, size_t len) {
        m_p_message->from(buffer, len);
        int type = m_p_message->type();
        switch (type)
        {
            case SMD::MESSAGE_TYPE_EMPTY: {
                return;
            }
            case SMD::MESSAGE_TYPE_INVALID: {
                return;
            }
            case SMD::MESSAGE_TYPE_ORDER_ADD: {
                m_p_orderAdd->get(m_p_message);
                m_p_listener->on_order_add_message(m_p_orderAdd);
                break;
            }
            case SMD::MESSAGE_TYPE_TRADE: {
                m_p_Trade->get(m_p_message);
                m_p_listener->on_trade_message(m_p_Trade);
                break;
            }
            case SMD::MESSAGE_TYPE_ORDER_REMOVE: {
                m_p_orderRemove->get(m_p_message);
                m_p_listener->on_order_remove_message(m_p_orderRemove);
                break;
            }
            case SMD::MESSAGE_TYPE_ORDER_MODIFY: {
                m_p_orderModify->get(m_p_message);
                m_p_listener->on_order_modify_message(m_p_orderModify);
                break;
            }
        }
    }
}
