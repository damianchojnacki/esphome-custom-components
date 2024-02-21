#ifdef USE_ESP32

#include "xbox_controller.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

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

                    this->setState("X Axis", 0, this->lx_axis_change_callback_, floorf(((float) xboxController.xboxNotif.joyLHori / joystickMax) * 100) / 100);
                    //   Serial.print("joyLVert rate: ");
                    //   Serial.println((float)xboxController.xboxNotif.joyLVert / joystickMax);
                    //   Serial.print("trigLT rate: ");
                    //   Serial.println(xboxController.xboxNotif.trigLT);
                    //   Serial.print("trigRT rate: ");
                    //   Serial.println(xboxController.xboxNotif.trigRT);
                }
            }
            else
            {
                if (xboxController.getCountFailedConnection() > 2)
                {
                    ESP_LOGW(TAG, "Xbox Controller connection failed. Restarting...");
                    ESP.restart();
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
            if (this->state[index] == value) {
                return;
            }

            this->state[index] = value;
            callback.call(value);
            ESP_LOGD(TAG, "%s changed value to: %0.2f", name, value);
        }

        XBOXController *global_xbox_controller; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    } // namespace xbox_controller
} // namespace esphome

#endif