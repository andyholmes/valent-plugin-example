// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2022 Andy Holmes <andrew.g.r.holmes@gmail.com>

#define G_LOG_DOMAIN "example-device-plugin"

#include <glib/gi18n.h>
#include <gio/gio.h>
#include <json-glib/json-glib.h>
#include <libpeas.h>
#include <valent.h>

#include "example-device-plugin.h"


struct _ExampleDevicePlugin
{
  ValentDevicePlugin  parent_instance;
};

G_DEFINE_DYNAMIC_TYPE (ExampleDevicePlugin, example_device_plugin, VALENT_TYPE_DEVICE_PLUGIN)


static void
example_device_plugin_handle_ping (ExampleDevicePlugin *self,
                                   JsonNode            *packet)
{
  g_autoptr (GNotification) notification = NULL;
  const char *message;
  ValentDevice *device;

  g_assert (EXAMPLE_IS_DEVICE_PLUGIN (self));
  g_assert (VALENT_IS_PACKET (packet));

  /* Check for the optional message */
  if (!valent_packet_get_string (packet, "message", &message))
    message = _("Ping!");

  /* Show a notification */
  device = valent_extension_get_object (VALENT_EXTENSION (self));
  notification = g_notification_new (valent_device_get_name (device));
  g_notification_set_body (notification, message);
  valent_device_plugin_show_notification (VALENT_DEVICE_PLUGIN (self),
                                          "ping",
                                          notification);
}

/*
 * GActions
 */
static void
ping_action (GSimpleAction *action,
             GVariant      *parameter,
             gpointer       user_data)
{
  ExampleDevicePlugin *self = EXAMPLE_DEVICE_PLUGIN (user_data);
  g_autoptr (JsonNode) packet = NULL;

  g_assert (EXAMPLE_IS_DEVICE_PLUGIN (self));

  packet = valent_packet_new ("kdeconnect.ping");
  valent_device_plugin_queue_packet (VALENT_DEVICE_PLUGIN (self), packet);
}

static const GActionEntry actions[] = {
    {"ping", ping_action, NULL, NULL, NULL}
};

/**
 * ValentDevicePlugin
 */
static void
example_device_plugin_update_state (ValentDevicePlugin *plugin,
                                    ValentDeviceState   state)
{
  gboolean available;

  g_assert (EXAMPLE_IS_DEVICE_PLUGIN (plugin));

  available = (state & VALENT_DEVICE_STATE_CONNECTED) != 0 &&
              (state & VALENT_DEVICE_STATE_PAIRED) != 0;

  valent_extension_toggle_actions (VALENT_EXTENSION (plugin), available);
}

static void
example_device_plugin_handle_packet (ValentDevicePlugin *plugin,
                                      const char         *type,
                                      JsonNode           *packet)
{
  ExampleDevicePlugin *self = EXAMPLE_DEVICE_PLUGIN (plugin);

  g_assert (EXAMPLE_IS_DEVICE_PLUGIN (self));
  g_assert (type != NULL);
  g_assert (VALENT_IS_PACKET (packet));

  if (strcmp (type, "kdeconnect.ping") == 0)
    example_device_plugin_handle_ping (self, packet);
  else
    g_assert_not_reached ();
}

/*
 * GObject
 */
static void
example_device_plugin_constructed (GObject *object)
{
  ValentDevicePlugin *plugin = VALENT_DEVICE_PLUGIN (object);

  g_action_map_add_action_entries (G_ACTION_MAP (plugin),
                                   actions,
                                   G_N_ELEMENTS (actions),
                                   plugin);

  G_OBJECT_CLASS (example_device_plugin_parent_class)->constructed (object);
}

static void
example_device_plugin_class_finalize (ExampleDevicePluginClass *klass)
{
}

static void
example_device_plugin_class_init (ExampleDevicePluginClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  ValentDevicePluginClass *plugin_class = VALENT_DEVICE_PLUGIN_CLASS (klass);

  object_class->constructed = example_device_plugin_constructed;

  plugin_class->handle_packet = example_device_plugin_handle_packet;
  plugin_class->update_state = example_device_plugin_update_state;
}

static void
example_device_plugin_init (ExampleDevicePlugin *self)
{
}

void
example_device_plugin_register_types (PeasObjectModule *module)
{
  example_device_plugin_register_type (G_TYPE_MODULE (module));

  peas_object_module_register_extension_type (module,
                                              VALENT_TYPE_DEVICE_PLUGIN,
                                              EXAMPLE_TYPE_DEVICE_PLUGIN);
}

