#ifndef _MEGALIB1_H_
#define _MEGALIB1_H_


#pragma pack(push,1)

//---------------------------------------------------------------------------
//   MegaPixel Ltd. 01.09.2006 Init and close function Version 6
//---------------------------------------------------------------------------
extern "C" 
{
UINT     _MPCreate(VOID);
VOID     _MPRelease(VOID);
}
//---------------------------------------------------------------------------
//   MegaPixel Ltd. 01.09.2006 Input Devices Service Version 6
//---------------------------------------------------------------------------
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |   \
                ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))
#define HDEVICE  UINT

enum MPCaptureProperty
{
   CAPTURE_BRIGHTNESS,
   CAPTURE_EXPOSURE,
   CAPTURE_SHARPNESS,
   CAPTURE_WHITE_BALANCE,
   CAPTURE_HUE,
   CAPTURE_SATURATION,
   CAPTURE_GAMMA,
   CAPTURE_IRIS,
   CAPTURE_FOCUS,
   CAPTURE_ZOOM,
   CAPTURE_PAN,
   CAPTURE_TILT,
   CAPTURE_ROLL,
   CAPTURE_SHUTTER,
   CAPTURE_GAIN,
   CAPTURE_BACKLIGHT,
   CAPTURE_TRIGGER_DELAY,
   CAPTURE_FRAME_RATE,
   CAPTURE_FRAME_RATE_SLIDER,
   CAPTURE_CONTRAST,
   CAPTURE_COLOR_MODE,
   CAPTURE_CHROMAU,
   CAPTURE_CHROMAV,
   CAPTURE_CUSTOM_FRAME,
   CAPTURE_FRAME_MODE,
   CAPTURE_SETUP_DIALOG,
   CAPTURE_NAME,
   CAPTURE_SERIAL_NUMBER,
   CAPTURE_CROSSBAR,
   CAPTURE_STANDARD,
   CAPTURE_FIELD_MODE,
   CAPTURE_COMPRESSION
   };

enum MPAudioProperty                                                       //new
{
   AUDIOCAPTURE_ENABLED,
   AUDIOCAPTURE_MONO,
   AUDIOCAPTURE_RECORDLEVEL,
   AUDIOCAPTURE_PAN,
   AUDIOCAPTURE_LOUDNESS,
   AUDIOCAPTURE_TREBLE,
   AUDIOCAPTURE_BASS,
   AUDIOCAPTURE_CAPTUREMODE,
   AUDIOCAPTURE_NAME,
   AUDIOCAPTURE_SERIAL_NUMBER
   };

typedef struct TPropertyData {
	bool Present;
        INT  Value;
        INT  DefaultValue;
	INT  MinValue;
	INT  MaxValue;
        INT  SteppingDelta;
	bool AutoEnabled;
	bool Auto;
	bool OnOffEnabled;
	bool OnOff;
	bool OnePushEnabled;
	bool OnePush;
        void *Data;
        } PROPERTYDATA;


typedef struct TInputParam {
        UINT ColorMode;
        UINT InputMode;
	UINT Brightness;
	UINT Contrast;
	UINT ChromaV;
	UINT ChromaU;
	UINT Hue;
        } TINPUTPARAMS;

typedef struct TDeviceProperty {
        UINT NumberInLines;
        UINT NumberOutLines;
        UINT NumberChannels;
	UINT MaxHorFrameSize;
	UINT MaxVerFrameSize;
        UINT DeviceFlags;
	UINT NumberAudioChannels;                                          //new
        } TDEVICEPROPERTY;

typedef struct TChannelProperty {
	UINT HorFrameSize;
	UINT VerFrameSize;
	UINT PixelMode;
	UINT ColorCode;
	UINT ChannelFlags;
	UINT Reserved;
        } TCHANNELPROPERTY;

typedef struct TAudioProperty {                                            //new
        WORD  wFormatTag;
        WORD  nChannels;
        DWORD nSamplesPerSec;
        DWORD nAvgBytesPerSec;
        WORD  nBlockAlign;
        WORD  wBitsPerSample;
        WORD  cbSize;
        } TAUDIOPROPERTY;

extern "C" {
UINT      _IDGetVersion(void);
HDEVICE   _IDAdd(char *DeviceName,UINT mode);
VOID      _IDClose(HDEVICE Hdv);
VOID      _IDCloseAll(void);
UINT      _IDGetNumberDevices(void);
UINT      _IDGetMaxEnabledChannels(UINT type);                              //new
UINT      _IDGetDeviceInfo(HDEVICE Hdv);

UINT      _IDGetMaxChannels(void);
UINT      _IDGetMaxAudioChannels(void);                                     //new
UINT      _IDGetMaxInLines(void);                                           //new
UINT      _IDGetMaxOutLines(void);                                          //new

VOID      _IDGetDeviceProperty(HDEVICE Hdv,TDEVICEPROPERTY *);
VOID      _IDSetDeviceProperty(HDEVICE Hdv,TDEVICEPROPERTY *);
VOID      _IDGetChannelProperty(HDEVICE Hdv,UINT Channel, TCHANNELPROPERTY *);
VOID      _IDGetChannelAudioProperty(HDEVICE Hdv,UINT Channel, TAUDIOPROPERTY *);  //new
VOID      _IDGetPicture(HDEVICE Hdv,UINT *ImgTegg,VOID **Images);
VOID      _IDGetAudioBuffer(HDEVICE Hdv,UINT *AudioTegg,VOID **AudioBuffers);   //new
VOID      _IDSetParams(HDEVICE Hdv,UINT Channel,TINPUTPARAMS *Params);
VOID      _IDInput(HDEVICE Hdv,UINT *UsesChannels);
VOID      _IDInputAudio(HDEVICE Hdv,UINT *UsesChannels);                        //new
VOID      _IDSetOutLine(HDEVICE Hdv,UINT Line,UINT value);
UINT      _IDGetInLine(HDEVICE Hdv,UINT Line);
PCHAR     _IDGetName(HDEVICE Hdv);
PCHAR     _IDGetSN(HDEVICE Hdv);
HDEVICE   _IDGetDevices(UINT number);
UINT      _IDGetFirstChannel(HDEVICE Hdv);

UINT      _IDGetCaptureProperty(HDEVICE Hdv,UINT Channel, MPCaptureProperty Prop,PROPERTYDATA *chProp);
UINT      _IDSetCaptureProperty(HDEVICE Hdv,UINT Channel, MPCaptureProperty Prop,PROPERTYDATA chProp);
UINT      _IDGetAudioProperty(HDEVICE Hdv,UINT Channel, MPAudioProperty Prop,PROPERTYDATA *chProp);  //new
UINT      _IDSetAudioProperty(HDEVICE Hdv,UINT Channel, MPAudioProperty Prop,PROPERTYDATA chProp);   //new

VOID      _CHGetProperty(UINT Channel, TCHANNELPROPERTY *);
VOID      _CHGetChannelAudioProperty(UINT Channel, TAUDIOPROPERTY *);              //new
VOID      _CHGetPicture(UINT *ImgTegg,VOID **Images);
VOID      _CHGetAudioBuffer(UINT *AudioTegg,VOID **AudioBuffers);           //new
VOID      _CHSetParams(UINT Channel,TINPUTPARAMS *Params);
VOID      _CHInput(UINT *UsesChannels);
VOID      _CHInputAudio(UINT *UsesAudioChannels);                           //new
VOID      _CHStart(UINT Channel,UINT Priority);
VOID      _CHStop(UINT Channel);
VOID      _CHStartAudio(UINT AudioChannel);                                 //new
VOID      _CHStopAudio(UINT AudioChannel);                                  //new
VOID      _CHSetOutLine(UINT Line,UINT value);
UINT      _CHGetInLine(UINT Line);
HDEVICE   _CHGetDevice(UINT Channel);

HDEVICE   _CHGetVideoDevice(UINT VideoChannel);                             //new
HDEVICE   _CHGetAudioDevice(UINT AudioChannel);                             //new
HDEVICE   _CHGetInLineDevice(UINT Line);                                    //new
HDEVICE   _CHGetOutLineDevice(UINT Line);                                   //new
PCHAR     _CHGetVideoName(UINT VideoChannel);                               //new
PCHAR     _CHGetAudioName(UINT AudioChannel);                               //new
PCHAR     _CHGetInLineName(UINT Line);                                      //new
PCHAR     _CHGetOutLineName(UINT Line);                                     //new

UINT      _CHGetCaptureProperty(UINT Channel, MPCaptureProperty Prop,PROPERTYDATA *chProp);
UINT      _CHSetCaptureProperty(UINT Channel, MPCaptureProperty Prop,PROPERTYDATA chProp);
UINT      _CHGetAudioProperty(UINT Channel, MPAudioProperty Prop,PROPERTYDATA *chProp);   //new
UINT      _CHSetAudioProperty(UINT Channel, MPAudioProperty Prop,PROPERTYDATA chProp);    //new

}
//Open error code
#define ERRORDEVICESLIMIT       0
#define ERRORDEVICESECURITY     1
#define ERRORDEVICELOAD         2
#define ERRORDEVICEOPEN         3
#define ERRORDEVICEUSE          4
#define ERRORDEVICECODE         5
#define ERRORDEVICEMAXCHANNELS  6
//Input Picture flags "ImgTegg"
#define NOPICTURE               0
#define PICTUREREADY            1
#define INPUTUNCONNECTED        2
//---------------------------------------------------------------------------
//   MegaPixel Ltd. 01.09.2006 Car Plate Version 6
//---------------------------------------------------------------------------
typedef struct TNumInitParam {
        UINT CarThreshold;
	UINT ZoneThreshold;
	UINT ZoneMode;
	RECT Zone_visio;
	UINT Thhory;
	UINT Thhorx;
	UINT Thbin;
	UINT Min_Pipe_Size;
	UINT Max_Pipe_Size;
        } NUMINITPARAMS;

#define ZONE_MODE_96x24   0x00000001
#define ZONE_MODE_128x32  0x00000002
#define ZONE_MODE_160x40  0x00000008
#define ZONE_MODE_192x48  0x00000004
#define ZONE_MODE_256x64  0x00000010
#define ZONE_MODE_320x80  0x00000020
#define ZONE_MODE_384x96  0x00000040

#define ZONE_MODE_48x48   0x00000080
#define ZONE_MODE_64x64   0x00000100
#define ZONE_MODE_80x80   0x00000200
#define ZONE_MODE_96x96   0x00000400
#define ZONE_MODE_128x128 0x00000800
#define ZONE_MODE_160x160 0x00001000
#define ZONE_MODE_192x192 0x00002000

typedef struct TNumInitRecognitionParam {
        UINT SymbolRecFlag;
	UINT ZoneRecFlag;
	UINT ErrorCorrectionTime;
	UINT WeightTreshold;
	UINT Reserved0;
	UINT Reserved1;
	UINT Reserved2;
        } NUMINITRECPARAMS;

#define ZONE_ENABLED_CHECK_SIZE      0x00000001
#define ZONE_ENABLED_CHECK_WEIGHT    0x00000002
#define ZONE_ENABLED_CHECK_GIPOTIZE  0x00000004
#define ZONE_ENABLED_CHECK_LOST      0x00000008

#define SYM_ENABLED_CLEARNUMBER    0x00000001
#define SYM_ENABLED_CORRECTION     0x00000002
#define SYM_ENABLED_DELETEZONES    0x00000004

typedef struct TZoneResult {
        UINT    Flag;
        UINT    Status;
	UINT    Resolution;
	RECT    Position;
        CHAR    PlateNumber[16];
        CHAR    PlateGipotiz[16];
        UINT    Heght;
        INT     Angle;
        UINT    Weight;
        UINT    Width;
        UINT    Color;
        UINT    PeekValue;
        UINT    Direction;
	UINT    Speed;
        PVOID   Image_Gray;
        PVOID   Image_Bin;
        PVOID   Image_Lap;
        PVOID   Image_Mask;
        PVOID   Image_Pipe;
        } PLATERESULT;

//Resolution zone
#define ZONE_RESOLUTION_96x24   0
#define ZONE_RESOLUTION_128x32  1
#define ZONE_RESOLUTION_160x40  3
#define ZONE_RESOLUTION_192x48  2
#define ZONE_RESOLUTION_256x64  4
#define ZONE_RESOLUTION_320x80  5
#define ZONE_RESOLUTION_384x96  6

#define ZONE_RESOLUTION_48x48   10
#define ZONE_RESOLUTION_64x64   11
#define ZONE_RESOLUTION_80x80   12
#define ZONE_RESOLUTION_96x96   13
#define ZONE_RESOLUTION_128x128 14
#define ZONE_RESOLUTION_160x160 15
#define ZONE_RESOLUTION_192x192 16

extern "C" {
UINT      _CFGetVersion(VOID);

UINT      _CFOpen(UINT country,char *libpath);
VOID      _CFClose(UINT error);
VOID      _CFRestart(HDEVICE Hdv,UINT Channel,NUMINITPARAMS *Params);
VOID      _CFSetRecognitionParams(HDEVICE Hdv,UINT Channel,NUMINITRECPARAMS *Params);    //new
UINT      _CFRun(HDEVICE Hdv,UINT Channel,void *imgbuf,UINT flag);
UINT      _CFQuery(HDEVICE Hdv,UINT Channel,UINT QueryFlag);
UINT      _CFGetResult(HDEVICE Hdv,UINT Channel,UINT QueryFlag,UINT NumberQuery,PLATERESULT *Result);
VOID      _CFSetChannelProperty(HDEVICE Hdv,UINT Channel, UINT sizex, UINT sizey, UINT PixelMode);
VOID      _CFSetProperty(HDEVICE Hdv, UINT sizex, UINT sizey, UINT PixelMode);

VOID      _CFCHRestart(UINT Channel,NUMINITPARAMS *Params);
VOID      _CFCHSetRecognitionParams(UINT Channel,NUMINITRECPARAMS *Params);    //new
UINT      _CFCHRun(UINT Channel,void *imgbuf,UINT flag);
UINT      _CFCHQuery(UINT Channel,UINT QueryFlag);
UINT      _CFCHGetResult(UINT Channel,UINT QueryFlag,UINT NumberQuery,PLATERESULT *Result);
VOID      _CFCHSetChannelProperty(UINT Channel, UINT sizex, UINT sizey, UINT PixelMode);

}
// Return values ***************************************************************
#define NOT_FOUND 		0
#define NUMBER_CORRECTED	1
#define ONLY_ZONE		2
#define FATAL_ERROR		3
#define ERROR_KEY		16
#define DOUBLE_FRAME		0x80
// Query Flag Values ***********************************************************
#define RESULT_CORRECTION	1
#define RESULT_LOST		2
#define RESULT_PRELOST		4
#define RESULT_CARPOSITION	8
#define RESULT_FINDZONE	        0x10
// PixelMode Flags *************************************************************
#define SQUARE_PIXELS	        2
#define DOUBLEFIELD_PIXELS      4
#define WIDE_PIXELS	        1
#define GRAY_PIXELS	        8
#define RGB_PIXELS	        0x10
#define UYVY_PIXELS	        0x20
#define YUY2_PIXELS	        0x40
#define Y411_PIXELS	        0x80
#define JPEG_PIXELS	        0x100
// ChannelFlags flag  **********************************************************
#define MSENABLED 0x0
#define CFENABLED 0x1
#define MDENABLED 0x2
#define TFENABLED 0x4
// RunMode flag (Function CFRun TFRun) *****************************************
#define RUN_FRAME               1
#define RUN_FIELD	        0
#define RUN_ZONEONLY	        2
//Device property flags "DeviceFlags"
#define TVSTANDARD              0x00000001
#define PROGRESIVE              0x00000002
#define SQUAREPIXELS	        0x00000004
#define WIDEPIXELS	        0x00000008
#define ADJUSTENABLED	        0x00000010
#define PRIORITYENABLED	        0x00000020
#define RGBPIXELS	        0x00000040
#define UYVYPIXELS	        0x00000080
#define GRAYPIXELS	        0x00000100
#define YUY2PIXELS	        0x00000200
#define Y411PIXELS	        0x00000400
#define JPEGPIXELS	        0x00000800
#define DEVCFENABLED	        0x00010000
#define DEVMDENABLED	        0x00020000
#define DEVTFENABLED	        0x00040000
//TV Standard
#define TVSTANDARD_NONE         0
#define TVSTANDARD_PAL          1
#define TVSTANDARD_NTSC         2
#define TVSTANDARD_SECAM        3
//------------------------------------------------------------------------------
//   MegaPixel Ltd. 01.09.2006 Motion Library Version 6
//------------------------------------------------------------------------------
#define MDVERSION 0x0600
#define MAXZONES 32
typedef struct TMotion {
	UINT MotionThresholdLow;
	UINT MotionThresholdMedium;
	UINT MotionThresholdHigh;
        UINT MotionNoiseReductionLow;
        UINT MotionNoiseReductionMedium;
        UINT MotionNoiseReductionHigh;
	UINT AdaptTime;
        UINT SSDetectTime;
        UINT SSMotionb;
	UINT ThzoneLowDown[MAXZONES];
	UINT ThzoneLowUp[MAXZONES];
	UINT ThzoneMediumDown[MAXZONES];
	UINT ThzoneMediumUp[MAXZONES];
	UINT ThzoneHighDown[MAXZONES];
	UINT ThzoneHighUp[MAXZONES];
	UINT ThzoneSDDDown[MAXZONES];
	UINT ThzoneSDDUp[MAXZONES];
        char *ZoneMask;
        UINT Quality;
        UINT DetectFlag;
	UINT SDDResolution;
	UINT SDDThreshold;
	UINT SDDDetectTime;
	UINT SDDk1;
	UINT SDDk2;
	UINT SDDk3;
	UINT SDDk4;
	UINT SDDNoiseReduction;
        UINT SDDMotionb1;
        UINT SDDMotionb2;
	UINT SDDUseZone[MAXZONES];
	} MOTIONINITPARAMS;

typedef struct TMotionResult {
	UINT resultLow;
	UINT resultMedium;
	UINT resultHigh;
	UINT resultSDD;
	} MOTIONRESULT;

// Motion function and parameters **********************************************
extern "C" {
UINT      _MDGetVersion(VOID);

VOID      _MDSetParam(HDEVICE Hdv,UINT Channel,MOTIONINITPARAMS *ChParams);
VOID      _MDRestart(HDEVICE Hdv,UINT Channel);
UINT      _MDRun(HDEVICE Hdv,UINT Channel,MOTIONRESULT *MotResult,void *imgbuf,UINT Flags,char *mask);
VOID      _MDSetChannelProperty(HDEVICE Hdv,UINT Channel, UINT sizex, UINT sizey, UINT PixelMode);
VOID      _MDSetProperty(HDEVICE Hdv,UINT sizex, UINT sizey, UINT PixelMode);
VOID      _MDLoadMask(HDEVICE Hdv,UINT Channel,VOID *Msk);

VOID      _MDCHSetParam(UINT Channel,MOTIONINITPARAMS *ChParams);
VOID      _MDCHRestart(UINT Channel);
UINT      _MDCHRun(UINT Channel,MOTIONRESULT *MotResult,void *imgbuf,UINT Flags,char *mask);
VOID      _MDCHSetChannelProperty(UINT Channel, UINT sizex, UINT sizey, UINT PixelMode);
VOID      _MDCHLoadMask(UINT Channel,VOID *Msk);
}
//******************************************************************************
#define SDD_DETECT_MEDIUM       0
#define SDD_DETECT_LOW	        1
#define SDD_DETECT_HIGH	        2
#define MOT_DETECT_LOW 	        0x40
#define MOT_DETECT_MEDIUM 	0x80
#define MOT_DETECT_HIGH 	0x100
//------------------------------------------------------------------------------
//   MegaPixel Ltd. 01.09.2006 TrnFlow Library Version 6
//------------------------------------------------------------------------------
extern "C" {
UINT      _TFGetVersion(VOID);

UINT      _TFOpen(char *libpath);
VOID      _TFClose(UINT error);
VOID      _TFRestart(HDEVICE Hdv,UINT Channel,NUMINITPARAMS *Params);
VOID      _TFSetRecognitionParams(HDEVICE Hdv,UINT Channel,NUMINITRECPARAMS *Params);    //new
UINT      _TFRun(HDEVICE Hdv,UINT Channel,void *imgbuf,UINT flag);
UINT      _TFQuery(HDEVICE Hdv,UINT Channel,UINT QueryFlag);
UINT      _TFGetResult(HDEVICE Hdv,UINT Channel,UINT QueryFlag,UINT NumberQuery,PLATERESULT *Result);
VOID      _TFSetChannelProperty(HDEVICE Hdv,UINT Channel, UINT sizex, UINT sizey, UINT PixelMode);
VOID      _TFSetProperty(HDEVICE Hdv, UINT sizex, UINT sizey, UINT PixelMode);

VOID      _TFCHRestart(UINT Channel,NUMINITPARAMS *Params);
VOID      _TFCHSetRecognitionParams(UINT Channel,NUMINITRECPARAMS *Params);    //new
UINT      _TFCHRun(UINT Channel,void *imgbuf,UINT flag);
UINT      _TFCHQuery(UINT Channel,UINT QueryFlag);
UINT      _TFCHGetResult(UINT Channel,UINT QueryFlag,UINT NumberQuery,PLATERESULT *Result);
VOID      _TFCHSetChannelProperty(UINT Channel, UINT sizex, UINT sizey, UINT PixelMode);
}
//******************************************************************************
extern "C" {
VOID      _YUY2toRGB(PVOID inb,PVOID obuf,UINT SizeX,UINT SizeY);
VOID      _UYVYtoRGB(PVOID inb,PVOID obuf,UINT SizeX,UINT SizeY);

VOID      _UYVYtoGRAY(PVOID inb,PVOID oim,UINT SizeX,UINT SizeY);
VOID      _YUY2toGRAY(PVOID inb,PVOID oim,UINT SizeX,UINT SizeY);
VOID      _RGBtoGRAY(PVOID inb,PVOID oim,UINT SizeX,UINT SizeY);

VOID      _GRAYtoUYVY(PVOID inb,PVOID oim,UINT SizeX,UINT SizeY);
VOID      _GRAYtoYUY2(PVOID inb,PVOID oim,UINT SizeX,UINT SizeY);

VOID      _GRAYHREDUCE(PVOID inb,PVOID oim,UINT SizeX,UINT SizeY);
VOID      _UYVYHREDUCE(PVOID inb,PVOID oim,UINT SizeX,UINT SizeY);
VOID      _YUY2HREDUCE(PVOID inb,PVOID oim,UINT SizeX,UINT SizeY);
VOID      _RGBHREDUCE(PVOID inb,PVOID obuf,UINT SizeX,UINT SizeY);
}

#pragma pack(pop)

#endif


