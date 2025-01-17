//
// Created by ryen on 12/22/24.
//

#include "GameWorld.h"

namespace me::scene {
    GameWorld::GameWorld(Scene* scene) : HaxeEngineObject(u"me.game.GameWorld") {
        this->scene = scene;
    }

    std::vector<GameObject*> GameWorld::GetObjects() {
        std::vector<GameObject*> raw;
        raw.reserve(objects.size());
        std::ranges::transform(std::as_const(objects), std::back_inserter(raw), [](auto& ptr) { return ptr.get(); });
        return raw;
    }

    void GameWorld::StartCheck() {
        for (const auto& obj : objects) {
            obj->GetComponents().StartCheck();
        }
    }


    void GameWorld::Update() {
        for (const auto& obj : objects) {
            obj->GetComponents().Update();
        }
    }

    void GameWorld::FixedUpdate() {
        for (const auto& obj : objects) {
            obj->GetComponents().FixedUpdate();
        }
    }

    void GameWorld::LateUpdate() {
        for (const auto& obj : objects) {
            obj->GetComponents().LateUpdate();
        }
    }

    void GameWorld::OnPreRender() {
        for (const auto& obj : objects) {
            obj->GetComponents().OnPreRender();
        }
    }

    void GameWorld::AddObject(GameObject* obj) {
        obj->Internal_AssignWorld(this);
        objects.push_back(std::unique_ptr<GameObject>(obj));
    }

}
