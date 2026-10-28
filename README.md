# an-game

A starter template for making a game with [an-engine](https://github.com/El3tekDeveloper/an-engine).

The engine is pulled in as a git submodule, used unmodified, and built as `libanengine.so`. Your game is a normal executable that links against it.

## Requirements

- `clang` / `clang++`
- `meson`, `ninja`, `python3`
- LLVM + libclang (`llvm-config`, `libclang-cpp`), used by the reflection tool
- `sdl2`, OpenGL, `freetype2`, `luajit` (found through pkg-config)

On Arch Linux:

```sh
sudo pacman -S clang llvm meson ninja python sdl2 freetype2 luajit
```

## Setup

```sh
git clone --recursive <your-repo-url> my-game
cd my-game
./build.sh
```

If you cloned without `--recursive`, `build.sh` fetches the engine submodule for you, or you can run:

```sh
git submodule update --init --recursive
```

## Building and running

| Command              | What it does                                  |
|----------------------|-----------------------------------------------|
| `./build.sh`         | Configure (first time), build, and run the game |
| `./build.sh build`   | Build only                                    |
| `./build.sh clean`   | Delete the build directory                    |

The game binary ends up at `build/game/game`. `build.sh` also links `compile_commands.json` into the project root for clangd.

Only the `game` target (and what it needs) is compiled. A plain `meson compile -C build` also builds the engine's own standalone executable, which you don't need.

## Project layout

```
an-game/
├── an-engine/          # engine (git submodule, don't edit here)
├── subprojects/
│   └── an-engine       # symlink to ../an-engine so meson can find it
├── game/
│   ├── main.cpp        # entry point: window, renderer, scene, main loop
│   ├── components.h    # your components
│   ├── assets/         # sprites, scenes... (reachable as "assets://...")
│   └── meson.build
├── meson.build         # builds libanengine.so from the submodule
└── build.sh
```

## Making your game

- **Code** goes in `game/`. When you add a `.cpp` file, add it to `game_src` in `game/meson.build`.
- **Assets** go in `game/assets/` and load with `assets://` paths, e.g. `assets://sprites/Fish.png`. Engine assets are available as `engine://...`.
- **Components** derive from `Component`. Mark a class and its fields with `[[export]]` to get reflection data for them:

  ```cpp
  struct [[export]] PlayerController : public Component {
      [[export]] float speed = 2.0f;
  };
  ```

  The reflection tool writes the registry to `game/project.sln.hxx` on every build. Include it in your sources, and don't edit it by hand.

- **Systems** derive from `System`, override `update(Scene&)`, and are added with `scene.add_system(...)`. See `PlayerSystem` in `game/main.cpp`.

## Updating the engine

```sh
git submodule update --remote an-engine
./build.sh
git add an-engine
git commit -m "Update an-engine"
```

To pin a specific engine version, run `git checkout <commit>` inside `an-engine/` and commit the new pointer in this repo.
