#pragma once
#include "Enemy.h"
/*
Non-rotated Box		NRB
Circle Box			CB
Rotated Box			RB
*/



bool hitCheckNRBNRB(const Enemy&, const Enemy&);
bool hitCheckNRBCB(const Enemy&, const Enemy&);
bool hitCheckNRBRB(const Enemy&, const Enemy&);

bool hitCheckCBCB(const Enemy&, const Enemy&);
bool hitCheckCBRB(const Enemy&, const Enemy&);

bool hitCheckRBRB(const Enemy&, const Enemy&);

#include "HitboxCalc.inl"