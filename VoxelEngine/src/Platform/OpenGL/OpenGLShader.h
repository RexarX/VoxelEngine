#pragma once

#include "Render/Shader.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace VoxelEngine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertex, const std::string& fragment);
		virtual ~OpenGLShader();

		virtual inline const uint32_t GetID() const override { return m_ID; }

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddUniform(const void* data = nullptr, const uint32_t size = 128) override;

		virtual void UploadUniformInt(const std::string& name, const int value) override;

		virtual void UploadUniformFloat(const std::string& name, const float value) override;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& value) override;

		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

		virtual void UploadUniformData(const std::string& name, const void* data, const uint32_t size) override;

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::pair<std::string, std::string>> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::pair<std::string, std::string>>& shaderSources);

		bool GLSLtoSPV(const GLenum shaderType, const std::string& glslShader,
									 const std::string& fileName, std::vector<uint32_t>& spvShader) const;

	private:
		uint32_t m_ID = 0;

		uint32_t m_RendererID;

		bool m_Compiled = false;
	};
}