#ifndef H_blob
#define H_blob

#include <cstdint>
#include <vector>
#include "math2d.hpp"
#include "dynamic.hpp"
namespace bOoM {

struct BlobZone
// The shape of blob is assumed to be always a CIRCLE
// The color mode of a blob is assumed to be [0,1] greyscale fill.
// All blob are assumed to behave the same (i.e. with the same class/struct type)
{
// Physical properties
  //! Position, velocity and acceleratio of the entity represented by the zone
	OrientedDynamic movement;
  //! center of mass relative to the local movement reference system.
	real2 centerOfMass;
// Blobs
	LCZHierarchy lczs;
}

//! Locally Connected Zone Hierarchy
struct LCZHierarchy {
}

struct LCZBranch {
  real2 centerOfBCirc;
  real radiusOfBCirc;
}

struct LCZLeaf {
  real2 centerOfBCirc;
  real radiusOfBCirc;
  std::vector<Blob_RH_FU_C> localBlobs;
}

struct LCZNode {
  std::uint8 flags;
  union {
    LCZBranch branch;
    LCZLeaf leaf;
  };
}




//Blobs
// R: Round shape
// --
// H: cubic Hill field
// P: cubic Plate field
// ------
// F: fixed dynamics
// D: moving dynamics
// --
// O: Oriented dynamics
// U: Unoriented dynamics
// ------
// C: Constant color

struct Blob_RH_FU_C
{
  real2 pos;
  CubicHillField fphys;
};

} //namespace bOoM
#endif

