#ifndef SMDLISTENER_HH
#define SMDLISTENER_HH
#include "SMD.hh"
namespace SMD {
    class SMDListener
    {
    public:
        SMDListener(SMDListener& other) = delete;
        SMDListener& operator=(SMDListener& other) = delete;
    public:
        SMDListener() = default;
        virtual ~SMDListener()= default;
    public:
        virtual void onOrderAdd(OrderAdd* p_message) = 0;
        virtual void onOrderRemove(OrderRemove* p_message) = 0;
        virtual void onOrderModify(OrderModify* p_message) = 0;
        virtual void onOrderExecuted(OrderExecuted* p_message) = 0;
    };
}

#endif //SMDLISTENER_HH
