[![Continuous Deployment](https://github.com/andyholmes/valent-plugin-example/actions/workflows/cd.yml/badge.svg)](https://github.com/andyholmes/valent-plugin-example/actions/workflows/cd.yml)

# Valent (Plugin Template)

**Template for Valent Plugins**

[Valent][valent] is an implementation of the [KDE Connect][kdeconnect] protocol,
built on [GNOME][gnome] platform libraries.

This repository hosts an example plugin, implementing a standard device plugin
with preferences.

## Using This Template

Replace `example` in any filenames, then search-and-replace instances of
`example`, `Example` and `EXAMPLE` in the project. Files with the basename
`template` are automatically renamed at build time.

Check the `meson.build` in each directory for more details about using the
template files. The root `meson.build` has a small section of variables:

| Name            | Description                                        |
|-----------------|----------------------------------------------------|
| `plugin_module` | The libpeas module name                            |
| `plugin_author` | The plugin author (e.g. "Alice Roberts")           |
| `plugin_email`  | The plugin author's e-mail address                 |
| `plugin_url`    | The plugin homepage or repository                  |

## Installation

To build and install as a system plugin, run `meson` with the appropriate
arguments for your distribution:

```sh
meson setup --prefix=/usr _build
meson install -C _build
```

For those interested in building a Flatpak extension, Valent's
[nightly repository][nightly-repo] can be used as a source for the runtime:

```sh
flatpak remote-add --if-not-exists valent https://valent.andyholmes.ca/valent.flatpakrepo
```

A Flatpak extension can then be built and installed with `flatpak-builder` and
`flatpak`:

```sh
# Build the extension
flatpak-builder --force-clean \
                --repo _flatpak_repo \
                _flatpak_builddir \
                ca.andyholmes.Valent.Plugin.example.json

# Export a bundle
flatpak build-bundle _flatpak_repo --runtime \
                     ca.andyholmes.Valent.Plugin.example.flatpak \
                     ca.andyholmes.Valent.Plugin.example \
                     master

# Install the extension
flatpak install ca.andyholmes.Valent.Plugin.example.flatpak
```

## Deployment

This repository includes a CI workflow that builds a Flatpak bundle for pull
requests, and a CD workflow that can deploy `x84_64` and `aarch64` builds to a
repository hosted on GitHub Pages (see the [flatter GitHub Action][flatter] for
details).

## Getting Help

Join the community in [Discussions][discussions] to ask questions, share ideas
and get help writing your plugin!

[valent]: https://github.com/andyholmes/valent
[gnome]: https://www.gnome.org
[kdeconnect]: https://kdeconnect.kde.org
[nightly-repo]: https://valent.andyholmes.ca/valent.flatpakrepo
[flatter]: https://github.com/andyholmes/flatter
[discussions]: https://github.com/andyholmes/valent/discussions
