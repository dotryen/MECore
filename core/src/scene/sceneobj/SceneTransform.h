//
// Created by ryen on 12/14/24.
//

#ifndef SCENETRANSFORM_H
#define SCENETRANSFORM_H
#include "haxe/HaxeEngineObject.h"
#include "math/Transform.h"

namespace me::scene {
    class SceneTransform : public haxe::HaxeEngineObject {
        private:
        math::Transform transform;
        math::Vector3 eulerAngles;

        public:
        SceneTransform() : HaxeEngineObject(u"me.scene.SceneTransform") {
            transform = math::Transform::identity;
            eulerAngles = math::Vector3(0, 0, 0);
        }

        [[nodiscard]] inline math::Vector3 GetPosition() const { return transform.position; }
        [[nodiscard]] inline math::Quaternion GetRotation() const { return transform.rotation; }
        [[nodiscard]] inline math::Vector3 GetAngles() const { return eulerAngles; }
        [[nodiscard]] inline math::Vector3 GetScale() const { return transform.scale; }
        [[nodiscard]] inline math::Vector3 GetRight() const { return transform.Right(); }
        [[nodiscard]] inline math::Vector3 GetUp() const { return transform.Up(); }
        [[nodiscard]] inline math::Vector3 GetForward() const { return transform.Forward(); }
        [[nodiscard]] inline math::Transform& Raw() { return transform; }

        inline void SetPosition(const math::Vector3& pos) { transform.position = pos; }
        inline void SetRotation(const math::Quaternion& rot) { transform.rotation = rot; eulerAngles = rot.GetEulerAngles() * math::RAD_TO_DEG; }
        inline void SetAngles(const math::Vector3& angles) { eulerAngles = angles; transform.rotation = math::Quaternion::sEulerAngles(angles * math::DEG_TO_RAD); }
        inline void SetScale(const math::Vector3& scale) { transform.scale = scale; }
    };
}


#endif //SCENETRANSFORM_H
