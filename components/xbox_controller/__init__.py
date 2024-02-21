import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.const import (
    CONF_ID,
    CONF_TRIGGER_ID,
)
from esphome.cpp_helpers import setup_entity

DEPENDENCIES = ["esp32"]

xbox_controller_ns = cg.esphome_ns.namespace("xbox_controller")
XBOXController = xbox_controller_ns.class_("XBOXController", cg.PollingComponent, cg.EntityBase)

XBOXControllerConnectTrigger = xbox_controller_ns.class_(
    "XBOXControllerConnectTrigger",
    automation.Trigger.template(),
)

XBOXControllerLXAxisChangeTrigger = xbox_controller_ns.class_(
    "XBOXControllerLXAxisChangeTrigger",
    automation.Trigger.template(float),
)

XBOXControllerLYAxisChangeTrigger = xbox_controller_ns.class_(
    "XBOXControllerLYAxisChangeTrigger",
    automation.Trigger.template(float),
)

XBOXControllerRXAxisChangeTrigger = xbox_controller_ns.class_(
    "XBOXControllerRXAxisChangeTrigger",
    automation.Trigger.template(float),
)

XBOXControllerRYAxisChangeTrigger = xbox_controller_ns.class_(
    "XBOXControllerRYAxisChangeTrigger",
    automation.Trigger.template(float),
)

XBOXControllerLTriggerChangeTrigger = xbox_controller_ns.class_(
    "XBOXControllerLTriggerChangeTrigger",
    automation.Trigger.template(float),
)

XBOXControllerRTriggerChangeTrigger = xbox_controller_ns.class_(
    "XBOXControllerRTriggerChangeTrigger",
    automation.Trigger.template(float),
)

CONF_ON_CONNECT = "on_connect"
CONF_ON_LX_AXIS_CHANGE = "on_l_x_axis_change"
CONF_ON_LY_AXIS_CHANGE = "on_l_y_axis_change"
CONF_ON_RX_AXIS_CHANGE = "on_r_x_axis_change"
CONF_ON_RY_AXIS_CHANGE = "on_r_y_axis_change"
CONF_ON_L_TRIGGER_CHANGE = "on_l_trigger_change"
CONF_ON_R_TRIGGER_CHANGE = "on_r_trigger_change"

CONFIG_SCHEMA = cv.ENTITY_BASE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(XBOXController),
        cv.Optional(CONF_ON_CONNECT): automation.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(
                    XBOXControllerConnectTrigger
                ),
            }
        ),
        cv.Optional(CONF_ON_LX_AXIS_CHANGE): automation.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(
                    XBOXControllerLXAxisChangeTrigger
                ),
            }
        ),
        cv.Optional(CONF_ON_LY_AXIS_CHANGE): automation.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(
                    XBOXControllerLYAxisChangeTrigger
                ),
            }
        ),
           cv.Optional(CONF_ON_RX_AXIS_CHANGE): automation.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(
                    XBOXControllerRXAxisChangeTrigger
                ),
            }
        ),
        cv.Optional(CONF_ON_RY_AXIS_CHANGE): automation.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(
                    XBOXControllerRYAxisChangeTrigger
                ),
            }
        ),
        cv.Optional(CONF_ON_L_TRIGGER_CHANGE): automation.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(
                    XBOXControllerLTriggerChangeTrigger
                ),
            }
        ),
        cv.Optional(CONF_ON_R_TRIGGER_CHANGE): automation.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(
                    XBOXControllerRTriggerChangeTrigger
                ),
            }
        ),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await setup_entity(var, config)
    await cg.register_component(var, config)

    for conf in config.get(CONF_ON_CONNECT, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(trigger, [], conf)
    
    for conf in config.get(CONF_ON_LX_AXIS_CHANGE, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(trigger, [(float, "x")], conf)
    
    for conf in config.get(CONF_ON_LY_AXIS_CHANGE, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(trigger, [(float, "x")], conf)

    for conf in config.get(CONF_ON_RX_AXIS_CHANGE, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(trigger, [(float, "x")], conf)
    
    for conf in config.get(CONF_ON_RY_AXIS_CHANGE, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(trigger, [(float, "x")], conf)

    for conf in config.get(CONF_ON_L_TRIGGER_CHANGE, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(trigger, [(float, "x")], conf)

    for conf in config.get(CONF_ON_R_TRIGGER_CHANGE, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(trigger, [(float, "x")], conf)

    cg.add_library(
        None,
        None,
        "https://github.com/asukiaaa/arduino-XboxControllerNotificationParser.git",
    )

    cg.add_library(
        None,
        None,
        "https://github.com/h2zero/NimBLE-Arduino.git",
    )

    cg.add_library(
        None,
        None,
        "https://github.com/asukiaaa/arduino-XboxSeriesXHIDReportBuilder.git",
    )

    cg.add_library(
        None,
        None,
        "https://github.com/asukiaaa/arduino-XboxSeriesXControllerESP32.git",
    )