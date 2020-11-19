#pragma once

#include <windows.h>

#include "amex/ds.h"
#include "amex/eeprom.h"
#include "amex/gpio.h"
#include "amex/sram.h"

struct amex_config {
    struct ds_config ds;
    struct eeprom_config eeprom;
    struct gpio_config gpio;
    struct sram_config sram;
};

HRESULT amex_hook_init(const struct amex_config *cfg);
