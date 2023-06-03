// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#pragma once

#include <valent.h>

G_BEGIN_DECLS

#define EXAMPLE_TYPE_DEVICE_PREFERENCES_GROUP (example_device_preferences_group_get_type())

G_DECLARE_FINAL_TYPE (ExampleDevicePreferencesGroup, example_device_preferences_group, EXAMPLE, DEVICE_PREFERENCES_GROUP, ValentDevicePreferencesGroup)

void   example_device_preferences_group_register_types (PeasObjectModule *module);

G_END_DECLS
