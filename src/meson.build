# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: No rights reserved

plugin_c_args = []
plugin_link_args = []


# Dependencies
#
# Add any additional libraries your plugin requires here.
plugin_deps = [
  libvalent_dep,
]

# Plugin Sources
#
# Add additional extension implementations, being sure to also add their type
# registration functions to "example-plugin.c". Any source files that contain
# translatable strings should also be added to "/po/POTFILES".
plugin_sources = files([
  'example-device-plugin.c',
  'example-device-preferences-group.c',
  'example-plugin.c',
])

plugin_include_directories = [include_directories('.')]


# GResources
#
# You can replace "data/template.svg" with another symbolic icon for your plugin
# and add other plugin assets to "template.gresource.xml.in".
gresource_xml = configure_file(
          input: files('template.gresource.xml.in'),
         output: 'ca.andyholmes.Valent.Plugin.@0@.gresource.xml'.format(plugin_module),
  configuration: plugin_conf,
)

plugin_resources = gnome.compile_resources('@0@-resources'.format(plugin_module),
                                           gresource_xml,
        c_name: plugin_module,
)
plugin_sources += plugin_resources


# Plugin Library
plugin_library = shared_library(plugin_module, plugin_sources,
  include_directories: plugin_include_directories,
               c_args: plugin_c_args + release_args,
            link_args: plugin_link_args,
         dependencies: plugin_deps,
          install_dir: pkgpluginsdir,
              install: true,
)

