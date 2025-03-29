//
// Created by ryen on 3/1/25.
//

#include <spdlog/spdlog.h>

#include "MECore/resource/Material.h"

#include "MECore/render/RenderInterface.h"
#include "MECore/render/pipeline/RenderPipeline.h"

namespace ME::resource {
    #define ADD_LAYOUT(cond, source) \
    if (cond) { \
        if (auto layout = source; layout != nullptr) { \
            desc.bindingLayouts.push_back(layout); \
        } \
    } \

    bool Material::CreatePipeline(nvrhi::IFramebuffer* framebuffer) {
        if (!pipeline) {
            if (!vertexShader || !pixelShader) {
                spdlog::error("Failed material is missing vertex or pixel shader!");
                return false;
            }

            auto nvDevice = render::RenderInterface::instance->GetDevice();
            auto desc = pipelineDesc;
            desc.inputLayout = vertexShader->GetInputLayout();
            desc.VS = vertexShader->GetGPUShader();
            if (geometryShader) desc.GS = geometryShader->GetGPUShader();
            desc.PS = pixelShader->GetGPUShader();

            ADD_LAYOUT(true, render::RenderPipeline::instance->GetGlobalBindings())
            ADD_LAYOUT(vertexShader, vertexShader->GetBindingLayout())
            ADD_LAYOUT(geometryShader, geometryShader->GetBindingLayout())
            ADD_LAYOUT(pixelShader, pixelShader->GetBindingLayout())

            pipeline = nvDevice->createGraphicsPipeline(desc, framebuffer);
        }
        return pipeline;
    }

    #undef ADD_LAYOUT

    inline void PropertiesToBindings(nvrhi::IDevice* device, const Shader* shader, nvrhi::BindingSetHandle& handle, std::vector<nvrhi::IResource*>& resources) {
        if (!shader->GetBindingLayout()) return;

        const auto& properties = shader->GetProperties();
        const auto& layoutDesc = shader->GetBindingLayout()->getDesc();

        auto setDesc = nvrhi::BindingSetDesc();

        std::vector<int> indexes;
        indexes.resize(layoutDesc->bindings.size(), -1);
        for (int i = 0; i < properties.size(); i++) {
            const auto& prop = properties[i];
            indexes[prop.index] = i;
        }

        for (int i = 0; i < layoutDesc->bindings.size(); i++) {
            const auto& item = layoutDesc->bindings[i];

            auto setItem = nvrhi::BindingSetItem();
            setItem.type = item.type;
            setItem.slot = item.slot;
            setItem.subresources = nvrhi::AllSubresources;

            if (indexes[i] != -1) {
                setItem.resourceHandle = resources[indexes[i]];
            }

            setDesc.addItem(setItem);
        }

        handle = device->createBindingSet(setDesc, shader->GetBindingLayout());
    }

    bool Material::UpdateBindings() {
        auto nvDevice = render::RenderInterface::instance->GetDevice();
        if (vertexShader) PropertiesToBindings(nvDevice, vertexShader.get(), vertexBindings, vertexResources);
        if (geometryShader) PropertiesToBindings(nvDevice, geometryShader.get(), geometryBindings, geometryResources);
        if (pixelShader) PropertiesToBindings(nvDevice, pixelShader.get(), pixelBindings, pixelResources);
        resourcesDirty = false;
        return true;
    }

    inline bool SearchAndSet(const std::vector<ShaderProperty>& properties, std::vector<nvrhi::IResource*>& resources, const std::string& property, nvrhi::IResource* value) {
        for (int i = 0; i < properties.size(); i++) {
            if (properties[i].name == property) {
                resources[i] = value;
                return true;
            }
        }
        return false;
    }

    #define PROPRETY_SET(type, prop) if (type##Shader) changed |= SearchAndSet(type##Shader->GetProperties(), type##Resources, property, prop)

    bool Material::SetProperty(const std::string& property, const std::shared_ptr<Texture>& texture) {
        bool changed = false;
        PROPRETY_SET(vertex, texture->GetGPUTexture());
        PROPRETY_SET(geometry, texture->GetGPUTexture());
        PROPRETY_SET(pixel, texture->GetGPUTexture());
        resourcesDirty |= changed;
        return changed;
    }

    bool Material::SetProperty(const std::string& property, const nvrhi::SamplerHandle& sampler) {
        bool changed = false;
        PROPRETY_SET(vertex, sampler);
        PROPRETY_SET(geometry, sampler);
        PROPRETY_SET(pixel, sampler);
        resourcesDirty |= changed;
        return changed;
    }

    #undef PROPRETY_SET
}
