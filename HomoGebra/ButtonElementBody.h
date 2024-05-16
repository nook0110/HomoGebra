#pragma once
#include "GeometricObject.h"
#include "Input.h"
#include "Plane.h"

namespace HomoGebra
{ /**
   * \brief Represents the body of an ObjectSelector.
   *
   * The ObjectSelectorBody class is responsible for managing the selection of
   * geometric objects in a plane. It provides methods to set and get the
   * selected object, as well as drawing the body of the selector, including the
   * name of the selected object and a list of objects to choose from.
   *
   * \tparam GeometricObjectType The type of geometric object to be selected.
   */
template <class GeometricObjectType>
class ObjectSelectorBody : public PlaneObserver
{
 public:
  /**
   * \brief Constructs an ObjectSelectorBody object.
   *
   * \param plane The plane to associate with the ObjectSelectorBody.
   */
  explicit ObjectSelectorBody(Plane* plane)
      : plane_(plane), object_getter_(plane)
  {
    plane->Attach(this);
  }

  /**
   * \brief Draws the body of the ObjectSelector.
   *
   * This method is responsible for drawing the body of the ObjectSelector,
   * including the name of the selected object and a list of objects to choose
   * from.
   */
  void Draw();

  /**
   * \brief Sets the selected object.
   *
   * \param object The object to set as the selected object.
   */
  void SetObject(GeometricObjectType* object);

  /**
   * \brief Gets the selected object.
   *
   * \return The selected object.
   */
  [[nodiscard]] GeometricObjectType* GetObject() const;

  /**
   * \brief Updates the ObjectSelectorBody when an object is removed from the
   * plane.
   *
   * \param object_removed The event data for the object removed event.
   */
  void Update(const PlaneEvent::ObjectRemoved& object_removed) override;

 private:
  /**
   * \brief Draws the name of the selected object.
   *
   * This method is responsible for drawing the name of the selected object.
   */
  void DrawName();

  /**
   * \brief Draws the list of objects to choose from.
   *
   * This method is responsible for drawing the list of objects to choose from.
   */
  void DrawList();

  /**
   * \brief Draws the setter through the last nearest object.
   *
   * This method is responsible for drawing the setter through the last nearest
   * object.
   */
  void DrawSetter();

  GeometricObjectType* object_{};
  Plane* plane_;
  NearbyObjectGetter<GeometricObjectType> object_getter_;

  int current_object_ = -1;
};
}  // namespace HomoGebra
