#pragma once

#include "Render/Texture.h"

#include <glad/glad.h>

namespace VoxelEngine
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const TextureSpecification& specification);
		OpenGLTexture(const std::string& path);
		OpenGLTexture(const std::string& right, const std::string& left,
			const std::string& top, const std::string& bottom,
			const std::string& front, const std::string& back);
		virtual ~OpenGLTexture();

		virtual const TextureSpecification& GetSpecification() const override { return m_Specification; }

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		virtual const std::string& GetPath() const override { return m_Path; }

		virtual void SetData(const void* data, const uint32_t size) override;

		virtual void Bind(const uint32_t slot = 0) const override;

		virtual bool IsLoaded() const override { return m_IsLoaded; }

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == other.GetRendererID();
		}

		static void SetGenerateMipmaps(const bool value) { m_GenerateMipmaps = value; }
		static void SetAnisoLevel(const float value) { m_AnisoLevel = value; }

	private:
		TextureSpecification m_Specification;

		std::string m_Path;
		std::array<std::string, 6> m_Paths;

		int32_t m_LoadedCnt = 0;
		bool m_IsLoaded = false;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;

		static bool m_GenerateMipmaps;
		static float m_AnisoLevel;
	};
}