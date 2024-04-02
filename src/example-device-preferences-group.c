// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#define G_LOG_DOMAIN "example-device-preferences-group"

#include <glib/gi18n.h>
#include <gio/gio.h>
#include <gtk/gtk.h>
#include <libpeas.h>
#include <valent.h>

#include "example-device-preferences-group.h"


struct _ExampleDevicePreferencesGroup
{
  ValentDevicePreferencesGroup  parent_instance;

  /* template */
  GtkWidget                   *boolean_switch;
};

G_DEFINE_DYNAMIC_TYPE (ExampleDevicePreferencesGroup, example_device_preferences_group, VALENT_TYPE_DEVICE_PREFERENCES_GROUP)


/*
 * GObject
 */
static void
example_device_preferences_group_constructed (GObject *object)
{
  ExampleDevicePreferencesGroup *self = EXAMPLE_DEVICE_PREFERENCES_GROUP (object);
  ValentDevicePreferencesGroup *group = VALENT_DEVICE_PREFERENCES_GROUP (self);
  GSettings *settings;

  /* Setup GSettings */
  settings = valent_device_preferences_group_get_settings (group);
  g_settings_bind (settings,             "boolean-setting",
                   self->boolean_switch, "active",
                   G_SETTINGS_BIND_DEFAULT);

  G_OBJECT_CLASS (example_device_preferences_group_parent_class)->constructed (object);
}

static void
example_device_preferences_group_class_finalize (ExampleDevicePreferencesGroupClass *klass)
{
}

static void
example_device_preferences_group_class_init (ExampleDevicePreferencesGroupClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->constructed = example_device_preferences_group_constructed;

  gtk_widget_class_set_template_from_resource (widget_class, "/plugins/example/example-device-preferences-group.ui");
  gtk_widget_class_bind_template_child (widget_class, ExampleDevicePreferencesGroup, boolean_switch);
}

static void
example_device_preferences_group_init (ExampleDevicePreferencesGroup *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

void
example_device_preferences_group_register_types (PeasObjectModule *module)
{
  example_device_preferences_group_register_type (G_TYPE_MODULE (module));

  peas_object_module_register_extension_type (module,
                                              VALENT_TYPE_DEVICE_PREFERENCES_GROUP,
                                              EXAMPLE_TYPE_DEVICE_PREFERENCES_GROUP);
}

