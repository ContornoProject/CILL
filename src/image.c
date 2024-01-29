#include <stdlib.h>
#include <contorno.h>

#include "cill.h"
#include "cillmain.h"

CONTORNO_EXPORT unsigned int CILL_ImageChannelType_GetChannelCount(CILLImageChannelType channel_type) {
	switch (channel_type) {
		case CILL_IMAGE_CHANNEL_TYPE_RGB:
			return 3;
			break;
		case CILL_IMAGE_CHANNEL_TYPE_RGBA:
			return 4;
			break;
		default:
			return 0;
	}	
}

void FreeImage(void *img) {
	CILLImage* image;
	
	image = (CILLImage*)img;
	if (!image) {
		return;
	}
		
	switch (image->img_channel_type) {
		case CILL_IMAGE_DATA_TYPE_8BPP:
			Contorno_MemoryManager_Free(&cill_mem_manager, ((CILLImageData8BPP*)image->img_data)->data);
			break;
		case CILL_IMAGE_DATA_TYPE_FLOAT:
			Contorno_MemoryManager_Free(&cill_mem_manager, ((CILLImageDataFloat*)image->img_data)->data);
			break;
	}		
	Contorno_MemoryManager_Free(NULL, image->img_data);
	Contorno_MemoryManager_Free(NULL, image);
}

CONTORNO_EXPORT void CILL_Image_Fill(CILLImage* image, CILLImageChannelType channel_type, CILLImageDataType data_type, unsigned int width, unsigned int height) {
	Contorno_RefCountable_SetFreeFunc((ContornoRefCountable*)image, FreeImage);
	
	image->img_channel_type = channel_type;
	image->img_width = width;
	image->img_height = height;
	image->img_stride = width * CILL_ImageChannelType_GetChannelCount(channel_type);
	
	switch (data_type) {
		case CILL_IMAGE_DATA_TYPE_8BPP:
			image->img_data = Contorno_MemoryManager_Malloc(&cill_mem_manager, sizeof(CILLImageData8BPP));
			break;
		case CILL_IMAGE_DATA_TYPE_FLOAT:
			image->img_data = Contorno_MemoryManager_Malloc(&cill_mem_manager, sizeof(CILLImageDataFloat));
			break;
	}	
	
	image->img_data->data_type = data_type;
	image->img_data->data_size = image->img_stride * image->img_height;
	switch (channel_type) {
		case CILL_IMAGE_DATA_TYPE_8BPP:
			((CILLImageData8BPP*)image->img_data)->data = Contorno_MemoryManager_Calloc(&cill_mem_manager, image->img_data->data_size, sizeof(ContornoUInt8));
			break;
		case CILL_IMAGE_DATA_TYPE_FLOAT:
			((CILLImageDataFloat*)image->img_data)->data = Contorno_MemoryManager_Calloc(&cill_mem_manager, image->img_data->data_size, sizeof(float));
			break;
	}		
}

void FillImageGeneric(void *img) {
	CILL_Image_Fill(img, CILL_IMAGE_CHANNEL_TYPE_RGB, CILL_IMAGE_DATA_TYPE_8BPP, 1, 1);	
}


CONTORNO_EXPORT CILLImage* CILL_Image_Create(CILLImageChannelType channel_type, CILLImageDataType data_type, unsigned int width, unsigned int height) {
	CILLImage* ret;
	ContornoObjectFillFunc* gen_fill_func_arr;
	
	ret = Contorno_MemoryManager_Malloc(&cill_mem_manager, sizeof(CILLImage));
	if (!ret) {
		return NULL;
	}	
	
	gen_fill_func_arr = Contorno_MemoryManager_Calloc(&cill_mem_manager, 2, sizeof(ContornoObjectFillFunc));
	gen_fill_func_arr[0] = FillImageGeneric;
	gen_fill_func_arr[1] = NULL;
	
	Contorno_Object_Fill((ContornoObject*)ret, CILL_IMAGE_TYPE, gen_fill_func_arr, CONTORNO_TRUE);
	CILL_Image_Fill(ret, channel_type, data_type, width, height);
	
	Contorno_MemoryManager_Free(&cill_mem_manager, gen_fill_func_arr);
	
	return ret;
}
