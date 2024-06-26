#include "GeometricObjectBody.h"

#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include <numbers>
#include <utility>

#include "Assert.h"
#include "Matrix.h"
#include "ThickLineDrawer.h"

namespace HomoGebra
{
extern float CalculateSizeOfPixel(const sf::RenderTarget& target)
{
  // Calculate position of pixel with coordinate (0, 0)
  const auto first_pixel_position = target.mapPixelToCoords({0, 0});

  // Calculate position of pixel with coordinate (1, 0)
  const auto second_pixel_position = target.mapPixelToCoords({1, 0});

  // Calculate size of pixel
  const auto pixel_size =
      std::abs(second_pixel_position.x - first_pixel_position.x);

  return pixel_size;
}
}  // namespace HomoGebra

namespace HomoGebra
{
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

void PointBody::Update(const sf::RenderTarget& target,
                       const PointEquation& equation)
{
  // Calculate position
  position_ = CalculatePosition(equation);

  // Point is in real projective plane
  if (position_)
  {
    body_.setPosition(position_.value().position);
    SetNamePosition(position_.value().position);
  }

  // Calculate size of body
  const auto size = CalculateSizeOfBody(target);

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

[[nodiscard]] inline std::optional<sf::Vector2f> IntersectRayWithRectangle(
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
      const HomoGebra::FloatSquaredMatrix matrix(
          {{first_point.x, first_point.y, 1},
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

Distance PointBody::GetDistance(const sf::Vector2f& position) const
{
  if (!position_) return std::numeric_limits<Distance>::max();

  if (position_.value().is_at_infinity)
    return std::numeric_limits<Distance>::max();

  return Length(position_.value().position - position);
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

float PointBody::CalculateSizeOfBody(const sf::RenderTarget& target)
{
  // Calculate size of pixel
  const auto pixel_size = CalculateSizeOfPixel(target);

  // Ratio of size of body to size of pixel
  constexpr float kRatio = 2 * std::numbers::pi_v<float>;

  // Calculate size of body
  const auto size = pixel_size * kRatio;

  // Return size of body
  return size;
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

Distance LineBody::GetDistance(const sf::Vector2f& position) const
{
  if (!equation_) return std::numeric_limits<Distance>::max();

  const auto& [a, b, c] = equation_.value();

  return DistanceToLine(position, a, b, c);
}

float LineBody::Equation::Solve(const Var var, const float another) const
{
  switch (var)
  {
    case Var::kX:
      return (-c - b * another) / a;
    case Var::kY:
      return (-c - a * another) / b;
    default:
      Assert(false, "Invalid variable");
  }
  return float{};
}

void ConicBody::Update(const sf::RenderTarget& target,
                       const ConicEquation& equation)
{
  UpdateEquation(equation);
  UpdateBodyLines(target);
}

void ConicBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Draw lines
  std::ranges::for_each(body_lines.lines_x, [&target](const auto& line)
                        { ThickLineDrawer{}.Draw(target, line, 3.f); });

  std::ranges::for_each(body_lines.lines_y, [&target](const auto& line)
                        { ThickLineDrawer{}.Draw(target, line, 3.f); });
}

Distance ConicBody::GetDistance(const sf::Vector2f& position) const
{
  Distance distance = std::numeric_limits<Distance>::max();
  std::ranges::for_each(
      body_lines.lines_x,
      [&distance, &position](const auto& line)
      {
        std::ranges::for_each(
            line,
            [&distance, &position](const auto& vertex) {
              distance = std::min(distance, Length(vertex.position - position));
            });
      });

  std::ranges::for_each(
      body_lines.lines_y,
      [&distance, &position](const auto& line)
      {
        std::ranges::for_each(
            line,
            [&distance, &position](const auto& vertex) {
              distance = std::min(distance, Length(vertex.position - position));
            });
      });

  return distance;
}

void ConicBody::UpdateEquation(const ConicEquation& equation)
{
  const auto normalizer = Complex{1} / equation.squares.front();

  auto [squares, pair_product, linears, constant] = Equation{};
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

  const auto normalized_square_x =
      equation.squares[static_cast<size_t>(Var::kX)] * normalizer;
  if (!normalized_square_x.IsReal())
  {
    equation_ = std::nullopt;
    return;
  }

  squares[static_cast<size_t>(Var::kX)] = normalized_square_x;
  squares[static_cast<size_t>(Var::kY)] =
      equation.squares[static_cast<size_t>(Var::kY)] * normalizer;

  // F*xy +          || pair product
  pair_product =
      equation.pair_products[static_cast<size_t>(Var::kZ)] * normalizer;

  // E*x*1 + D*y*1 + || linears
  linears[static_cast<size_t>(Var::kX)] =
      equation.pair_products[static_cast<size_t>(Var::kY)] * Complex{1} *
      normalizer;
  linears[static_cast<size_t>(Var::kY)] =
      equation.pair_products[static_cast<size_t>(Var::kX)] * Complex{1} *
      normalizer;

  // C*1^2 = 0       || constant
  constant = equation.squares[static_cast<size_t>(Var::kZ)] * Complex{1} *
             Complex{1} * normalizer;

  equation_ = Equation{squares, pair_product, linears, constant};
}

void ConicBody::UpdateBodyLines(const sf::RenderTarget& target)
{
  auto& [lines_x, lines_y, thickness] = body_lines;
  lines_x.clear();
  lines_y.clear();

  if (!equation_)
  {
    return;
  }

  thickness = CalculateSizeOfBody(target);

  // Acquire render region center and size
  const auto& render_region_center = target.getView().getCenter();
  const auto kDelta = 2.f * sf::Vector2f{thickness, thickness};
  const auto& render_region_size = target.getView().getSize() + kDelta;

  // Calculate render region corner
  const auto corner = render_region_center - render_region_size / 2.f;

  const sf::FloatRect rendering_region{corner, render_region_size};

  // Calculate amount of steps needed and their size
  const size_t steps = std::max(target.getSize().x, target.getSize().y) / 2;
  const auto step_size = render_region_size / static_cast<float>(steps);

  lines_x.reserve(4);
  lines_y.reserve(4);
  lines_x.resize(2);
  lines_y.resize(2);

  for (size_t step = 0; step < steps; ++step)
  {
    // Calculate position of current step
    const auto pos = corner + step_size * static_cast<float>(step);

    // Calculate roots of equation
    // Check if roots are real and add them to line
    auto roots_x = equation_.value().Solve(
        Var::kX, Complex{static_cast<long double>(pos.y)});

    for (size_t root_number = 0; root_number < roots_x.size(); ++root_number)
    {
      auto& root = roots_x[root_number];
      if (root && root.value().IsReal() &&
          rendering_region.contains({static_cast<float>(root.value()), pos.y}))
      {
        lines_x[lines_x.size() - 1 - root_number].emplace_back(sf::Vertex(
            {static_cast<float>(root.value()), pos.y}, sf::Color::Black));
      }
    }

    if (std::ranges::all_of(roots_x,
                            [](const auto& root)
                            {
                              return !root.has_value() ||
                                     !root.value().IsReal();
                            }) /*check for discontinuity*/
        && !lines_x.back().empty() /*check if need to resize*/)
    {
      lines_x.resize(lines_x.size() + roots_x.size());
    }

    // Calculate roots of equation
    // Check if roots are real and add them to line
    auto roots_y = equation_.value().Solve(
        Var::kY, Complex{static_cast<long double>(pos.x)});

    for (size_t root_number = 0; root_number < roots_y.size(); ++root_number)
    {
      auto& root = roots_y[root_number];

      if (root && root.value().IsReal() &&
          rendering_region.contains({pos.x, static_cast<float>(root.value())}))
      {
        lines_y[lines_y.size() - 1 - root_number].emplace_back(sf::Vertex(
            {pos.x, static_cast<float>(root.value())}, sf::Color::Black));
      }
    }

    if (std::ranges::all_of(roots_y,
                            [](const auto& root)
                            {
                              return !root.has_value() ||
                                     !root.value().IsReal();
                            }) /*check for discontinuity*/
        && !lines_y.back().empty() /*check if need to resize*/)
    {
      lines_y.resize(lines_y.size() + roots_y.size());
    }
  }

  Expect(lines_x.size() <= 4);
  Expect(lines_y.size() <= 4);
}

float ConicBody::CalculateSizeOfBody(const sf::RenderTarget& target)
{
  // Calculate size of pixel
  const auto pixel_size = CalculateSizeOfPixel(target);

  // Ratio of size of body to size of pixel
  constexpr float kRatio = std::numbers::pi_v<float>;

  // Calculate size of body
  const auto size = pixel_size * kRatio;

  // Return size of body
  return size;
}

[[nodiscard]] inline std::array<std::optional<Complex>, 2>
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

  const auto discriminant_root = sqrt(discriminant);

  const auto first_root = (-linear_coefficient + discriminant_root) /
                          (Complex{2} * quadratic_coefficient);
  const auto second_root = (-linear_coefficient - discriminant_root) /
                           (Complex{2} * quadratic_coefficient);

  return {first_root, second_root};
}

ConicBody::Equation::Solution ConicBody::Equation::Solve(
    Var var, const Complex& another) const
{
  // Ax^2 + Bxy + Cy^2 + Dx + Ey + F = 0
  // Ax^2 + (By+D)x + (Cy^2 + Ey + F) = 0
  const auto another_var = kAnother[static_cast<size_t>(var)];

  const auto& /* A */ quadratic_coefficient = squares[static_cast<size_t>(var)];

  const auto /* (By+D) */ linear_coefficient =
      /* By */ pair_product * another +
      /* D */ linears[static_cast<size_t>(var)];

  const auto /* (Cy^2 + Ey + F) */ constant_coefficient =
      /* Cy^2 */ squares[static_cast<size_t>(another_var)] * another * another +
      /* Ey */ linears[static_cast<size_t>(another_var)] * another +
      /* F */ constant;

  return SolveQuadraticEquation(quadratic_coefficient, linear_coefficient,
                                constant_coefficient);
}
}  // namespace HomoGebra