#include <system_error>
#include <grayvalley/core/Engine.hh>
#include <grayvalley/smd/SMDClient.hh>
#include <grayvalley/core/RFC6455.hh>

namespace GVT::SMD {
    SMDClient::SMDClient(SMDParser* p_parser) {
        m_p_parser = p_parser;
    }
}

namespace GVT::SMD {
    SMDClient::~SMDClient() {
        delete m_p_parser;
    }
}

namespace GVT::SMD {
    void SMDClient::connect(const RFC6455::Session& session) {
        m_session = session;
        fd = fd_create();
        fd_connect(fd, m_session.Host, m_session.Port);
        fd_set_nonblock(fd, true);
    }
}

namespace GVT::SMD {
    void SMDClient::subscribe(const ISubscription &subscription) {
        auto sub = subscription.generate_payload();
        send(StringView::from(sub));
    }
}

namespace GVT::SMD {
    void SMDClient::send(const StringView& fragment) {
        fd_send(fd, fragment.base, fragment.len, MSG_DONTWAIT | MSG_NOSIGNAL);
    }
}

namespace GVT::SMD {
    void SMDClient::recv(Epoller* p_epoller) {
        int n_received = ::recv(fd, buffer, 5*BUFSIZ - used, MSG_DONTWAIT);
        if (n_received > 0) {
            used += n_received;
            read();
        } else if (n_received < 0) {
            return;
        } else if (n_received == 0) {
            p_epoller->remove(fd, true);
        }
    }
}

namespace GVT::SMD {
    void SMDClient::open() {
        m_session.State = RFC6455::CONNECTING;
        auto handshake = m_session.create_handshake();
        send(StringView::from(handshake));
    }
}

namespace GVT::SMD {
    void SMDClient::read_handshake_response(){
        m_session.validate(std::string{buffer, (size_t)(used)});
        clean_buffer();
    }
}

namespace GVT::SMD {
    void SMDClient::read_websocket_frame() {
        bool exhausted = false;
        while (!exhausted) {
            unsigned char scratch[8] = {0};
            unsigned char mb[4] = {0};
            int payload_start = 2;
            if (used < payload_start) {
                return;
            }
            int opcode = buffer[0] & _OPCODE;
            int has_mask = buffer[1] >> 7 & _MASK;
            size_t payload_len = buffer[1] & _PAYLOAD_LEN;
            if (payload_len == 126) {
                payload_start += 2;
                if (used < payload_start) {
                    return;
                };
                memcpy(scratch, buffer + 2, 2);
                payload_len = 0ULL;
                for (int i = 0; i < 2; i++) {
                    payload_len = (payload_len << 8) + scratch[i];
                }
            } else if (payload_len == 127) {
                payload_start += 8;
                if (used < payload_start) {
                    return;
                };
                memcpy(scratch, buffer + 2, 8);
                payload_len = 0ULL;
                for (int i = 0; i < 8; i++) {
                    payload_len = (payload_len << 8) + scratch[i];
                }
            }
            if (has_mask) {
                memcpy(scratch, buffer + payload_start, 4);
                payload_start += 4;
            }
            if (used < payload_len + payload_start) {
                exhausted = true;
                return;
            };
            if (opcode == OPCODE_TEXT) {
                m_p_parser->parse(buffer + payload_start, payload_len);
            }
            used -= payload_start + payload_len;
            if (used < 0) {
                throw std::runtime_error("Error reading buffer.");
            }
            if ((used > 0) && (used <= 5*BUFSIZ)) {
                memmove(buffer, buffer + payload_start + payload_len, used);
            } else {
                used = 0;
                exhausted = true;
            }
        }
    }
}

namespace GVT::SMD {
    void SMDClient::read() {
        switch (m_session.State) {
            case RFC6455::CONNECTING: {
                read_handshake_response();
                break;
            }
            case RFC6455::CONNECTED: {
                read_websocket_frame();
                break;
            }
            case RFC6455::ERROR: {
                throw std::runtime_error("Session error.");
            }
        }
    }
}

