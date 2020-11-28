#ifndef _SMDLISTENER_HH
#define _SMDLISTENER_HH
#include <grayvalley/smd/SMD.hh>
namespace GVT {
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
            virtual void onTrade(Trade* p_message) = 0;
        };
    }
}
#endif //_SMDLISTENER_HH
