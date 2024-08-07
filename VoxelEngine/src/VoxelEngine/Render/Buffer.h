#pragma once

namespace VoxelEngine
{
  enum class ShaderDataType
  {
    None = 0,
    Float, Float2, Float3, Float4,
    Mat3, Mat4,
    Int, Int2, Int3, Int4,
    Bool
  };

  static uint32_t ShaderDataTypeSize(const ShaderDataType& type)
  {
    switch (type)
    {
    case ShaderDataType::Float: return 4;
    case ShaderDataType::Float2: return 4 * 2;
    case ShaderDataType::Float3: return 4 * 3;
    case ShaderDataType::Float4: return 4 * 4;
    case ShaderDataType::Mat3: return 4 * 3 * 3;
    case ShaderDataType::Mat4: return 4 * 4 * 4;
    case ShaderDataType::Int: return 4;
    case ShaderDataType::Int2: return 4 * 2;
    case ShaderDataType::Int3: return 4 * 3;
    case ShaderDataType::Int4: return 4 * 4;
    case ShaderDataType::Bool: return 1;
    }

    CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
  }

  struct BufferElement
  {
    BufferElement() = default;

    BufferElement(const ShaderDataType& type, const std::string& name,
                  const bool normalized = false)
      : name_(name), type_(type), normalized_(normalized), size_(ShaderDataTypeSize(type))
    {
    }

    uint32_t GetComponentCount() const
    {
      switch (type_)
      {
      case ShaderDataType::Float:   return 1;
      case ShaderDataType::Float2:  return 2;
      case ShaderDataType::Float3:  return 3;
      case ShaderDataType::Float4:  return 4;
      case ShaderDataType::Mat3:    return 3 * 3;
      case ShaderDataType::Mat4:    return 4 * 4;
      case ShaderDataType::Int:     return 1;
      case ShaderDataType::Int2:    return 2;
      case ShaderDataType::Int3:    return 3;
      case ShaderDataType::Int4:    return 4;
      case ShaderDataType::Bool:    return 1;
      }

      CORE_ASSERT(false, "Unknown ShaderDataType!");
      return 0;
    }

    std::string name_;
    ShaderDataType type_;
    uint32_t size_;
    uint32_t offset_;
    bool normalized_;
  };

  class BufferLayout
  {
  public:
    BufferLayout() = default;

    BufferLayout(const std::initializer_list<BufferElement>& elements)
      : m_Elements(elements)
    {
      CalculateOffsetsAndStride();
    }

    inline uint64_t GetStride() const { return m_Stride; }
    inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

  private:
    void CalculateOffsetsAndStride()
    {
      uint64_t offset = 0;
      m_Stride = 0;
      for (auto& element : m_Elements) {
        element.offset_ = offset;
        offset += element.size_;
        m_Stride += element.size_;
      }
    }

  private:
    std::vector<BufferElement> m_Elements;
    uint64_t m_Stride = 0;
  };

  class VertexBuffer
  {
  public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetData(const void* data, const uint64_t size) = 0;

    virtual inline const BufferLayout& GetLayout() const = 0;
    virtual void SetLayout(const BufferLayout& layout) = 0;

    static std::shared_ptr<VertexBuffer> Create(const uint64_t size);
    static std::shared_ptr<VertexBuffer> Create(const float* vertices, const uint64_t size);
  };

  class IndexBuffer
  {
  public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual inline const uint32_t GetCount() const = 0;

    virtual void SetData(const void* data, const uint64_t size) = 0;

    static std::shared_ptr<IndexBuffer> Create(const uint32_t* indices, const uint32_t count);
    static std::shared_ptr<IndexBuffer> Create(const uint64_t size);
  };
}