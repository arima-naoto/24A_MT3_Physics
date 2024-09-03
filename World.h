#pragma once
#include "Rendering.h"

class World : public Rendering
{
public:

	void Initialize(Affine affine);

	void CreateAffineMatrix(Affine affine);

private:

	Affine affine_;

	Matrix4x4 worldMatrix_;

};

