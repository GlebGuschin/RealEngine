#pragma once

#ifndef __ANIMATOR_HPP__
#define __ANIMATOR_HPP__

#include "Animation.hpp"


class Animator : public Referenced {

public:

	//const Matrix4x4& getMatrix(unsigned index) const { return palette[index]; }

	void playSequency(const Name& name);

};



#endif

