//
// Created by ryen on 12/4/24.
//

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <memory>
#include "SceneTransform.h"
#include "../../math/Transform.h"

namespace me::scene {
    class SceneWorld;

    // An object used for rendering.
    class SceneObject {
        private:
        SceneWorld* world;
        bool enabled;
        SceneTransform transform;
        std::string name;

        public:
        SceneObject();
        explicit SceneObject(const std::string name);
        virtual ~SceneObject();

        [[nodiscard]] inline bool IsEnabled() const { return enabled; }
        inline void SetEnabled(const bool state) { enabled = state; }
        [[nodiscard]] inline SceneTransform& GetTransform() { return transform; }

        [[nodiscard]] inline std::string GetName() const { return name; }
        inline void SetName(const std::string name) { this->name = name; }

        void Internal_AssignWorld(SceneWorld* world);
    };

    typedef std::shared_ptr<SceneObject> SceneObjectPtr;
}

#endif //SCENEOBJECT_H