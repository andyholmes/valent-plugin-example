// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#include <gio/gio.h>
#include <libpeas/peas.h>

#include "example-device-plugin.h"
#include "example-device-preferences-page.h"


G_MODULE_EXPORT void
peas_register_types (PeasObjectModule *module)
{
  example_device_plugin_register_types (module);
  example_device_preferences_page_register_types (module);
}

