#pragma once
#include "Coordinate.h"
#include "Observer.h"

namespace HomoGebra
{
/**
 * \brief Construction that loses its properties after projective
 * transformation.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 *
 * \see StrongTransformation
 */
class WeekConstruction
{
 public:
  /**
   * \brief Gets transformation which was applied on the object.
   *
   * \return Transformation which was applied on the object.
   */
  [[nodiscard]] const Transformation& GetTransformation() const;

 private:
  Transformation
      transformation_;  //!< Transformation which was applied on the object.
};

/**
 * \brief Construction that does not lose its properties after projective
 * transformation.
 *
 * \author nook0110
 *
 * \version 0.1
 *
 * \date April 2023
 *
 * \see WeekTransformation
 */
class StrongConstruction
{};

/**
 * \brief Defines how object is created.
 *
 * \author nook0110
 *
 * \version 1.0
 *
 * \date February 2023
 *
 * \details Updates positions of objects
 * \see GeometricObjectImplementation
 */
class Construction : public GeometricObjectObserver
{
 public:
  /**
   * \brief Default destructor.
   *
   */
  ~Construction() override = default;

  /**
   * \brief Gets object that is constructed.
   *
   * \return Object that is constructed.
   */
  [[nodiscard]] virtual GeometricObject* GetObject() const = 0;

  /**
   * \brief Recalculates equation of the object.
   *
   */
  virtual void RecalculateEquation() = 0;

  void Update(const ObjectEvent::Moved& moved_event) override;

  void Update(const ObjectEvent::GoingToBeDestroyed& destroyed_event) override =
      0;

  void Update(const ObjectEvent::Renamed& renamed_event) override = 0;

 protected:
  /**
   * \brief Constructor deleted.
   *
   */
  Construction() = default;
};
}  // namespace HomoGebra