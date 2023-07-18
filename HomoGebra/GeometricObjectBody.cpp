#include "GeometricObjectBody.h"

#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include <utility>

#include "Assert.h"
#include "Matrix.h"

ObjectName::ObjectName(std::string name)
{
  // Load font
  font_.loadFromFile(kFontPath);

  // Set font
  text_.setFont(font_);
  text_.setCharacterSize(kCharacterSize);

  // Set color
  text_.setFillColor(kTextColor);

  // Set name
  SetName(std::move(name));
}

void ObjectName::SetName(std::string name)
{
  // Set name
  name_ = std::move(name);

  // Set text
  text_.setString(name_);
}

const std::string& ObjectName::GetName() const { return name_; }

void ObjectName::SetSize(const float size)
{
  const auto height = text_.getLocalBounds().height;
  auto factor = size / height;
  text_.setScale({factor, factor});
}

void ObjectName::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Apply transform
  states.transform *= getTransform();
  // Draw
  target.draw(text_, states);
}

void ObjectBody::SetName(std::string name)
{
  // Set name
  text_.SetName(std::move(name));
}

const std::string& ObjectBody::GetName() const
{
  // Return name
  return text_.GetName();
}

void ObjectBody::SetNamePosition(const sf::Vector2f& position)
{
  // Set position
  text_.setPosition(position);
}

void ObjectBody::SetNameSize(const float size)
{
  // Set size
  text_.SetSize(size);
}

void ObjectBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Draw name
  target.draw(text_, states);
}

PointBody::PointBody() { body_.setFillColor(sf::Color::Red); }

void PointBody::Update(const PointEquation& equation, const float size)
{
  // Calculate position
  position_ = CalculatePosition(equation);

  // Point is in real projective plane
  if (position_)
  {
    body_.setPosition(position_.value().position);
    SetNamePosition(position_.value().position);
  }

  // Set size
  constexpr auto kTextFactor = 2.f;
  SetNameSize(size * kTextFactor);

  // Set size
  body_.setRadius(size);
  body_.setOrigin(size, size);
}

void PointBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Point is not on a real plane
  if (!position_) return;

  if (const auto& [position, is_at_infinity] = position_.value();
      is_at_infinity)
  {
    // Draw point at infinity
    // DrawArrow(target, states);
  }
  else
  {
    // Draw point
    target.draw(body_, states);
    ObjectBody::draw(target, states);
  }
}

inline [[nodiscard]] std::optional<sf::Vector2f> IntersectRayWithRectangle(
    const sf::Vector2f& point, const sf::Vector2f& direction,
    const sf::FloatRect& rectangle)
{
  if (!rectangle.contains(point))
  {
    return std::nullopt;
  }

  // TODO: Intersect line with rect.

  struct Line
  {
    Line(sf::Vector2f first_point, sf::Vector2f second_point)
    {
      const FloatSquaredMatrix matrix({{first_point.x, first_point.y, 1},
                                       {second_point.x, second_point.y, 1},
                                       {1, 1, 1}},
                                      {0, 0, 1});
      auto solution = matrix.GetSolution();
    }
  };
}

void PointBody::DrawArrow(sf::RenderTarget& target,
                          sf::RenderStates states) const
{
  Assert(position_, "Point has no 'real' position");

  const auto& [position, is_at_infinity] =
      position_.value();  // NOLINT(bugprone-unchecked-optional-access)

  Expect(is_at_infinity, "Drawing arrow, but point isn't at infinity?!");

  const auto& view = target.getView();
  const auto intersection = std::optional<sf::Vector2f>{};

  Assert(intersection.has_value(),
         "Couldn't find an intersection with a screen!");

  // Coefficient for start of line.
  constexpr auto kStartShift = 0.9f;
  const auto arrow_start = intersection.value() * kStartShift +
                           view.getCenter() * (1.f - kStartShift);
  constexpr auto kEndShift = 0.95f;
  const auto arrow_end =
      intersection.value() * kEndShift + view.getCenter() * (1.f - kEndShift);

  thor::Arrow arrow{arrow_start, arrow_end, sf::Color::Black, 10};

  target.draw(arrow, states);
}

std::optional<PointBody::ProjectivePosition> PointBody::CalculatePosition(
    const PointEquation& equation)
{
  // Get equation
  const auto& eq = equation.GetEquation();

  // Normalize equation
  const auto normalized_eq = eq.GetNormalized();

  // Check if point lies on the "R-plane" which we see
  if (!normalized_eq.x.IsReal() || !normalized_eq.y.IsReal())
  {
    return std::nullopt;
  }

  // Check if point is at infinity
  if (normalized_eq[Var::kZ].IsZero())
  {
    return ProjectivePosition{
        sf::Vector2f(static_cast<float>(normalized_eq.x.real()),
                     static_cast<float>(normalized_eq.y.real())),
        true};
  }

  // Return position
  return ProjectivePosition{
      sf::Vector2f(static_cast<float>(normalized_eq.x.real()),
                   static_cast<float>(normalized_eq.y.real())),
      false};
}

void LineBody::Update(const LineEquation& equation)
{
  // Normalize equation
  const auto normalized_equation = equation.equation.GetNormalized();

  // Check if line is in 'real' plane
  if (!(normalized_equation.x.IsReal() && normalized_equation.y.IsReal()))
  {
    equation_ = std::nullopt;
  }

  // Set equation
  Equation body_equation{
      static_cast<float>(static_cast<long double>(normalized_equation.x)),
      static_cast<float>(static_cast<long double>(normalized_equation.y)),
      static_cast<float>(static_cast<long double>(normalized_equation.z))};

  equation_ = body_equation;
}

void LineBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Check ig line is in 'real' plane
  if (!equation_)
  {
    return;
  }
  const auto& a = equation_.value().a;
  const auto& b = equation_.value().b;
  const auto& c = equation_.value().c;

  const auto& center = target.getView().getCenter();
  const auto& size = target.getView().getSize();

  const auto left = center.x - size.x / 2.f;
  const auto right = center.x + size.x / 2.f;
  const auto up = center.y + size.y / 2.f;
  const auto down = center.y - size.y / 2.f;

  std::array<sf::Vertex, 2> line_vertices;

  std::ranges::for_each(line_vertices, [](sf::Vertex& vertex)
                        { vertex.color = sf::Color::Black; });

  constexpr size_t first = 0;
  constexpr size_t second = 1;

  if (abs(a / b) > size.y / size.x)
  {
    line_vertices[first].position.y = down;
    line_vertices[second].position.y = up;
    line_vertices[first].position.x =
        -(line_vertices[first].position.y * b + c) / a;
    line_vertices[second].position.x =
        -(line_vertices[second].position.y * b + c) / a;
  }
  else
  {
    line_vertices[first].position.x = left;
    line_vertices[second].position.x = right;
    line_vertices[first].position.y =
        -(line_vertices[first].position.x * a + c) / b;
    line_vertices[second].position.y =
        -(line_vertices[second].position.x * a + c) / b;
  }

  target.draw(line_vertices.data(), 2, sf::Lines);
}

float LineBody::Equation::Solve(const Var var, const float another) const
{
  switch (var)
  {
    case Var::kX:
      return (-c - b * another) / a;
    case Var::kY:
      return (-c - a * another) / b;
    case Var::kZ:
    default:
      Assert(false, "Invalid variable");
  }
}

void ConicBody::Update(const ConicEquation& equation)
{
  /*
   A*x^2 + B*y^2 + C*z^2 +
   D*yz + E*xz + F*xy = 0

   Transforms into:

   A*x^2 + B*y^2 + || squares
   F*xy +          || pair product
   E*x*1 + D*y*1 + || linears
   C*1^2 = 0       || constant
   */

  // A*x^2 + B*y^2 + || squares
  equation_.squares[static_cast<size_t>(Var::kX)] =
      equation.squares[static_cast<size_t>(Var::kX)];
  equation_.squares[static_cast<size_t>(Var::kY)] =
      equation.squares[static_cast<size_t>(Var::kY)];

  // F*xy +          || pair product
  equation_.pair_product = equation.pair_products[static_cast<size_t>(Var::kZ)];

  // E*x*1 + D*y*1 + || linears
  equation_.linears[static_cast<size_t>(Var::kX)] =
      equation.pair_products[static_cast<size_t>(Var::kY)] * Complex{1};
  equation_.linears[static_cast<size_t>(Var::kY)] =
      equation.pair_products[static_cast<size_t>(Var::kX)] * Complex{1};

  // C*1^2 = 0       || constant
  equation_.constant =
      equation.squares[static_cast<size_t>(Var::kZ)] * Complex{1} * Complex{1};
}

void ConicBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Acquire render region center and size
  const auto render_region_center = target.getView().getCenter();
  const auto render_region_size = target.getView().getSize();

  // Calculate render region corner
  const auto corner = render_region_center - render_region_size / 2.f;

  sf::FloatRect rendering_region{corner, render_region_size};

  // Calculates distance between
  auto find_distance =
      [](const sf::Vector2f first, const sf::Vector2f second = sf::Vector2f{})
  {
    const auto delta = second - first;
    return std::hypot(delta.x, delta.y);
  };

  // Calculate amount of steps needed and their size
  const size_t steps = std::max(target.getSize().x, target.getSize().y);
  const auto step_size = render_region_size / static_cast<float>(steps);

  // Max distance between two points on line
  const auto max_distance = find_distance(step_size) * 4.f;

  using Line = std::vector<sf::Vertex>;
  using Lines = std::vector<Line>;

  Lines lines;

  for (size_t step = 0; step < steps; ++step)
  {
    // Calculate position of current step
    const auto pos = corner + step_size * static_cast<float>(step);

    // Calculate roots of equation
    auto roots_y = equation_.Solve(Var::kY, Complex{pos.x});

    // Calculate roots of equation
    auto roots_x = equation_.Solve(Var::kX, Complex{pos.y});

    std::vector<sf::Vector2f> points_to_add;

    // Check if roots are real and add them to points_to_add
    for (auto& root : roots_y)
    {
      if (root && root.value().IsReal() &&
          rendering_region.contains({pos.x, static_cast<float>(root.value())}))
      {
        points_to_add.emplace_back(pos.x, static_cast<float>(root.value()));
      }
    }

    // Check if roots are real and add them to points_to_add
    for (auto& root : roots_x)
    {
      if (root && root.value().IsReal() &&
          rendering_region.contains({static_cast<float>(root.value()), pos.y}))
      {
        points_to_add.emplace_back(static_cast<float>(root.value()), pos.y);
      }
    }

    // Find line that is closest to current point
    auto find_line = [&](const sf::Vector2f& point)
    {
      auto best = lines.rend();
      auto distance = INFINITY;

      for (auto it = lines.rbegin(); it != lines.rend(); ++it)
      {
        if (find_distance(it->back().position, point) <
            std::min(distance, max_distance))
        {
          best = it;
          distance = find_distance(it->back().position, point);
        }
      }

      return best;
    };

    // Add points to lines
    for (auto& point : points_to_add)
    {
      if (auto suitable = find_line(point); suitable == lines.rend())
      {
        lines.emplace_back(Line{{point, sf::Color::Black}});
      }
      else
      {
        suitable->push_back({point, sf::Color::Black});
      }
    }
  }

  // Draw lines
  for (auto& line : lines)
  {
    target.draw(line.data(), line.size(), sf::PrimitiveType::LineStrip, states);
  }
}

inline [[nodiscard]] std::array<std::optional<Complex>, 2>
SolveQuadraticEquation(const Complex& quadratic_coefficient,
                       const Complex& linear_coefficient,
                       const Complex& constant_coefficient)
{
  // Check if a is zero
  if (quadratic_coefficient.IsZero())
  {
    if (linear_coefficient.IsZero())
    {
      return {std::nullopt, std::nullopt};
    }

    auto root = -constant_coefficient / linear_coefficient;
    return {root, std::nullopt};
  }

  // ax^2+bx+c=0
  // x = (-b +- sqrt(discriminant)) / 2a

  // Calculate discriminant
  const auto discriminant =
      linear_coefficient * linear_coefficient -
      Complex{4} * quadratic_coefficient * constant_coefficient;

  const auto first_root = (-linear_coefficient + sqrt(discriminant)) /
                          (Complex{2} * quadratic_coefficient);
  const auto second_root = (-linear_coefficient - sqrt(discriminant)) /
                           (Complex{2} * quadratic_coefficient);

  return {first_root, second_root};
}

ConicBody::Equation::Solution ConicBody::Equation::Solve(
    Var var, const Complex& another) const
{
  // Ax^2 + Bxy + Cy^2 + Dx + Ey + F = 0
  const auto another_var = kAnother[static_cast<size_t>(var)];

  const auto quadratic_coefficient = squares[static_cast<size_t>(var)];

  const auto linear_coefficient = pair_product * another;
  const auto constant_coefficient =
      squares[static_cast<size_t>(another_var)] * another * another + constant;

  return SolveQuadraticEquation(quadratic_coefficient, linear_coefficient,
                                constant_coefficient);
}