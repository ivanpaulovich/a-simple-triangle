#include "opengl-mesh.hpp"
#include "../../core/glm-wrapper.hpp"
#include <vector>

using ast::OpenGLMesh;

namespace
{
    GLuint createVertexBuffer(const ast::Mesh& mesh)
    {
        std::vector<glm::vec3> positions;

        for (const auto& vertex : mesh.getVertices())
        {
            positions.push_back(vertex.position);
        }

        GLuint bufferId;
        glGenBuffers(1, &bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        glBufferData(GL_ARRAY_BUFFER,
                     positions.size() * sizeof(glm::vec3),
                     positions.data(),
                     GL_STATIC_DRAW);

        return bufferId;
    }

    GLuint createIndexBuffer(const ast::Mesh& mesh)
    {
        GLuint bufferId;
        glGenBuffers(1, &bufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     mesh.getIndices().size() * sizeof(uint32_t),
                     mesh.getIndices().data(),
                     GL_STATIC_DRAW);

        return bufferId;
    }
} // namespace

struct OpenGLMesh::Internal
{
    const GLuint bufferIdVertices;
    const GLuint bufferIdIndices;
    const uint32_t numIndices;

    Internal(const ast::Mesh& mesh)
        : bufferIdVertices(::createVertexBuffer(mesh)),
          bufferIdIndices(::createIndexBuffer(mesh)),
          numIndices(static_cast<uint32_t>(mesh.getIndices().size())) {}

    ~Internal()
    {
        glDeleteBuffers(1, &bufferIdVertices);
        glDeleteBuffers(1, &bufferIdIndices);
    }
};

OpenGLMesh::OpenGLMesh(const ast::Mesh& mesh)
    : internal(ast::make_internal_ptr<Internal>(mesh)) {}

const GLuint& OpenGLMesh::getVertexBufferId() const
{
    return internal->bufferIdVertices;
}

const GLuint& OpenGLMesh::getIndexBufferId() const
{
    return internal->bufferIdIndices;
}

const uint32_t& OpenGLMesh::getNumIndices() const
{

    return internal->numIndices;
}