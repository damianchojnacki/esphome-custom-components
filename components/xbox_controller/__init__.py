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

CONF_ON_CONNECT = "on_connect"

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
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await setup_entity(var, config)
    await cg.register_component(var, config)

    for conf in config.get(CONF_ON_CONNECT, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(trigger, [], conf)

    cg.add_library(
        None,
        None,
        "https://github.com/asukiaaa/arduino-XboxSeriesXControllerESP32.git",
    )