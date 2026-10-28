#include "core/debug/logger.h"
#include "core/input/input.h"
#include "core/io/path.h"
#include "core/math/vector3.h"
#include "core/memory/memory.h"
#include "core/os/application.h"
#include "core/os/time.h"
#include "render/renderer.h"
#include "resources/resource_manager.h"
#include "resources/sprite.h"
#include "resources/texture.h"
#include "scene2/component.h"
#include "scene2/scene.h"
#include "scene2/systems/render_system.h"

#include "components.h"
#include "project.sln.hxx"

#include <cmath>

class PlayerSystem : public System {
public:
    void update(Scene& scene) override {
        ecs::Registry& registry = scene.get_registry();
        float dt = static_cast<float>(Time.delta_time());
        
        for (auto e : registry.view<Transform, PlayerController>()) {
            Transform& transform = registry.get<Transform>(e);
            PlayerController& controller = registry.get<PlayerController>(e);

            Vector3 dir = Vector3::Zero;
            if (Input.is_key_pressed(Key::Left))  dir.x -= 1.0f;
            if (Input.is_key_pressed(Key::Right)) dir.x += 1.0f;
            if (Input.is_key_pressed(Key::Up))    dir.y += 1.0f;
            if (Input.is_key_pressed(Key::Down))  dir.y -= 1.0f;

            transform.position += dir * (controller.speed * dt);
            transform.position.y += std::sin(static_cast<float>(Time.time()) * controller.bob_speed) * controller.bob_height * dt;
        }
    }
};

int main() {
    IO::set_engine_path(ANENGINE_PATH);
    IO::set_assets_path(GAME_ASSETS_PATH);

    BumpAllocator transient_storage(GB(1));

    Application app;
    if (!app.is_running()) {
        LOG_ERROR("Application failed to start");
        return -1;
    }

    Window* window = app.create_window(WindowDesc{
        .title = "an-game",
        .width = 1280,
        .height = 720
    });
    if (!window) {
        LOG_ERROR("Window creation failed");
        return -1;
    }
    window->on_close = [&app]() { app.quit(); };
    
    SwapchainRenderTarget swap_chain(window);
    ViewPort viewport{
        window->get_width(), window->get_height(),
        0, 0,
        &swap_chain,
    };
    window->on_resize = [&viewport](int w, int h) { viewport.resize(w, h); };

    Renderer renderer;
    if (!renderer.init(&transient_storage)) {
        LOG_ERROR("Renderer init failed");
        return -1;
    }

    RenderData render_data = { .clear_color = "#1E2A3A" };

    Scene scene;
    scene.add_system(std::make_unique<PlayerSystem>());
    scene.add_system(std::make_unique<RenderSystem>());
    scene.initialize();

    Entity camera = scene.create_entity();
    scene.assign_component<Transform>(camera).position = Vector3(0.0f, 0.0f, 1.0f);
    Camera& camera_component = scene.assign_component<Camera>(camera);
    camera_component.type = CameraType::Orthographic;
    camera_component.orthographic_size = 1.5f;

    Sprite fish_sprite;
    fish_sprite.load("assets://sprites/Fish.png");
    fish_sprite.texture->set_filter(TextureFilter::Nearest);
    fish_sprite.rect = SpriteRect{ .width = 64, .height = 64 };

    Entity fish = scene.create_entity();
    scene.assign_component<Transform>(fish);
    scene.assign_component<SpriteRenderer>(fish, fish_sprite);
    scene.assign_component<PlayerController>(fish);
    
    if (TypeClass* type = static_cast<TypeClass*>(get_type<PlayerController>())) {
        for (Field& field : type->get_fields())
            LOG_INFO("reflected {}::{} ({})", type->get_name(), field.name, field.type->get_name());
    }

    LOG_INFO("an-game started: arrow keys to move, Escape to quit");
    
    while (app.is_running()) {
        app.poll_events();
        if (Input.is_key_just_pressed(Key::Escape)) app.quit();

        Time.update();
        scene.update();

        window->make_current();
        scene.draw(viewport, render_data);
        renderer.render(viewport, render_data);
        window->swap_buffers();
    }

    ResourceManager.clear_all();
    renderer.destroy();
    app.destroy_all_windows();
    scene.save("assets://main_scene.ascn");
    return 0;
}
