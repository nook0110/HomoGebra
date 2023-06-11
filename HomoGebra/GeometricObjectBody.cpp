#include "GeometricObjectBody.h"

#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include <cassert>
#include <utility>

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
  name_ = std::move(name);
  text_.setString(name_);
}

const std::string& ObjectName::GetName() const { return name_; }

void ObjectName::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Apply transform
  states.transform *= getTransform();
  // Draw
  target.draw(text_, states);
}

PointBody::PointBody() { body_.setFillColor(sf::Color::Red); }

void PointBody::SetName(std::string name) { text_.SetName(std::move(name)); }

const std::string& PointBody::GetName() const { return text_.GetName(); }

void PointBody::Update(const PointEquation& equation, const float size)
{
  // Calculate position
  position_ = CalculatePosition(equation);

  if (position_)
  {
    body_.setPosition(position_.value().position);
    text_.setPosition(position_.value().position);
  }

  // Set size
  body_.setRadius(size);
  body_.setOrigin(size, size);
}

void PointBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (!position_) return;

  if (const auto& [position, is_at_infinity] = position_.value();
      is_at_infinity)
  {
    // Draw point at infinity
    DrawArrow(target, states);
  }
  else
  {
    // Draw point
    target.draw(body_, states);
    target.draw(text_, states);
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
  assert(position_);

  const auto& [position, is_at_infinity] =
      position_.value();  // NOLINT(bugprone-unchecked-optional-access)

  assert(is_at_infinity);

  const auto& view = target.getView();
  const auto intersection = std::optional<sf::Vector2f>{};

  assert(intersection.has_value());

  // Coefficient for start of line.
  constexpr auto kStartShift = 0.9f;
  const auto arrow_start = intersection.value() * kStartShift +
                           view.getCenter() * (1.f - kStartShift);
  constexpr auto kEndShift = 0.95f;
  const auto arrow_end =
      intersection.value() * kEndShift + view.getCenter() * (1.f - kEndShift);

  thor::Arrow arrow{arrow_start, arrow_end, sf::Color::Black, 10};
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
  auto normalized_equation = equation.equation.GetNormalized();

  // Check if line is in 'real' plane
  if (!(normalized_equation.x.IsReal() && normalized_equation.y.IsReal()))
  {
    equation_ = std::nullopt;
  }

  Equation body_equation;
  body_equation.a =
      static_cast<float>(static_cast<long double>(normalized_equation.x));
}

void LineBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {}

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
      assert(false);
      return 0.f;
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
  const auto window_center = target.getView().getCenter();
  const auto window_size = target.getView().getSize();

  const auto corner = window_center - window_size / 2.f;

  // Calculates distance between
  auto find_distance =
      [](const sf::Vector2f first, const sf::Vector2f second = sf::Vector2f{})
  {
    const auto delta = second - first;
    return std::hypot(delta.x, delta.y);
  };

  constexpr size_t kSteps = 1000;
  const auto step_size = window_size / static_cast<float>(kSteps);

  const auto max_distance = find_distance(step_size) * 2.f;

  using Line = std::vector<sf::Vertex>;
  using Lines = std::vector<Line>;

  Lines lines;

  for (size_t step = 0; step < kSteps; ++step)
  {
    const auto pos = corner + step_size * static_cast<float>(step);

    auto roots_y = equation_.Solve(Var::kY, pos.x);

    auto roots_x = equation_.Solve(Var::kX, pos.y);

    std::vector<sf::Vector2f> points_to_add;
    for (auto& root : roots_y)
    {
      if (root && root.value().IsReal())
      {
        points_to_add.emplace_back(pos.x, root.value().real());
      }
    }

    for (auto& root : roots_x)
    {
      if (root && root.value().IsReal())
      {
        points_to_add.emplace_back(root.value().real(), pos.y);
      }
    }

    auto find_line = [&](const sf::Vector2f& point)
    {
      return std::find_if(lines.begin(), lines.end(),
                          [&](const Line& line)
                          {
                            if (line.empty()) return true;

                            return find_distance(line.back().position, point) <
                                   max_distance;
                          });
    };

    for (auto& point : points_to_add)
    {
      if (auto suitable = find_line(point); suitable == lines.end())
      {
        lines.emplace_back(Line{{point, sf::Color::Black}});
      }
      else
      {
        suitable->push_back({point, sf::Color::Black});
      }
    }
  }

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
  const auto another_var = kAnother[static_cast<size_t>(var)];

  const auto quadratic_coefficient = squares[static_cast<size_t>(var)];
  const auto linear_coefficient = pair_product * another;
  const auto constant_coefficient =
      squares[static_cast<size_t>(another_var)] * another * another + constant;

  return SolveQuadraticEquation(quadratic_coefficient, linear_coefficient,
                                constant_coefficient);
}