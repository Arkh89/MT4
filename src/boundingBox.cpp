#include "boundingBox.hpp"

BoundingBox::BoundingBox(void)
 : Body()
{ }

BoundingBox::BoundingBox(const Vect2D& pos0, double _m, double _k, double _W, double _H)
 : Body(pos0, _m, _k), W(_W), H(_H)
{ }

BoundingBox::BoundingBox(const Vect2D& pos0, const Vect2D& v0, double _m, double _k, double _W, double _H)
 : Body(pos0, v0, _m, _k), W(_W), H(_H)
{ }

BoundingBox::BoundingBox(const Vect2D& pos0, const Vect2D& v0, double _m, double _k, const Vect2D& _R, double _W, double _H)
 : Body(pos0, v0, _m, _k, _R), W(_W), H(_H)
{ }

BoundingBox::BoundingBox(const Vect2D& pos0, const Vect2D& v0, double _m, double _k, const Vect2D& _R, double _tI, double _W, double _H)
 : Body(pos0, v0, _m, _k, _R, _tI), W(_W), H(_H)
{ }

BoundingBox::~BoundingBox(void)
{ }
