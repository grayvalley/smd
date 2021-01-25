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
#ifndef GVT_SMD_SUBSCRIPTION_HH
#define GVT_SMD_SUBSCRIPTION_HH

#include <nlohmann/json.hpp>

#include <grayvalley/core/Macros.hh>
#include <grayvalley/core/ISubscription.hh>

namespace GVT::SMD {

    class SMDSubscription: public ISubscription {

    public:

        /**
         * Generate SMD style subscription string.
         *
         * @return: subscription string.
         */
        std::string generate_payload() const override;


    };

}

namespace GVT::SMD {
    std::string SMDSubscription::generate_payload() const {

        if (empty()){
            throw std::runtime_error("Subscription was empty!");
        }

        nlohmann::json payload = {{"op", "subscribe"}};
        auto args = nlohmann::json::array();
        for(auto item: m_items){
            args.push_back(item);
        }
        payload["args"] = args;
        auto result = payload.dump();

        return result;
    }
}

#endif //GVT_SMD_SUBSCRIPTION_HH
