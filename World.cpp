#include "World.h"

void World::Initialize(Affine affine) {
	affine_ = affine;
}

void World::CreateAffineMatrix(Affine affine) {

	worldMatrix_ = Rendering::SRTAffineMatrix(affine);

}