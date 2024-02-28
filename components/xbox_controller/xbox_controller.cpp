#ifdef USE_ESP32

#include "xbox_controller.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include "esphome/core/application.h"

namespace esphome
{
    namespace xbox_controller
    {

        static const char *const TAG = "xbox_controller";

        XboxSeriesXControllerESP32_asukiaaa::Core xboxController;

        /* ---------------- public API (derivated) ---------------- */
        void XBOXController::setup()
        {
            global_xbox_controller = this;

            xboxController.begin();

            ESP_LOGW(TAG, "Xbox Controller initilized.");
        }

        void XBOXController::loop()
        {
            xboxController.onLoop();

            if (xboxController.isConnected())
            {
                if (xboxController.isWaitingForFirstNotification())
                {
                    ESP_LOGW(TAG, "Xbox Controller waiting for first notification...");
                }
                else
                {
                    this->setConnected();

                    uint16_t joystickMax = XboxControllerNotificationParser::maxJoy;

                    this->setState("LX Axis", 0, this->lx_axis_change_callback_, (float) xboxController.xboxNotif.joyLHori / joystickMax);
                    this->setState("LY Axis", 1, this->ly_axis_change_callback_, (float) xboxController.xboxNotif.joyLVert / joystickMax);

                    this->setState("RX Axis", 2, this->rx_axis_change_callback_, (float) xboxController.xboxNotif.joyRHori / joystickMax);
                    this->setState("RY Axis", 3, this->ry_axis_change_callback_, (float) xboxController.xboxNotif.joyRVert / joystickMax);

                    uint16_t triggerMax = XboxControllerNotificationParser::maxTrig;

                    this->setState("L Trigger", 4, this->l_trigger_change_callback_, (float) xboxController.xboxNotif.trigLT / triggerMax);
                    this->setState("R Trigger", 5, this->r_trigger_change_callback_, (float) xboxController.xboxNotif.trigRT / triggerMax);
                }
            }
            else
            {
                if (xboxController.getCountFailedConnection() > 2)
                {
                    ESP_LOGW(TAG, "Xbox Controller connection failed. Restarting...");

                    delay(100);  // NOLINT

                    App.safe_reboot();
                }
            }
        }

        /* ---------------- constructors ---------------- */
        XBOXController::XBOXController()
        {
            global_xbox_controller = this;
        }

        void XBOXController::setConnected()
        {
            if (this->connected) {
                return;
            }

            this->connect_callback_.call();
            this->connected = true;
            ESP_LOGI(TAG, "Xbox Controller connected!");
        }

        void XBOXController::setState(std::string name, int index, CallbackManager<void(float)> callback, float value)
        {
            value = floorf(value * 100) / 100;

            if (this->state[index] == value) {
                return;
            }

            this->state[index] = value;
            callback.call(value);
            ESP_LOGD(TAG, "%s changed value to: %0.2f", name.c_str(), value);
        }

        XBOXController *global_xbox_controller; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    } // namespace xbox_controller
} // namespace esphome

#endif