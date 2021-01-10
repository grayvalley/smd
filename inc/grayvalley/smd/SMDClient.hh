/*
 * Copyright 2020 Juha-Samuli Hellén
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef GVT_SMD_CLIENT_HH
#define GVT_SMD_CLIENT_HH

#include <grayvalley/core/IWebSocketClient.hh>

#include <grayvalley/smd/SMD.hh>
#include <grayvalley/smd/SMDParser.hh>

namespace GVT::SMD {
    class SMDClient :
            public IWebSocketClient,
            public Epollable
            {
    private:
        RFC6455::Session m_session;
        SMDParser* m_p_parser;
    public:
        SMDClient() = delete;
        PREVENT_COPY(SMDClient);
    public:
        explicit SMDClient(SMDParser* p_parser);
        ~SMDClient();
    private:
        void recv(Epoller* p_epoller) override;
        void read();
        void read_handshake_response();
        void read_websocket_frame();
        void send(const StringView& fragment);
    public:
        void connect(const RFC6455::Session& session) override;
        void open() override;
        void subscribe(const ISubscription& subscription) override;
    };
}
#endif //GVT_SMD_CLIENT_HH
