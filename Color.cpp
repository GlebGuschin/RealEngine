
#include "stdafx.h"

#include "Color.hpp"



const Color Color::BLACK = Color( 0.0, 0.0, 0.0, 1.0 ) ;
const Color Color::RED = Color( 1.0, 0.0, 0.0, 1.0 ) ;
const Color Color::GREEN = Color( 0.0, 1.0, 0.0, 1.0 ) ;
const Color Color::BLUE = Color( 0.0, 0.0, 1.0, 1.0 ) ;
const Color Color::WHITE = Color( 1.0, 1.0, 1.0, 1.0 ) ;
const Color Color::GRAY = Color( 0.5, 0.5, 0.5, 1.0 ) ;
const Color Color::YELLOW = Color(0.0, 1.0, 1.0, 1.0);
const Color Color::CYAN = Color(0.0, 0.5, 1.0, 1.0);
const Color Color::PINK = Color(1.0, 0.5, 0.0, 1.0);


Color Color::Random() { return Color(FloatRandom(), FloatRandom(), FloatRandom()); }



