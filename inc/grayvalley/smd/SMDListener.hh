#ifndef GVT_SMDLISTENER_HH
#define GVT_SMDLISTENER_HH

#include <grayvalley/smd/SMD.hh>

namespace GVT {

    class SMDListener {

    public:

        SMDListener() = default;

        virtual ~SMDListener()= default;

        SMDListener(SMDListener& other) = delete;

        SMDListener& operator=(SMDListener& other) = delete;

    public:

        /**
         * Invoked when SMD::OrderAddMessage is received
         *
         * @param p_message: pointer to SMD::OrderAddMessage
         */
        virtual void on_order_add_message(SMD::OrderAddMessage* p_message) = 0;

        /**
         * Invoked when SMD::OrderRemoveMessage is received
         *
         * @param p_message: pointer to SMD::OrderRemoveMessage
         */
        virtual void on_order_remove_message(SMD::OrderRemoveMessage* p_message) = 0;

        /**
         * Invoked when SMD::OrderModifyMessage is received
         *
         * @param p_message: pointer to SMD::OrderModifyMessage
         */
        virtual void on_order_modify_message(SMD::OrderModifyMessage* p_message) = 0;

        /**
         * Invoked when SMD::TradeMessage is received
         *
         * @param p_message: pointer to SMD::TradeMessage
         */
        virtual void on_trade_message(SMD::TradeMessage* p_message) = 0;

    };
}
#endif //GVT_SMDLISTENER_HH
