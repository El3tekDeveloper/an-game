// Generated reflection registry
// DO NOT EDIT
#pragma once
#include "tools/reflector/runtime/type_registry.h"

// @@BEGIN 0/components.h
#include "components.h"
template<> struct has_reflection<PlayerController> : std::true_type {};
// @@END

// @@BEGIN 1/components.h
// PlayerController
#include "scene2/components/component_ops.h"

template<>
inline TypeClass* get_class_impl<PlayerController>() {
    static TypeClass c("PlayerController", sizeof(PlayerController));
    static bool initialized = false;
    if (initialized) return &c;
    initialized = true;

    c.get_impl = []() -> TypeClass* { return get_class_impl<PlayerController>(); };
    c.create_instance = []() -> void* { return new PlayerController(); };

    c.parent_type = static_cast<TypeClass*>(get_type_by_name("Component"));

    {
        static const std::string_view _fname_speed = "speed";
        static const std::string_view _ftype_speed = "float";
        Field f;
        f.name = _fname_speed;
        f.offset = offsetof(PlayerController, speed);
        f.type = get_type<float>();
        if (f.type) f.type->set_name(_ftype_speed);
        else LOG_ERROR("reflect: field 'speed' of PlayerController has unresolved type");
        c.get_fields().push_back(f);
    }
    {
        static const std::string_view _fname_bob_speed = "bob_speed";
        static const std::string_view _ftype_bob_speed = "float";
        Field f;
        f.name = _fname_bob_speed;
        f.offset = offsetof(PlayerController, bob_speed);
        f.type = get_type<float>();
        if (f.type) f.type->set_name(_ftype_bob_speed);
        else LOG_ERROR("reflect: field 'bob_speed' of PlayerController has unresolved type");
        c.get_fields().push_back(f);
    }
    {
        static const std::string_view _fname_bob_height = "bob_height";
        static const std::string_view _ftype_bob_height = "float";
        Field f;
        f.name = _fname_bob_height;
        f.offset = offsetof(PlayerController, bob_height);
        f.type = get_type<float>();
        if (f.type) f.type->set_name(_ftype_bob_height);
        else LOG_ERROR("reflect: field 'bob_height' of PlayerController has unresolved type");
        c.get_fields().push_back(f);
    }

    component_ops_registry()[&c] = ComponentTypeOps{
        [](Scene& scene, Entity id) -> Component* {
            return &scene.assign_component<PlayerController>(id);
        },
        [](Scene& scene, Entity id) -> Component* {
            return &scene.get_component<PlayerController>(id);
        },
        [](Scene& scene, Entity id) -> bool {
            return scene.get_entities()[entity::index(id)].mask.test(type_id<PlayerController>());
        },
        [](Scene& scene, Entity id) -> void {
            scene.remove_component<PlayerController>(id);
        },
    };

    return &c;
}

namespace {
    struct PlayerController_AutoRegister {
        PlayerController_AutoRegister() {
            register_type<PlayerController>(get_class_impl<PlayerController>());
        }
    };
    inline PlayerController_AutoRegister PlayerController_auto_register_instance;
}


// @@END

