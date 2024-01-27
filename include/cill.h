#include <stdio.h>
#include <contorno.h>

#ifndef CILL
#define CILL

#define CILL_IMAGE_TYPE "CILLIMAGEOBJECT"

/* Image */
typedef enum {
    CILL_IMAGE_DATA_TYPE_8BPP,
    CILL_IMAGE_DATA_TYPE_FLOAT
} CILLImageDataType;

typedef enum {
    CILL_IMAGE_CHANNEL_TYPE_RGB,
    CILL_IMAGE_CHANNEL_TYPE_RGBA
} CILLImageChannelType;

typedef struct {
	CILLImageDataType data_type;
	unsigned int data_size;
} CILLImageData;

typedef struct {
	CILLImageData;
	ContornoUInt8* data;
} CILLImageData8BPP;

typedef struct {
	CILLImageData;
	float* data;
} CILLImageDataFloat;

typedef struct {
	ContornoObject;
	
	/* public */
	CILLImageData* img_data;
	CILLImageChannelType img_channel_type;
	unsigned int img_width;
	unsigned int img_height;
	unsigned int img_stride;
	
	/* padding */
	void *img_padding_1;
	void *img_padding_2;
    void *img_padding_3;
} CILLImage;

extern CONTORNO_EXPORT unsigned int CILL_ImageChannelType_GetChannelCount(CILLImageChannelType channel_type);
extern CONTORNO_EXPORT CILLImage* CILL_Image_Create(CILLImageChannelType channel_type, CILLImageDataType data_type, unsigned int width, unsigned int height);

/* Loader Interface */
typedef void (*CILLLoadFunc)(FILE *);
typedef void (*CILLSaveFunc)(FILE *);
typedef char** (*CILLSupportedMimesDynamicFunc)(void);

typedef struct {
	ContornoObject;

	/* public */
	ContornoModule* loader_module;
	char** loader_supported_mimes;
	CILLSupportedMimesDynamicFunc loader_supported_mimes_dyn;
	CILLLoadFunc loader_load_func;
	CILLSaveFunc loader_save_func;
	
	/* padding */
	void *loader_pad_1;
	void *loader_pad_2;
    void *loader_pad_3;
} CILLLoader;

#endif
