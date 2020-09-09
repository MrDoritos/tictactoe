#pragma once
#include "box.h"
#include "player.h"
#include "png.h"
#include "boxsize.h"

static const png xDesign = png("x.png");
static const png oDesign = png("o.png");
	
struct spot {
	public:
	spot(int spx, int spy)		
	{
		x = spx;
		y = spy;
		taken = false;
	}
	spot() {}
	int x, y;
	bool taken;
	player* player;
	void draw(box* camera, boxsize& square) {
		if (!taken)
			return;
		boxsize old = boxsize(square);
		const float margin = 0.2f;		
		square.offsetX += old.getscaleX(margin);
		square.offsetY += old.getscaleY(margin);
		square.sizeX -= old.getscaleX(margin * 2);
		square.sizeY -= old.getscaleY(margin * 2);
		char* fb = camera->getFramebuffer();
		png* image = player->cpu ? (png*)&xDesign : (png*)&oDesign;
		for (int x = 0; x < square.sizeX; x++) {
			for (int y = 0; y < square.sizeY; y++) {
				fb[camera->get(x + square.offsetX, y + square.offsetY)] = image->getSample(x, y, &square)->negativeValue() > 0.5 ? '#' : ' ';
			}
		}
		#ifdef TTT_DEBUG
		//if taken		
		camera->set(taken ? 1 : 0, 2, old.offsetX, old.offsetY + 1);
		//owner
		camera->set((int)player, 12, old.offsetX+2, old.offsetY + 1);		
		#endif
	}
	private:
};