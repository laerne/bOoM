#ifndef HEADERBoOm_Entity
#define HEADERBoOm_Entity

#include "GenericEntity.hpp"
#include "components/graphic.hpp"

namespace bOoM {

//This is the entity with standard bOoM components.
using Entity = GenericEntity<Renderable>;

} //namespace bOoM
#endif


