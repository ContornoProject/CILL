#include <stdlib.h>
#include <contorno.h>

#include "cill.h"

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

CONTORNO_EXPORT CILLImage* CILL_Image_Create(CILLImageChannelType channel_type, CILLImageDataType data_type, unsigned int width, unsigned int height) {
	CILLImage* ret;
	
	ret = Contorno_MemoryManager_Malloc(NULL, sizeof(CILLImage));
	if (!ret) {
		return NULL;
	}	
	
	ret->img_channel_type = channel_type;
	ret->img_width = width;
	ret->img_height = height;
	ret->img_stride = width * CILL_ImageChannelType_GetChannelCount(channel_type);
	
	switch (data_type) {
		case CILL_IMAGE_DATA_TYPE_8BPP:
			ret->img_data = Contorno_MemoryManager_Malloc(NULL, sizeof(CILLImageData8BPP));
			break;
		case CILL_IMAGE_DATA_TYPE_FLOAT:
			ret->img_data = Contorno_MemoryManager_Malloc(NULL, sizeof(CILLImageDataFloat));
			break;
	}	
	if (!ret->img_data) {
		Contorno_MemoryManager_Free(NULL, ret);
		return NULL;
	}	
	
	ret->img_data->data_type = data_type;
	ret->img_data->data_size = ret->img_stride * ret->img_height;
	switch (channel_type) {
		case CILL_IMAGE_DATA_TYPE_8BPP:
			((CILLImageData8BPP*)ret->img_data)->data = Contorno_MemoryManager_Calloc(NULL, ret->img_data->data_size, sizeof(ContornoUInt8));
			if (!((CILLImageData8BPP*)ret->img_data)->data) {
				Contorno_MemoryManager_Free(NULL, ret);
				return NULL;
			}
			break;
		case CILL_IMAGE_CHANNEL_TYPE_RGBA:
			((CILLImageDataFloat*)ret->img_data)->data = Contorno_MemoryManager_Calloc(NULL, ret->img_data->data_size, sizeof(float));
			if (!((CILLImageData8BPP*)ret->img_data)->data) {
				Contorno_MemoryManager_Free(NULL, ret);
				return NULL;
			}
			break;
	}		
	
	return ret;
}
