#pragma once
#include <SFML/Graphics.hpp>
namespace HomoGebra
{
/**
 * \brief Thick line drawer.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date April 2023
 *
 */
class ThickLineDrawer
{
 public:
  void Draw(sf::RenderTarget& target, const std::vector<sf::Vertex>& vertices,
            float thickness)
  {
    if (vertices.empty())
    {
      return;  // If there are no vertices, no line can be drawn
    }

    if (vertices.size() == 1)
    {
      sf::CircleShape circle(thickness / 2.f);
      circle.setFillColor(vertices[0].color);
      circle.setPosition(vertices[0].position);
      target.draw(circle);  // Draw a circle if there is only one vertex
      return;
    }

    std::vector<sf::Vertex> vertices_with_thickness;
    vertices_with_thickness.reserve(vertices.size() * 4);

    for (size_t i = 0; i < vertices.size() - 1; ++i)
    {
      const auto& first = vertices[i];
      const auto& second = vertices[i + 1];

      const auto direction = second.position - first.position;
      const auto normal = sf::Vector2f(-direction.y, direction.x);
      const auto normalized_normal = normal / std::hypot(normal.x, normal.y);

      const auto half_thickness = thickness / 2.f;
      const auto first_vertex =
          first.position + normalized_normal * half_thickness;
      const auto second_vertex =
          first.position - normalized_normal * half_thickness;
      const auto third_vertex =
          second.position + normalized_normal * half_thickness;
      const auto fourth_vertex =
          second.position - normalized_normal * half_thickness;

      vertices_with_thickness.emplace_back(first_vertex, first.color);
      vertices_with_thickness.emplace_back(second_vertex, first.color);
      vertices_with_thickness.emplace_back(third_vertex, second.color);
      vertices_with_thickness.emplace_back(fourth_vertex, second.color);
    }

    sf::VertexBuffer buffer(sf::TriangleStrip);
    buffer.create(vertices_with_thickness.size());
    buffer.update(vertices_with_thickness.data());
    target.draw(buffer);  // Draw the thick line

    // Drawing circle at each point with radius equal to half of thickness
    for (const auto& vertex : vertices)
    {
      sf::CircleShape circle(thickness / 2.f);
      circle.setFillColor(vertex.color);
      circle.setPosition(vertex.position);
      target.draw(circle);
    }
  }
};
}  // namespace HomoGebra
