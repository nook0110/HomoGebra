#pragma once
#include "GeometricObject.h"
#include "Input.h"
#include "Plane.h"

template <class GeometricObjectType>
class ObjectSelectorBody
{
 public:
  explicit ObjectSelectorBody(Plane* plane)
      : plane_(plane), object_getter_(plane)
  {}

  /**
   * \brief Draws the body.
   *
   */
  void Draw();

  /**
   * \brief Set selected object.
   *
   * \param object Object to set with.
   */
  void SetObject(GeometricObjectType* object);

  /**
   * \brief Get selected object.
   *
   * \return Selected object.
   */
  [[nodiscard]] GeometricObjectType* GetObject() const;

 private:
  /**
   * \brief Draws name of selected object.
   *
   */
  void DrawName();

  /**
   * \brief Draws list to choose object from.
   *
   */
  void DrawList();

  /**
   * \brief Draws setter through last nearest object.
   *
   */
  void DrawSetter();

  GeometricObjectType* object_{};
  Plane* plane_;
  NearbyObjectGetter<GeometricObjectType> object_getter_;

  int current_object_ = 0;
};

template ObjectSelectorBody<GeometricObject>;
template ObjectSelectorBody<Point>;
template ObjectSelectorBody<Line>;
template ObjectSelectorBody<Conic>;