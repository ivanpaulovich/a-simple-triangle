#pragma once

#include "../../core/internal-ptr.hpp"
#include "vulkan-device.hpp"

namespace ast
{
    struct VulkanCommandPool
    {
        VulkanCommandPool(const ast::VulkanDevice& device);

        vk::UniqueCommandBuffer beginCommandBuffer(const ast::VulkanDevice& device) const;

        void endCommandBuffer(const vk::CommandBuffer& commandBuffer,
                              const ast::VulkanDevice& device) const;

    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast
