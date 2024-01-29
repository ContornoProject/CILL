#include <stdio.h>
#include <contorno.h>

#ifndef CILL
#define CILL

#define CILL_IMAGE_TYPE "CILLIMAGEOBJECT"

/* Main */
extern CONTORNO_EXPORT void CILL_Init();

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
extern CONTORNO_EXPORT CILLImage* CILL_Image_LoadFromFilename(char* filename);
extern CONTORNO_EXPORT void CILL_Image_Fill(CILLImage* image, CILLImageChannelType channel_type, CILLImageDataType data_type, unsigned int width, unsigned int height);

/* Loader Interface */
typedef CILLImage* (*CILLLoadFunc)(FILE *);
typedef void (*CILLSaveFunc)(CILLImage *, FILE *);
typedef void (*CILLInitFunc)(void);

#define CILL_LOAD_FUNC_NAME "CillLoader_Load"
#define CILL_SAVE_FUNC_NAME "CillLoader_Save"
#define CILL_PROBE_FUNC_NAME "CillLoader_Probe"
#define CILL_INIT_FUNC_NAME "CillLoader_Init"

typedef struct {
	char* mime;
	char* extension;
} CILLLoaderSupportedFT;
typedef CILLLoaderSupportedFT** (*CILLProbeSupportedFTsFunc)(void);

typedef struct {
	ContornoObject;

	/* public */
	ContornoModule* loader_module;
	CILLLoadFunc loader_load_func;
	CILLSaveFunc loader_save_func;
	CILLInitFunc loader_init_func;
	CILLProbeSupportedFTsFunc loader_probe_func;
	CILLLoaderSupportedFT** loader_supported_fts;
	
	/* padding */
	void *loader_pad_1;
	void *loader_pad_2;
    void *loader_pad_3;
} CILLLoader;

#endif
