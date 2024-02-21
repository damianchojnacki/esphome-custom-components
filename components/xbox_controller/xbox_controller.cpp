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
                    //   uint16_t joystickMax = XboxControllerNotificationParser::maxJoy;
                    //   Serial.print("joyLHori rate: ");
                    //   Serial.println((float)xboxController.xboxNotif.joyLHori / joystickMax);
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
                    ESP.restart();
                }
            }
        }

        /* ---------------- constructors ---------------- */
        XBOXController::XBOXController()
        {
            global_xbox_controller = this;
        }

        void XBOXController::add_connect_callback(std::function<void()> &&callback)
        {
            this->connect_callback_.add(std::move(callback));
        }

        void XBOXController::setConnected()
        {
            if (this->connected) {
                return;
            }

            this->connect_callback_.call();
            this->connected = true;
        }

        XBOXController *global_xbox_controller; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    } // namespace xbox_controller
} // namespace esphome

#endif