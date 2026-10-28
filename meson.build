project(
    'an-game',
    ['cpp', 'c'],
    version: '0.1.0',
    default_options: [
        'cpp_std=c++20',
        'warning_level=1',
        'buildtype=debug',
    ]
)

fs = import('fs')

anengine_proj = subproject('an-engine')

anengine_debug_arg = '-DENGINE_DEBUG_ENABLED=' + (get_option('debug') ? '1' : '0')
anengine_includes = anengine_proj.get_variable('includes')
anengine_deps = anengine_proj.get_variable('deps')

anengine_src = []
foreach f : anengine_proj.get_variable('src')
    if not fs.name(f).startswith('main_')
        anengine_src += f
    endif
endforeach

anengine_lib = shared_library(
    'anengine',
    # The engine's reflect_command is left out on purpose: its project.sln.hxx is
    # only read by the main_* entry points, and regenerating it re-parses every
    # engine source with clang on each build.
    anengine_src + anengine_proj.get_variable('thirdparty_src'),
    include_directories: anengine_includes,
    dependencies: anengine_deps,
    cpp_args: [anengine_debug_arg, '-D__REFLECT_GENERATED__'],
    c_args: [anengine_debug_arg],
    install: true,
)

anengine_dep = declare_dependency(
    link_with: anengine_lib,
    include_directories: anengine_includes,
    dependencies: anengine_deps,
    compile_args: [
        anengine_debug_arg,
        '-DANENGINE_PATH="' + meson.current_source_dir() / 'an-engine' + '"',
    ],
)

subdir('game')
