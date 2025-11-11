#ifndef IM_VIEW_SHADER_H
#define IM_VIEW_SHADER_H


#include <cstdint>
#include <string_view>
#include <string>
#include <expected>

namespace ImView {

class Shader
{
public:
    explicit Shader(std::string_view vertex_path, std::string_view fragment_path);
    void Bind() const noexcept; 

private:
    uint32_t m_shader_program_id;

    struct Data
    {
        std::string vertex;
        std::string fragment;
    };
    
    [[nodiscard]] static std::expected<Data, std::string_view> ReadFromFile(std::string_view vertex_path, std::string_view fragment_path) noexcept; 
    [[nodiscard]] static std::expected<uint32_t, std::string_view> Compile(const Data& shader_data) noexcept;
};
} //namespace ImView

#endif

