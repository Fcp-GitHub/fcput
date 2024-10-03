#ifndef FCP_MESH
#define FCP_MESH

#include "glad\glad.h"

#include "vertex_buffer.hpp"
#include "element_buffer.hpp"

#include <vector>

/* 
 * Available topology types.
 *
 * Taken from: https://www.khronos.org/opengl/wiki/Primitive
 */
enum TOPOLOGY
{
  POINTS,
  LINES,
  LINE_LOOP,
  LINE_STRIP,
  TRIANGLES,
  TRIANGLE_STRIP,
  TRIANGLE_FAN,
  LINES_ADJACENCY,
  LINE_STRIP_ADJACENCY,
  TRIANGLES_ADJACENCY,
  TRIANGLE_STRIP_ADJACENCY
};

template <typename T>
class Mesh
{
  private:
    std::vector<T> m_vertices;
    std::vector<T> m_normals;
    std::vector<T> m_uv;
    std::vector<T> m_tangents;
    std::vector<T> m_bitangents;
    std::vector<GLuint> m_indices;

    VAO m_vao;
    VBO<T> m_vbo;
    EBO<T> m_ebo;

    TOPOLOGY m_topology{ TRIANGLES }

  public:
    Mesh(){}
    Mesh(std::vector<T> vertices, std::vector<GLuint> indices):
      m_vertices{vertices}, m_indices{indices} {}
    Mesh(std::vector<T> vertices, std::vector<T> UV, std::vector<GLuint> indices):
      m_vertices{vertices}, m_uv{UV}, m_indices{indices} {}
    Mesh(std::vector<T> vertices, std::vector<T> UV, std::vector<T> normals, std::vector<GLuint> indices):
      m_vertices{vertices}, m_uv{UV}, m_normals{normals}, m_indices{indices} {}
    Mesh(std::vector<T> vertices, std::vector<T> UV, std::vector<T> normals, std::vector<T> tangents, std::vector<T> bitangents, std::vector<GLuint> indices):
      m_vertices{vertices}, m_uv{UV}, m_normals{normals}, m_tangents{tangents}, m_bitangents{bitangents}, m_indices{indices} {}

    void setVertices(const std::vector<T>& vertices)
    {
      m_vertices = vertices;
    }

    void setUV(const std::vector<T>& UV)
    {
      m_uv = UV;
    }

    void setNormals(const std::vector<T>& normals)
    {
      m_normals = normals;
    }

    void setTangents(const std::vector<T>& tangents)
    {
      m_tangents = tangents;
    }

    void setBitangents(const std::vector<T>& bitangents)
    {
      m_bitangents = bitangents;
    }

    void setIndices(const std::vector<GLuint>& indices)
    {
      m_indices = indices;
    }

    void finalize(bool interleaved = true)
    {
      std::vector<T> temp;
      if(interleaved)
      {
        for(std::size_t i{0}; i < m_vertices.size(); i++)
        {
          // complete
        }
      } else {
        // complete
      }

      m_vao.bind();
      m_vbo.bind();
      m_vbo.setData(temp);
      if(m_indices.size() > 0)
      {
        m_ebo.bind();
        m_ebo.setData(m_indices);
      }

      if(interleaved)
      {
        GLsizei stride{ 3 * sizeof(T) };
        if (m_uv.size() > 0)          stride += 2 * sizeof(T);
        if (m_normals.size() > 0)     stride += 2 * sizeof(T);
        if (m_tangents.size() > 0)    stride += 2 * sizeof(T);
        if (m_bitangents.size() > 0)  stride += 2 * sizeof(T);

        // complete setup
      }

    }
};

#endif  // FCP_MESH