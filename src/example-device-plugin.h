// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#pragma once

#include <valent.h>

G_BEGIN_DECLS

#define EXAMPLE_TYPE_DEVICE_PLUGIN (example_device_plugin_get_type())

G_DECLARE_FINAL_TYPE (ExampleDevicePlugin, example_device_plugin, EXAMPLE, DEVICE_PLUGIN, ValentDevicePlugin)

void   example_device_plugin_register_types (PeasObjectModule *module);

G_END_DECLS

