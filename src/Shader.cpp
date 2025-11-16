#include "Shader.h"
#include <cstddef>
#include <cstdint>
#include <expected>
#include <fstream>
#include <string_view>
#include <print>
#include <GL/glew.h>

ImView::Shader::Shader(std::string_view vertex_path, std::string_view fragment_path)
: m_shader_program_id{}
{
    const auto shader_data { ReadFromFile(vertex_path, fragment_path) };
    
    if (!shader_data.has_value())
    {
        std::print("Can't load shader data from file! Cause: {}\n", shader_data.error());
        return;
    }
    
    const auto compilation_res { Compile(shader_data.value()) };

    if (!compilation_res.has_value())
    {
        std::print("Can't compile shaders! Cause: {}\n", compilation_res.error());
        return;
    }

    m_shader_program_id = compilation_res.value();
}

void ImView::Shader::Bind() const noexcept 
{
    glUseProgram(m_shader_program_id);
}

std::expected<ImView::Shader::Data, std::string_view> ImView::Shader::ReadFromFile(std::string_view vertex_path, std::string_view fragment_path) noexcept
{
    auto read_file { [](std::string_view path) -> std::expected<std::string, std::string_view> {
        std::ifstream file_stream { std::ifstream(path.data(), std::ios::binary | std::ios::ate) };

        if (!file_stream.is_open())
        {
            return std::unexpected{"Path to shader not found!"};
        }
        
        const auto size {static_cast<size_t>(file_stream.tellg())};
            std::string buffer(size, '\n');
        file_stream.seekg(0, std::ios::beg);
        file_stream.read(buffer.data(), size);
        
        return std::expected<std::string, std::string_view>{buffer};
    } };

    const auto vertex_data {read_file(vertex_path)};
    if (!vertex_data.has_value())
    {
        return std::unexpected{vertex_data.error()};
    }

    const auto fragment_data {read_file(fragment_path)};
    if (!fragment_data.has_value())
    {
        return std::unexpected{fragment_data.error()};
    }

    const ImView::Shader::Data data {.vertex = vertex_data.value(), .fragment = fragment_data.value()};

   return std::expected<ImView::Shader::Data, std::string_view> {data};
}

std::expected<uint32_t, std::string_view> ImView::Shader::Compile(const ImView::Shader::Data& shader_data) noexcept
{
    const auto [vertex_data, fragment_data] { [](const auto& shader_data) {
        const auto& [vertex, fragment] { shader_data };
        return std::pair { vertex.c_str(), fragment.c_str() };
    }(shader_data) };
    
    auto check_status { [](const uint32_t data, GLenum type) {
        int success {};
        constexpr uint16_t log_size {512};
        std::array<char, log_size> log {};

        if (type == GL_COMPILE_STATUS)
        {
            glGetShaderiv(data, type, &success);
        }
        else
        {
            glGetProgramiv(data, type, &success);
        }

        if (!success)
        {
            if (type == GL_COMPILE_STATUS)
            {
                glGetShaderInfoLog(data, log.size(), nullptr, log.data());
            }
            else
            {
                glGetProgramInfoLog(data, log.size(), nullptr, log.data());
            }

            std::string msg { std::format("Error {}! Cause: {}\n", type, log.data()) };
            std::print("{}\n", msg);

            return false;
        }
        return true;

    } };

    const uint32_t vertex_shader { glCreateShader(GL_VERTEX_SHADER) };
    glShaderSource(vertex_shader, 1, &vertex_data, nullptr);
    glCompileShader(vertex_shader);

    if (!check_status(vertex_shader, GL_COMPILE_STATUS))
    {
        return std::unexpected{"Vertex shader compilation error!"};
    }

    const uint32_t fragment_shader { glCreateShader(GL_FRAGMENT_SHADER) };
    glShaderSource(fragment_shader, 1, &fragment_data, nullptr);
    glCompileShader(fragment_shader);

    if (!check_status(fragment_shader, GL_COMPILE_STATUS))
    {
        return std::unexpected{"Fragment shader compilation error!"};
    }

    const uint32_t shader_program { glCreateProgram() };
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    if (!check_status(shader_program, GL_LINK_STATUS))
    {
        return std::unexpected{"Shaders linking error!"};
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return std::expected<uint32_t, std::string_view> {shader_program};
}

uint32_t ImView::Shader::GetID() const noexcept
{
    return m_shader_program_id;
}

ImView::Shader::~Shader()
{
    glDeleteProgram(m_shader_program_id);
}
