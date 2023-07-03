#pragma once

/*
* 	Drawing order:
* ==================
* Background
* Background Effects
* Enemy Back effects
* Enemy Sprites
* Enemy Front effects
* Enemy Front effects (Vertex)
* Bullet (Includes effects)
* Enemy Text / Bubbles
* Portraits
* Portrait effects
* Portrait Text
* UI
* UI Effects
* UI Text
* FPS Counter //Not counted
*/


typedef enum {
	//Render Texture
	BACKGROUND,
	BACKGROUND_FX,

	ENEMYBACK_FX,

	ENEMY,

	ENEMYFRONT_FX,
	ENEMYFRONT_FX_V,

	ENEMY_TEXT,

	PORTRAIT,
	PORTRAIT_FX,
	PORTRAIT_TEXT,
	//
	UI,
	UI_FX,
	UI_TEXT

} drawLayer;