// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#define G_LOG_DOMAIN "example-device-preferences-page"

#include <glib/gi18n.h>
#include <gio/gio.h>
#include <gtk/gtk.h>
#include <libpeas/peas.h>
#include <valent.h>

#include "example-device-preferences-page.h"


struct _ExampleDevicePreferencesPage
{
  ValentDevicePreferencesPage  parent_instance;

  /* template */
  GtkWidget                   *boolean_switch;
};

G_DEFINE_DYNAMIC_TYPE (ExampleDevicePreferencesPage, example_device_preferences_page, VALENT_TYPE_DEVICE_PREFERENCES_PAGE)


/*
 * GObject
 */
static void
example_device_preferences_page_constructed (GObject *object)
{
  ExampleDevicePreferencesPage *self = EXAMPLE_DEVICE_PREFERENCES_PAGE (object);
  ValentDevicePreferencesPage *page = VALENT_DEVICE_PREFERENCES_PAGE (self);
  GSettings *settings;

  /* Setup GSettings */
  settings = valent_device_preferences_page_get_settings (page);
  g_settings_bind (settings,             "boolean-setting",
                   self->boolean_switch, "active",
                   G_SETTINGS_BIND_DEFAULT);

  G_OBJECT_CLASS (example_device_preferences_page_parent_class)->constructed (object);
}

static void
example_device_preferences_page_class_finalize (ExampleDevicePreferencesPageClass *klass)
{
}

static void
example_device_preferences_page_class_init (ExampleDevicePreferencesPageClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->constructed = example_device_preferences_page_constructed;

  gtk_widget_class_set_template_from_resource (widget_class, "/plugins/example/example-device-preferences-page.ui");
  gtk_widget_class_bind_template_child (widget_class, ExampleDevicePreferencesPage, boolean_switch);
}

static void
example_device_preferences_page_init (ExampleDevicePreferencesPage *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

void
example_device_preferences_page_register_types (PeasObjectModule *module)
{
  example_device_preferences_page_register_type (G_TYPE_MODULE (module));

  peas_object_module_register_extension_type (module,
                                              VALENT_TYPE_DEVICE_PREFERENCES_PAGE,
                                              EXAMPLE_TYPE_DEVICE_PREFERENCES_PAGE);
}

