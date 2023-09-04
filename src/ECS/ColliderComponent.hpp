#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "Components.hpp"

class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;

    TransformComponent* transform;

    ColliderComponent(std::string t) {
        tag = t;
    }

    void init() override {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override {
        collider.x = transform->position.x;
        collider.y = transform->position.y;
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }
};
