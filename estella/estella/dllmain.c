#include <windows.h>

#include "amex/config.h"
#include "amex/amex.h"

#include "hook/process.h"

#include "hooklib/gfx.h"
#include "hooklib/spike.h"
#include "hooklib/config.h"

#include "platform/config.h"
#include "platform/platform.h"

#include "util/dprintf.h"

static LPWSTR CONFIG_FILENAME = L".\\estella.ini";

static HMODULE app_module;
static process_entry_t app_startup;

static DWORD CALLBACK app_pre_startup(void)
{
    HRESULT hr;
    struct platform_config platform_cfg;
    struct amex_config amex_cfg;
    struct gfx_config gfx_cfg;

    dprintf("Project Estella - Segatools for Privileged Fuckers\n");
    dprintf("Copyright (C) DJHACKERS, Matt Bilker, Raki Saionji\n");
    dprintf("--------------------------------------------------\n");
    dprintf("<< You should give money to poor people.          \n");
    dprintf("       The government should've taxed you more. >>\n");
    dprintf("--------------------------------------------------\n");

    platform_config_load(&platform_cfg, CONFIG_FILENAME);
    amex_config_load(&amex_cfg, CONFIG_FILENAME);
    gfx_config_load(&gfx_cfg, CONFIG_FILENAME);

    hr = platform_hook_init(&platform_cfg, "SSSS", "AAV0", app_module);

    if (FAILED(hr)) {
        return hr;
    }

    hr = amex_hook_init(&amex_cfg);

    if (FAILED(hr)) {
        return hr;
    }

    gfx_hook_init(&gfx_cfg);

    spike_hook_init(CONFIG_FILENAME);

    return app_startup();
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    HRESULT hr;

    if (dwReason != DLL_PROCESS_ATTACH) {
        return TRUE;
    }

    app_module = hModule;

    hr = process_hijack_startup(app_pre_startup, &app_startup);

    if (!SUCCEEDED(hr)) {
        dprintf("Failed to hijack process startup: %x\n", (int)hr);
    }

    return SUCCEEDED(hr);
}
