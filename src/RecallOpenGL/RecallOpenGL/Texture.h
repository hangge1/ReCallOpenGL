#pragma once

#include <string>

class Texture
{
public:
    // 程序ID
    unsigned int texture;
    unsigned int unit;

    // 构造器读取并构建着色器
    Texture(const std::string& picture_path, int unit = 0);
    // 使用/激活程序
    void use();
};

