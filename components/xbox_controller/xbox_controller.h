#pragma once

//#ifdef USE_ESP32

#include "XboxSeriesXControllerESP32_asukiaaa/src/XboxSeriesXControllerESP32_asukiaaa.hpp"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"
#include "esphome/core/entity_base.h"
#include "esphome/core/helpers.h"

namespace esphome
{
    namespace xbox_controller
    {
        class XBOXController;

        /* ---------------- XBOXController class ---------------- */
        class XBOXController : public Component, public EntityBase
        {
            public:
                XBOXController();

                /* public API (derivated) */
                void setup() override;
                void loop() override;
                /* public API (specific) */
                void setConnected();

                void add_connect_callback(std::function<void()> &&callback);

            protected:
                bool connected = false;
        };

        // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
        extern XBOXController *global_xbox_controller;

        class XBOXControllerConnectTrigger : public Trigger<>
        {
        public:
            explicit XBOXControllerConnectTrigger(XBOXController *parent)
            {
                parent->add_connect_callback([this]()
                                             { this->trigger(); });
            }

        protected:
        };

    } // namespace xbox_controller
} // namespace esphome

#endif