#!/bin/sh -ex

DOCKER="$(command -v podman || command -v docker)"

DOCKER_DIR="$(dirname "${0}")"

"${DOCKER}" build -t 'simde-dev' -f "${DOCKER_DIR}/Dockerfile" "${DOCKER_DIR}/.."
"${DOCKER}" run -v "$(realpath "${DOCKER_DIR}/..")":/usr/local/src/simde:z --cap-add=CAP_SYS_PTRACE -it --rm simde-dev /bin/bash
