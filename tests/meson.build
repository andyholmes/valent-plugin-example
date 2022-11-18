# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: No rights reserved

# Test Environment
tests_env = [
  'MALLOC_CHECK_=3',
  'PYTHONDONTWRITEBYTECODE=yes',
  'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
  'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir()),
  # https://docs.gtk.org/glib/running.html
  'G_DEBUG=gc-friendly',
  'G_SLICE=always-malloc',
  # https://docs.gtk.org/gio/overview.html
  'GIO_USE_VFS=local',
  'GSETTINGS_BACKEND=memory',
  'GSETTINGS_SCHEMA_DIR=@0@'.format(meson.project_build_root()),
  'GVFS_DISABLE_FUSE=true',
  # https://docs.gtk.org/gtk4/running.html
  'GDK_BACKEND=wayland,x11',
  'GTK_A11Y=test',
  # See: https://github.com/google/sanitizers/issues/1322
  'ASAN_OPTIONS=detect_leaks=1,intercept_tls_get_addr=0',
  'LSAN_OPTIONS=fast_unwind_on_malloc=0,suppressions=@0@'.format(
    join_paths(meson.current_source_dir(), 'extra', 'lsan.supp')),
  'TSAN_OPTIONS=force_seq_cst_atomics=1,history_size=5,suppressions=@0@'.format(
    join_paths(meson.current_source_dir(), 'extra', 'tsan.supp')),
  'UBSAN_OPTIONS=print_stacktrace=1:print_summary=1:halt_on_error=1',
]

test_c_args = [
  '-I@0@'.format(join_paths(meson.project_source_root(), 'src')),
  '-DJSON_SCHEMA_DIR="@0@"'.format(
    join_paths(meson.project_source_root(), 'doc', 'schemas')),
  '-DTEST_DATA_DIR="@0@"'.format(
    join_paths (meson.current_source_dir(), 'data')),
]

test_link_args = [
]

