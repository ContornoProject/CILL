#include <stdio.h>
#include <stdlib.h>

#include <cill.h>

int main(void) {
	CILLImage* image;
	
	image = CILL_Image_Create(CILL_IMAGE_CHANNEL_TYPE_RGB, CILL_IMAGE_DATA_TYPE_8BPP, 320, 240);
	Contorno_RefCountable_Unref((ContornoRefCountable*)image);
}
