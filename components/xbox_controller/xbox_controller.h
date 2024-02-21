#pragma once

#ifdef USE_ESP32

#include "esphome/core/automation.h"
#include "esphome/core/component.h"
#include "esphome/core/entity_base.h"
#include "esphome/core/helpers.h"

#include <XboxSeriesXControllerESP32_asukiaaa.hpp>

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
            void setXAxis(float value);

            void add_connect_callback(std::function<void()> &&callback) {
                this->connect_callback_.add(std::move(callback));
            }

            void add_x_axis_change_callback(std::function<void(float)> &&callback)
            {
                this->x_axis_change_callback_.add(std::move(callback));
            }
        protected:
            bool connected = false;
            float x_axis = 0.5;
            CallbackManager<void()> connect_callback_{};
            CallbackManager<void(float)> x_axis_change_callback_{};
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
        };

        class XBOXControllerXAxisChangeTrigger : public Trigger<>
        {
            public:
                explicit XBOXControllerXAxisChangeTrigger(XBOXController *parent)
                {
                    parent->add_x_axis_change_callback([this](float value)
                                                { this->trigger(value); });
                }
        };

    } // namespace xbox_controller
} // namespace esphome

#endif