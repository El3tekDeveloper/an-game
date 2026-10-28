game_src = files(
    'main.cpp',
)

game_reflect = custom_target(
    'game solution file',
    output: 'project.sln.hxx',
    input: game_src,
    command: [
        anengine_proj.get_variable('reflect_tool_exe'),
        anengine_proj.get_variable('reflect_args'),
        '--root', meson.current_source_dir(),
        '--output', meson.current_source_dir() / 'project.sln.hxx',
        '@INPUT@',
    ],
    build_always_stale: true,
    build_by_default: true,
)

executable(
    'game',
    game_src,
    game_reflect,
    dependencies: anengine_dep,
    cpp_args: [
        '-DGAME_ASSETS_PATH="' + meson.current_source_dir() / 'assets' + '"',
    ],
    install: true,
    install_rpath: '$ORIGIN/../lib',
)
