#ifndef H_shape
#define H_shape

struct Interval
{
	Interval() = default; //!< Default constructor without initialisation.
	Interval(real a, real b): inf(a), sup(b) {} //!< Construct interval `[a,b]`.
	Interval(Interval const& interval) = default; //!< Default copy constructor.
	real inf, sup; 
}

struct LineSegment
{
	LineSegment() = default //!< Default constructor without initialisation.
	//! Construct line segment from `p1` to `p2`.
	LineSegment(real2 p1, real2 p2): p1(p1), p2(p2) {}
	LineSegment(LineSegment const& interval) = default; //!< Copy constructor.
	real2 p1, p2; //!< Line segment extremities.
}

struct Disk //TODO useless, because dynamic+radius will be used in blobs ?
{
	real2 c; //!< Center of the disk
	real r; //!< Radius of the disk's boundary circle.
}



#endif

