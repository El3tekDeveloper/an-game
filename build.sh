#!/usr/bin/env bash
set -e

BUILD_DIR=build

cd "$(dirname "$0")"

if [ "$1" = "clean" ]; then
    echo "Cleaning..."
    rm -rf "$BUILD_DIR" .cache compile_commands.json
    exit 0
fi

if [ ! -f an-engine/meson.build ]; then
    echo "Fetching engine submodule..."
    git submodule update --init --recursive
fi

if [ ! -f "$BUILD_DIR/build.ninja" ]; then
    echo "Configuring..."
    rm -rf "$BUILD_DIR"
    CC=clang CXX=clang++ meson setup "$BUILD_DIR"
fi

echo "Building engine + game..."
meson compile -C "$BUILD_DIR" game

ln -sf "$BUILD_DIR/compile_commands.json" compile_commands.json

if [ "$1" = "build" ]; then
    exit 0
fi

echo "Running..."
"./$BUILD_DIR/game/game"
