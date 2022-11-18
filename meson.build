# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: No rights reserved

project('valent-plugin-example', 'c',
          license: 'GPL-3.0-or-later',
          version: '1.0.0',
    meson_version: '>= 0.59.0',
  default_options: [
    'buildtype=debugoptimized',
    'warning_level=2',
    'werror=true',
  ],
)

gnome = import('gnome')
i18n = import('i18n')
pkgconfig = import('pkgconfig')


# Configuration
#
# The configuration is used to populate the plugin info file, AppStream metadata
# and others, as well as renaming files during build time.
#
# - plugin_module: Mandatory and unique name; lower-case alphanumeric and dashes
# - plugin_author: The plugin author's name; no e-mail addresses or links
# - plugin_email: The plugin author's e-mail address
# - plugin_url: The plugin homepage or repository URL
#
plugin_module = 'example'
plugin_author = ''
plugin_email = ''
plugin_url = ''

plugin_conf = configuration_data()
plugin_conf.set('plugin_module', plugin_module)
plugin_conf.set('plugin_author', plugin_author)
plugin_conf.set('plugin_email', plugin_email)
plugin_conf.set('plugin_url', plugin_url)
plugin_conf.set('plugin_version', meson.project_version())
plugin_conf.set('gettext_package', meson.project_name())


# Paths
prefix = get_option('prefix')
bindir = join_paths(prefix, get_option('bindir'))
datadir = join_paths(prefix, get_option('datadir'))
includedir = join_paths(prefix, get_option('includedir'))
libdir = join_paths(prefix, get_option('libdir'))
libexecdir = join_paths(prefix, get_option('libexecdir'))
localedir = join_paths(prefix, get_option('localedir'))

pkgpluginsdir = join_paths(libdir, 'valent', 'plugins', plugin_module)

po_dir = join_paths(meson.current_source_dir(), 'po')


# Compiler
cc = meson.get_compiler('c')

release_args = []
project_c_args = [
  '-Wformat=2',
  '-Wincompatible-pointer-types',
  '-Wint-conversion',
  '-Wint-to-pointer-cast',
  '-Wmissing-include-dirs',
  '-Woverflow',
  '-Wpointer-arith',
  '-Wpointer-to-int-cast',
  '-Wredundant-decls',
  '-Wshadow',
  '-Wstrict-prototypes',
  '-Wundef',

  '-Wno-discarded-array-qualifiers',
  '-Wno-missing-field-initializers',
  '-Wno-unused-parameter',
]
project_link_args = [
  '-Wl,-z,relro',
  '-Wl,-z,now',
]

if get_option('buildtype') != 'plain'
  project_c_args += ['-fstack-protector-strong']
endif

if get_option('debug')
  project_c_args += ['-fno-omit-frame-pointer']
endif

if get_option('optimization') in ['2', '3', 's']
  project_c_args += ['-DG_DISABLE_CAST_CHECKS']
  project_link_args += ['-Wl,-Bsymbolic']

  if not get_option('tests')
    release_args += ['-DG_DISABLE_ASSERT']
  endif
endif

add_project_arguments(cc.get_supported_arguments(project_c_args),
  language: 'c',
)

add_project_link_arguments(cc.get_supported_link_arguments(project_link_args),
  language: 'c',
)


# Dependencies
gio_dep = dependency('gio-2.0', version: '>= 2.66.0')
gtk_dep = dependency('gtk4', version: '>= 4.6.0')
jsonglib_dep = dependency('json-glib-1.0', version: '>= 1.6.0')
libadwaita_dep = dependency('libadwaita-1', version: '>= 1.2.0')
libebook_dep = dependency('libebook-1.2', version: '>= 3.34')
libpeas_dep = dependency('libpeas-1.0', version: '>= 1.22.0')
libvalent_dep = dependency('valent-1.0', version: '>= 1.0.0', required: false)

if not libvalent_dep.found()
  libvalent = subproject('valent',
    default_options: [
      'introspection=false',
      'plugins=false',
    ],
  )
  libvalent_dep = libvalent.get_variable('libvalent_dep')
endif


# Build
subdir('data')
subdir('src')
subdir('po')

if get_option('tests')
  subdir('tests')
endif

gnome.post_install(
  glib_compile_schemas: true,
)


# Build Summary
summary({
  'Optimization':          get_option('optimization'),
  'Tests':                 get_option('tests'),
  'Debugging':             get_option('debug'),
}, section: 'Build')
