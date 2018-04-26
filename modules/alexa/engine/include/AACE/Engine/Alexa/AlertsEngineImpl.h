/*
 * Copyright 2017-2018 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef AACE_ENGINE_ALEXA_ALERTS_ENGINE_IMPL_H
#define AACE_ENGINE_ALEXA_ALERTS_ENGINE_IMPL_H

#include <memory>
#include <string>

#include <ACL/AVSConnectionManager.h>
#include <Audio/AudioFactory.h>
#include <AVSCommon/AVS/Attachment/AttachmentManagerInterface.h>
#include <AVSCommon/SDKInterfaces/Audio/AlertsAudioFactoryInterface.h>
#include <AVSCommon/SDKInterfaces/ContextManagerInterface.h>
#include <AVSCommon/SDKInterfaces/DirectiveSequencerInterface.h>
#include <AVSCommon/SDKInterfaces/ExceptionEncounteredSenderInterface.h>
#include <AVSCommon/SDKInterfaces/FocusManagerInterface.h>
#include <AVSCommon/SDKInterfaces/MessageSenderInterface.h>
#include <Alerts/AlertsCapabilityAgent.h>
#include <Alerts/Storage/SQLiteAlertStorage.h>
#include <ContextManager/ContextManager.h>

#include "AACE/Alexa/AlexaEngineInterfaces.h"
#include "AACE/Alexa/Alerts.h"
#include "AudioChannelEngineImpl.h"

namespace aace {
namespace engine {
namespace alexa {

class AlertsEngineImpl :
    public AudioChannelEngineImpl,
    public aace::alexa::AlertsEngineInterface,
    public alexaClientSDK::capabilityAgents::alerts::AlertObserverInterface,
    public alexaClientSDK::avsCommon::utils::RequiresShutdown {
    
private:
    AlertsEngineImpl( std::shared_ptr<aace::alexa::Alerts> alertsPlatformInterface );

public:
    static std::shared_ptr<AlertsEngineImpl> create(
        std::shared_ptr<aace::alexa::Alerts> alertsPlatformInterface,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::DirectiveSequencerInterface> directiveSequencer,
        std::shared_ptr<alexaClientSDK::acl::AVSConnectionManager> connectionManager,
        std::shared_ptr<alexaClientSDK::certifiedSender::CertifiedSender> certifiedSender,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::FocusManagerInterface> focusManager,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ContextManagerInterface> contextManager,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExceptionEncounteredSenderInterface> exceptionSender,
        std::shared_ptr<alexaClientSDK::avsCommon::sdkInterfaces::audio::AlertsAudioFactoryInterface> alertsAudioFactory );

    // AlertsEngineInterface
    void onLocalStop() override;
    void removeAllAlerts() override;
    
    // AlertObserverInterface
    void onAlertStateChange( const std::string & alertToken, State state, const std::string & reason ) override;

protected:
    virtual void doShutdown() override;

private:
    std::shared_ptr<aace::alexa::Alerts> m_alertsPlatformInterface;
    
    std::shared_ptr<alexaClientSDK::capabilityAgents::alerts::AlertsCapabilityAgent> m_alertsCapabilityAgent;
};

} // aace::engine::alexa
} // aace::engine
} // aace

#endif // AACE_ENGINE_ALEXA_ALERTS_ENGINE_IMPL_H
