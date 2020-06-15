#!/bin/sh

if [ $# -gt 0 ]; then
  while [ $# -ge 1 ]; do
    if [ -e /usr/local/share/meson/cross/simde/"${1}.cross" ]; then
      if [ -e /opt/simde-build/"$1" ]; then
        rm -rf /opt/simde-build/"$1";
      fi
      meson --cross-file="simde/${1}.cross" /opt/simde-build/"$1" /usr/local/src/simde
    else
      echo "Unable to find cross file for $1" >&2 && exit 1
    fi

    shift
  done
else
  for cross in /usr/local/share/meson/cross/simde/*.cross; do
    target="$(basename "$cross" .cross)"
    if [ ! -e "/opt/simde-build/${target}" ]; then
      meson --cross-file="simde/${target}.cross" /opt/simde-build/"${target}" /usr/local/src/simde
    fi
  done
fi
