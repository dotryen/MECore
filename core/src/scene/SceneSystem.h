//
// Created by ryen on 12/6/24.
//

#ifndef SCENESYSTEM_H
#define SCENESYSTEM_H
#include <map>
#include <memory>

#include "Scene.h"

namespace me::scene {
    typedef std::map<uint32_t, ScenePtr> SceneMap;

    class SceneSystem {
        private:
        SceneMap scenes;
        uint32_t nextId;

        public:
        SceneSystem();

        void AddScene(const ScenePtr scene);
        void RemoveScene(ScenePtr scene);
        void Update() const;

        uint32_t GetNextId();
    };
}

#endif //SCENESYSTEM_H
