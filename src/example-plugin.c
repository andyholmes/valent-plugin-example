// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#include <gio/gio.h>
#include <libpeas.h>

#include "example-device-plugin.h"
#include "example-device-preferences-group.h"


G_MODULE_EXPORT void
peas_register_types (PeasObjectModule *module)
{
  example_device_plugin_register_types (module);
  example_device_preferences_group_register_types (module);
}

