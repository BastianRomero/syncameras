// Proyecto1_fotografiar.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <EmergentCameraAPIs.h>
#include <emergentframe.h>
#include <EvtParamAttribute.h>
#include <gigevisiondeviceinfo.h>
#include <EmergentFrameSave.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>  

#include <string>   
#include <iomanip> 
#include <sstream>
#include <thread> 

#include<windows.h>

using namespace std;
using namespace Emergent;
using namespace cv;

#define SUCCESS 0
#define MAX_FRAMES 100

#define MAX_CAMERAS 4

#define TRUE  1
#define FALSE 0

#define GAIN_VAL      256
#define OFFSET_VAL    0
#define AG_SET_VAL    512
#define AG_I_VAL      16

//void configure_defaults(CEmergentCamera* camera);
char* next_token;

void open_camera() {


}


int main()
{
    printf("Librerias cargadas con exito \n");

    CEmergentCamera camera;

    cout << "Cargando Variable" << endl;

    struct EvtParamAttribute attribute;
    int ReturnVal = SUCCESS;
    unsigned int param_val_max, param_val_min, param_val_inc;
    unsigned int height_max, width_max;
    unsigned int height_final, width_final;
    CEmergentFrame evtFrame;
    char filename[100];
    char user[50];
    struct GigEVisionDeviceInfo deviceInfo[MAX_CAMERAS];
    unsigned int count;
    unsigned int camera_index = 0;
    EVT_ERROR err = EVT_SUCCESS;


    cout << "Primera prueba para capturar fotogramas" << endl;
    cout << "1- Se intentara visualizar las imagenes guardando todas en el mismo archivo" << endl;
    cout << "2- Se intentara guardar los fotogramas para visualizarlos (Ahora como imagen, luego como video)" << endl;

    unsigned int listcam_buf_size = MAX_CAMERAS;
    EVT_ListDevices(deviceInfo, &listcam_buf_size, &count);

    if (count == 0)
    {
        printf("No camera found\n");
        return 0;
    }

#ifdef XML_FILE
    ReturnVal = EVT_CameraOpen(&camera, &deviceInfo[camera_index], XML_FILE);
#else
    ReturnVal = EVT_CameraOpen(&camera, &deviceInfo[camera_index]);
#endif
    if (ReturnVal != SUCCESS)
    {
        printf("Open Camera: \t\tError. Exiting program.\n");
        return ReturnVal;
    }
    else
    {
        printf("Open Camera: \t\tCamera Opened\n\n");
    }

    EVT_CameraGetUInt32ParamMax(&camera, "Height", &height_max);
    EVT_CameraGetUInt32ParamMax(&camera, "Width", &width_max);
    printf("Resolution: \t\t%d x %d\n", width_max, height_max);
    /* EVT_CameraSetUInt32Param(&camera, "Height", H);
     EVT_CameraSetUInt32Param(&camera, "Width", W);
     EVT_CameraGetUInt32Param(&camera, "Height", &height_final);
     EVT_CameraGetUInt32Param(&camera, "Width", &width_final);
     printf("Resolution: \t\t%d x %d\n", width_final, height_final);*/



    ReturnVal = EVT_CameraGetParamAttr(&camera, "Gain", &attribute);
    if (attribute.dataType == EDataTypeUnsupported)
    {
        printf("CameraGetParamAttr: Error\n");
        return ReturnVal;
    }
    else
    {
        EVT_CameraGetUInt32ParamMax(&camera, "Gain", &param_val_max);
        printf("Gain Max: \t\t%d\n", param_val_max);
        EVT_CameraGetUInt32ParamMin(&camera, "Gain", &param_val_min);
        printf("Gain Min: \t\t%d\n", param_val_min);
        EVT_CameraGetUInt32ParamInc(&camera, "Gain", &param_val_inc);
        printf("Gain Inc: \t\t%d\n", param_val_inc);
        if (GAIN_VAL >= param_val_min && GAIN_VAL <= param_val_max)
        {
            EVT_CameraSetUInt32Param(&camera, "Gain", GAIN_VAL);
            printf("Gain Set: \t\t%d\n", GAIN_VAL);
        }
    }

    ReturnVal = EVT_CameraGetParamAttr(&camera, "Offset", &attribute);
    if (attribute.dataType == EDataTypeUnsupported)
    {
        printf("CameraGetParamAttr: Error\n");
        return ReturnVal;
    }
    else
    {
        EVT_CameraGetUInt32ParamMax(&camera, "Offset", &param_val_max);
        printf("Offset Max: \t\t%d\n", param_val_max);
        EVT_CameraGetUInt32ParamMin(&camera, "Offset", &param_val_min);
        printf("Offset Min: \t\t%d\n", param_val_min);
        EVT_CameraGetUInt32ParamInc(&camera, "Offset", &param_val_inc);
        printf("Offset Inc: \t\t%d\n", param_val_inc);
        if (OFFSET_VAL >= param_val_min && OFFSET_VAL <= param_val_max)
        {
            EVT_CameraSetUInt32Param(&camera, "Offset", OFFSET_VAL);
            printf("Offset Set: \t\t%d\n", OFFSET_VAL);
        }
    }

    ReturnVal = EVT_CameraGetParamAttr(&camera, "LUTEnable", &attribute);
    if (attribute.dataType == EDataTypeUnsupported)
    {
        printf("CameraGetParamAttr: Error\n");
        return ReturnVal;
    }
    else
    {
        unsigned int lut_val_max, lut_val_min, lut_val_inc;
        unsigned int lut_addr_max, lut_addr_min, lut_addr_inc;
        EVT_CameraGetUInt32ParamMax(&camera, "LUTValue", &lut_val_max);
        printf("LUT Value Max: \t\t%d\n", lut_val_max);
        EVT_CameraGetUInt32ParamMin(&camera, "LUTValue", &lut_val_min);
        printf("LUT Value Min: \t\t%d\n", lut_val_min);
        EVT_CameraGetUInt32ParamInc(&camera, "LUTValue", &lut_val_inc);
        printf("LUT Value Inc: \t\t%d\n", lut_val_inc);
        EVT_CameraGetUInt32ParamMax(&camera, "LUTIndex", &lut_addr_max);
        printf("LUT Index Max: \t\t%d\n", lut_addr_max);
        EVT_CameraGetUInt32ParamMin(&camera, "LUTIndex", &lut_addr_min);
        printf("LUT Index Min: \t\t%d\n", lut_addr_min);
        EVT_CameraGetUInt32ParamInc(&camera, "LUTIndex", &lut_addr_inc);
        printf("LUT Index Inc: \t\t%d\n", lut_addr_inc);


        for (unsigned int lut_addr = lut_addr_min; lut_addr <= lut_addr_max; lut_addr++)
        {
            EVT_CameraSetUInt32Param(&camera, "LUTIndex", lut_addr); //Address we are setting value for...
            EVT_CameraSetUInt32Param(&camera, "LUTValue", lut_addr); //and value to set(just val=addr).
        }

        EVT_CameraSetBoolParam(&camera, "LUTEnable", TRUE); //Enable LUT we just programmed.

        printf("LUT table: \t\tWrote linear table. Enabled.\n");
    }
    ReturnVal = EVT_CameraGetParamAttr(&camera, "AutoGain", &attribute);
    if (attribute.dataType == EDataTypeUnsupported)
    {
        printf("CameraGetParamAttr: Error\n");
        return ReturnVal;
    }
    else
    {
        unsigned int ag_set_val_max, ag_set_val_min, ag_set_val_inc;
        unsigned int ag_I_val_max, ag_I_val_min, ag_I_val_inc;

        EVT_CameraGetUInt32ParamMax(&camera, "AutoGainSet", &ag_set_val_max);
        printf("AG Set Point Max: \t%d\n", ag_set_val_max);
        EVT_CameraGetUInt32ParamMin(&camera, "AutoGainSet", &ag_set_val_min);
        printf("AG Set Point Min: \t%d\n", ag_set_val_min);
        EVT_CameraGetUInt32ParamInc(&camera, "AutoGainSet", &ag_set_val_inc);
        printf("AG Set Point Inc: \t%d\n", ag_set_val_inc);
        EVT_CameraGetUInt32ParamMax(&camera, "AutoGainIGain", &ag_I_val_max);
        printf("AG Rate Max: \t\t%d\n", ag_I_val_max);
        EVT_CameraGetUInt32ParamMin(&camera, "AutoGainIGain", &ag_I_val_min);
        printf("AG Rate Min: \t\t%d\n", ag_I_val_min);
        EVT_CameraGetUInt32ParamInc(&camera, "AutoGainIGain", &ag_I_val_inc);
        printf("AG Rate Inc: \t\t%d\n", ag_I_val_inc);

        if (AG_SET_VAL >= ag_set_val_min && AG_SET_VAL <= ag_set_val_max)
        {
            EVT_CameraSetUInt32Param(&camera, "AutoGainSet", AG_SET_VAL);
            printf("AG Set Point: \t\t%d\n", AG_SET_VAL);
        }

        if (AG_I_VAL >= ag_I_val_min && AG_I_VAL <= ag_I_val_max)
        {
            EVT_CameraSetUInt32Param(&camera, "AutoGainIGain", AG_I_VAL);
            printf("AG Rate Set: \t\t%d\n", AG_I_VAL);
        }

        EVT_CameraSetBoolParam(&camera, "AutoGain", TRUE);
        printf("AutoGain Set: \t\tEnabled.\n");
    }

    ReturnVal = EVT_CameraOpenStream(&camera);
    if (ReturnVal != SUCCESS)
    {
        printf("CameraOpenStream: Error\n");
        return ReturnVal;
    }

    evtFrame.size_x = width_max;
    evtFrame.size_y = height_max;
    evtFrame.pixel_type = GVSP_PIX_MONO8; //Covers color model using BayerGB8 also.
    EVT_AllocateFrameBuffer(&camera, &evtFrame, EVT_FRAME_BUFFER_ZERO_COPY);
    EVT_CameraQueueFrame(&camera, &evtFrame);


    unsigned int frames_recd = 0;
    // for (int frame_count = 0; frame_count < MAX_FRAMES; frame_count++)
    for (; ;)

    {
        int frame_count = 1;
        ReturnVal = EVT_CameraExecuteCommand(&camera, "AcquisitionStart");
        //Tell camera to start streaming
        if (ReturnVal != SUCCESS)
        {
            printf("CameraExecuteCommand: Error\n");
            return ReturnVal;
        }

        err = EVT_CameraGetFrame(&camera, &evtFrame, EVT_INFINITE);
        if (err)
            printf("EVT_CameraGetFrame Error!\n");
        else
            frames_recd++;

        EVT_CameraExecuteCommand(&camera, "AcquisitionStop");


#ifdef _MSC_VER
        sprintf_s(filename, "D:/images/myimage_%d.tif", frame_count);
        //sprintf_s(filename, "myimage_%d.jpg", frame_count);
#else
        sprintf(filename, "myimage_%d.tif", frame_count);
#endif
        EVT_FrameSave(&evtFrame, filename, EVT_FILETYPE_TIF, EVT_ALIGN_NONE);

        EVT_CameraQueueFrame(&camera, &evtFrame);  //Now re-queue.

        //printf(". %p", &fra);
        Mat fra;
        fra = imread("D:/images/myimage_1.tif", IMREAD_COLOR);
        namedWindow("ventana", WINDOW_NORMAL);
        imshow("ventana", fra);
        waitKey(3);

#ifndef _MSC_VER 
        fflush(stdout);
#endif    

       // if (waitKey(10) == 27) break;
}

}

