#include "rspch.h"
#include "SubTexture2D.h"

Rose::SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
	: m_Texture(texture)
{
	m_TexCoords[0] = { min.x / texture->GetWidth(), min.y / texture->GetHeight() };
	m_TexCoords[1] = { max.x / texture->GetWidth(), min.y / texture->GetHeight() };
	m_TexCoords[2] = { max.x / texture->GetWidth(), max.y / texture->GetHeight() };
	m_TexCoords[3] = { min.x / texture->GetWidth(), max.y / texture->GetHeight() };
}
/*coords: glm::vec2类型，表示网格中的坐标。例如(1, 2)代表第3列第2行（从0开始计数）。
cellSize : glm::vec2类型，表示网格中每个单元格的像素尺寸。
spriteSize : glm::vec2类型，可选参数，默认为(1, 1)。表示子纹理占用的网格单元数。如果需要占多个单元格，可以设置此参数。*/
Rose::Ref<Rose::SubTexture2D> Rose::SubTexture2D::CreateFromCoords(
    const Rose::Ref<Rose::Texture2D>& texture,
    const glm::vec2& coords,
    const glm::vec2& cellSize,
    const glm::vec2& spriteSize)
{
    glm::vec2 min = { coords.x * cellSize.x, coords.y * cellSize.y };
    glm::vec2 max = { (coords.x + spriteSize.x) * cellSize.x, (coords.y + spriteSize.y) * cellSize.y };

    return Rose::CreateRef<SubTexture2D>(texture, min, max);
}

