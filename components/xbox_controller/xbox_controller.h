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
            void setState(std::string name, int index, CallbackManager<void(float)> callback, float value);

            void add_connect_callback(std::function<void()> &&callback) {
                this->connect_callback_.add(std::move(callback));
            }

            void add_lx_axis_change_callback(std::function<void(float)> &&callback)
            {
                this->lx_axis_change_callback_.add(std::move(callback));
            }

            void add_ly_axis_change_callback(std::function<void(float)> &&callback)
            {
                this->ly_axis_change_callback_.add(std::move(callback));
            }

            void add_rx_axis_change_callback(std::function<void(float)> &&callback)
            {
                this->rx_axis_change_callback_.add(std::move(callback));
            }

            void add_ry_axis_change_callback(std::function<void(float)> &&callback)
            {
                this->ry_axis_change_callback_.add(std::move(callback));
            }

            void add_l_trigger_change_callback(std::function<void(float)> &&callback)
            {
                this->l_trigger_change_callback_.add(std::move(callback));
            }

            void add_r_trigger_change_callback(std::function<void(float)> &&callback)
            {
                this->r_trigger_change_callback_.add(std::move(callback));
            }
        protected:
            bool connected = false;
            float state[6];
            CallbackManager<void()> connect_callback_{};
            CallbackManager<void(float)> lx_axis_change_callback_{};
            CallbackManager<void(float)> ly_axis_change_callback_{};
            CallbackManager<void(float)> rx_axis_change_callback_{};
            CallbackManager<void(float)> ry_axis_change_callback_{};
            CallbackManager<void(float)> l_trigger_change_callback_{};
            CallbackManager<void(float)> r_trigger_change_callback_{};
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

        class XBOXControllerLXAxisChangeTrigger : public Trigger<float>
        {
            public:
                explicit XBOXControllerLXAxisChangeTrigger(XBOXController *parent)
                {
                    parent->add_lx_axis_change_callback([this](float x)
                                                { this->trigger(x); });
                }
        };

        class XBOXControllerLYAxisChangeTrigger : public Trigger<float>
        {
            public:
                explicit XBOXControllerLYAxisChangeTrigger(XBOXController *parent)
                {
                    parent->add_ly_axis_change_callback([this](float x)
                                                { this->trigger(x); });
                }
        };

        class XBOXControllerRXAxisChangeTrigger : public Trigger<float>
        {
            public:
                explicit XBOXControllerRXAxisChangeTrigger(XBOXController *parent)
                {
                    parent->add_rx_axis_change_callback([this](float x)
                                                { this->trigger(x); });
                }
        };

        class XBOXControllerRYAxisChangeTrigger : public Trigger<float>
        {
            public:
                explicit XBOXControllerRYAxisChangeTrigger(XBOXController *parent)
                {
                    parent->add_ry_axis_change_callback([this](float x)
                                                { this->trigger(x); });
                }
        };

        class XBOXControllerLTriggerChangeTrigger : public Trigger<float>
        {
            public:
                explicit XBOXControllerLTriggerChangeTrigger(XBOXController *parent)
                {
                    parent->add_l_trigger_change_callback([this](float x)
                                                { this->trigger(x); });
                }
        };

        class XBOXControllerRTriggerChangeTrigger : public Trigger<float>
        {
            public:
                explicit XBOXControllerRTriggerChangeTrigger(XBOXController *parent)
                {
                    parent->add_r_trigger_change_callback([this](float x)
                                                { this->trigger(x); });
                }
        };

    } // namespace xbox_controller
} // namespace esphome

#endif