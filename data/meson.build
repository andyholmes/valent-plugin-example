# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: No rights reserved


# GSettings
#
# Add settings and child schemas to "template.gschema.xml.in", so that the
# extension implementations get automatic GSettings.
gsettings_schema = configure_file(
          input: files('template.gschema.xml.in'),
         output: 'ca.andyholmes.Valent.Plugin.@0@.gschema.xml'.format(plugin_module),
  configuration: plugin_conf,
    install_dir: join_paths(datadir, 'glib-2.0', 'schemas'),
        install: true,
)


# AppStream Metadata
#
# Set the "name" and "summary" tags in "template.metainfo.xml.in", so that they
# are included in translations.
metainfo_file = i18n.merge_file(
        input: configure_file(
                  input: files('template.metainfo.xml.in'),
                 output: 'template.metainfo.xml',
          configuration: plugin_conf,
        ),
       output: 'ca.andyholmes.Valent.Plugin.@0@.metainfo.xml'.format(plugin_module),
       po_dir: po_dir,
      install: true,
  install_dir: join_paths(datadir, 'metainfo'),
)

appstreamcli = find_program('appstreamcli', required: false)
if appstreamcli.found()
  test('Validate AppStream file', appstreamcli,
       args: ['validate', '--nonet', metainfo_file],
    depends: [metainfo_file],
  )
endif


# Plugin Info
#
# Set the "Name" and "Description" keys in "template.plugin.desktop.in", so that
# they are included in translations.
plugin_info = i18n.merge_file(
        input: configure_file(
                  input: files('template.plugin.desktop.in'),
                 output: 'template.plugin.desktop',
          configuration: plugin_conf,
        ),
       output: '@0@.plugin'.format(plugin_module),
       po_dir: po_dir,
         type: 'desktop',
  install_dir: pkgpluginsdir,
      install: true
)

