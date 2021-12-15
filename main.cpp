/* 
 * File:   main.cpp
 * Author: Lucas Wolfgang
 * Created on 20 de Janeiro de 2018, 14:12
 */

#include <jni.h>
#include "ftd2xx.h"

#define BUFFER_SIZE 4078
#define MAX_TEXT_SIZE 100

static const char DEVICE_DESCRIPTOR_CLASS[] = "web/DeviceDescriptor";
static const char DEVICE_CLASS[] = "web/Device";

#ifdef MAX_NUM_DEVICES
#undef MAX_NUM_DEVICES // defined in WinTypes.h
#endif

static const int MAX_NUM_DEVICES = 127;

#ifndef _Included_web_Device
#define _Included_web_Device
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
JNIEXPORT jint JNICALL Java_web_Device_printHello(JNIEnv* env, jobject deviceDescriptor,jlong handle){
    DWORD RxBytes; 
    FT_HANDLE ftHandle = (FT_HANDLE)handle;

    FT_GetQueueStatus(ftHandle,&RxBytes); 
    
    return RxBytes;
}

/*********************        DEVICE DESCRIPTOR       *************************/

/**
 * Sets a field of type <code>long</code> with in a <code>DeviceDescriptor</code>.
 *
 * @param env The JNI environment pointer.
 * @param deviceDescriptor The <code>DeviceDescriptor</code> object to operate on.
 * @param fieldName The name of the field to set.
 * @param value The value to set.
 */
static void SetLongField(JNIEnv* env, jobject deviceDescriptor, const char* fieldName, DWORD value){
    jclass descClass = NULL;
    jfieldID fieldID = NULL;

    if(env->ExceptionCheck() == JNI_TRUE) return;

    descClass = env->GetObjectClass(deviceDescriptor);
    if(descClass == NULL){ return; }

    fieldID = env->GetFieldID(descClass, fieldName, "J");
    if(fieldID == NULL){ return; }

    env->SetLongField(deviceDescriptor, fieldID, value);
}

/**
 * Retrieves the value of a field of type <code>long</code> from a <code>DeviceDescriptor</code>.
 *
 * @param env The JNI environment pointer.
 * @param deviceDescriptor The <code>DeviceDescriptor</code> object to operate on.
 * @param fieldName The name of the field to set.
 * @return The value of the field.
 */
static DWORD GetLongField(JNIEnv* env, jobject deviceDescriptor, const char* fieldName){
    jclass descClass = NULL;
    jfieldID fieldID = NULL;
    
    if(env->ExceptionCheck() == JNI_TRUE) return 0;

    descClass = env->GetObjectClass(deviceDescriptor);
    if(descClass == NULL){ return 0; }

    fieldID = env->GetFieldID(descClass, fieldName, "J");
    if(fieldID == NULL){ return 0; }

    return (DWORD)env->GetLongField(deviceDescriptor, fieldID);
}


/**
 * Sets a field of type <code>int</code> with in a <code>DeviceDescriptor</code>.
 *
 * @param env The JNI environment pointer.
 * @param deviceDescriptor The <code>DeviceDescriptor</code> object to operate on.
 * @param fieldName The name of the field to set.
 * @param value The value to set.
 */
static void SetIntField(JNIEnv* env, jobject deviceDescriptor, const char* fieldName, WORD value){
    jclass descClass = NULL;
    jfieldID fieldID = NULL;

    if(env->ExceptionCheck() == JNI_TRUE) return;

    descClass = env->GetObjectClass(deviceDescriptor);
    if(descClass == NULL){ return; }

    fieldID = env->GetFieldID(descClass, fieldName, "I");
    if(fieldID == NULL){ return; }

    env->SetIntField(deviceDescriptor, fieldID, value);
}

/**
 * Retrieves the value of a field of type <code>int</code> from a <code>DeviceDescriptor</code>.
 *
 * @param env The JNI environment pointer.
 * @param deviceDescriptor The <code>DeviceDescriptor</code> object to operate on.
 * @param fieldName The name of the field to set.
 * @return The value of the field.
 */
static WORD GetIntField(JNIEnv* env, jobject deviceDescriptor, const char* fieldName){
    jclass descClass = NULL;
    jfieldID fieldID = NULL;

    if(env->ExceptionCheck() == JNI_TRUE) return 0;

    descClass = env->GetObjectClass(deviceDescriptor);
    if(descClass == NULL){ return 0; }

    fieldID = env->GetFieldID(descClass, fieldName, "I");
    if(fieldID == NULL){ return 0; }

    return env->GetIntField(deviceDescriptor, fieldID);
}

/**
 * Sets a field of type <code>boolean</code> with in a <code>DeviceDescriptor</code>.
 *
 * @param env  The JNI environment pointer.
 * @param deviceDescriptor The <code>DeviceDescriptor</code> object to operate on.
 * @param fieldName The name of the field to set.
 * @param value The value to set.
 */
static void SetBooleanField(JNIEnv* env, jobject deviceDescriptor, const char* fieldName, WORD value){
    jclass descClass = NULL;
    jfieldID fieldID = NULL;

    /* if an exception was thrown do nothing */
    if(env->ExceptionCheck() == JNI_TRUE) return;

    descClass = env->GetObjectClass(deviceDescriptor);
    if(descClass == NULL){ return; }

    fieldID = env->GetFieldID(descClass, fieldName, "Z");
    if(fieldID == NULL){ return; }

    env->SetBooleanField(deviceDescriptor, fieldID, value);
}

/**
 * Retrieves the value of a field of type <code>boolean</code> from a <code>DeviceDescriptor</code>.
 *
 * @param env The JNI environment pointer.
 * @param deviceDescriptor The <code>DeviceDescriptor</code> object to operate on.
 * @param fieldName The name of the field to set.
 * @return The value of the field.
 */
static WORD GetBooleanField(JNIEnv* env, jobject deviceDescriptor, const char* fieldName){
    jclass descClass = NULL;
    jfieldID fieldID = NULL;

    if(env->ExceptionCheck() == JNI_TRUE) return 0;

    descClass = env->GetObjectClass(deviceDescriptor);
    if(descClass == NULL){ return JNI_FALSE; }

    fieldID = env->GetFieldID(descClass, fieldName, "Z");
    if(fieldID == NULL){ return JNI_FALSE; }

    return env->GetBooleanField(deviceDescriptor, fieldID);
}

/**
 * Sets a field of type <code>java.lang.String</code> with in a <code>DeviceDescriptor</code>.
 *
 * @param env The JNI environment pointer.
 * @param deviceDescriptor The <code>DeviceDescriptor</code> object to operate on.
 * @param fieldName The name of the field to set.
 * @param value The value to set.
 */
static void SetStringField(JNIEnv* env, jobject deviceDescriptor, const char* fieldName, const char* value){
    jclass descClass = NULL;
    jfieldID fieldID = NULL;
    jstring string = NULL;

    if(env->ExceptionCheck() == JNI_TRUE) return;

    descClass = env->GetObjectClass(deviceDescriptor);
    if(descClass == NULL){ return; }

    fieldID = env->GetFieldID(descClass, fieldName, "Ljava/lang/String;");
    if(fieldID == NULL){ return; }

    string = env->NewStringUTF(value);
    if(string == NULL){ return; }

    env->SetObjectField(deviceDescriptor, fieldID, string);
}

/**
 * Retrieves the value of a field of type <code>java.lang.String</code> from a <code>DeviceDescriptor</code>.
 *
 * @param env The JNI environment pointer.
 * @param deviceDescriptor The <code>DeviceDescriptor</code> object to operate on.
 * @param fieldName The name of the field to set.
 * @param buffer The buffer to copy the java string to.
 */
static void GetStringField(JNIEnv* env, jobject deviceDescriptor, const char* fieldName, char* buffer){
    jclass descClass = NULL;
    jfieldID fieldID = NULL;
    jstring string = NULL;
    const char* utfChars;

    /* if an exception was thrown do nothing */
    if(env->ExceptionCheck() == JNI_TRUE) return;

    descClass = env->GetObjectClass(deviceDescriptor);
    if(descClass == NULL){ return; }

    fieldID = env->GetFieldID(descClass, fieldName, "Ljava/lang/String;");
    if(fieldID == NULL){ return; }

    string = (jstring)env->GetObjectField(deviceDescriptor, fieldID);
    utfChars = env->GetStringUTFChars(string, NULL);

    strcpy(buffer, utfChars);

    env->ReleaseStringUTFChars(string, utfChars);
}

jobject CreateDeviceDescriptor(JNIEnv* env, const FT_PROGRAM_DATA* data){
    const char* deviceDescriptorClassName = DEVICE_DESCRIPTOR_CLASS;
    jclass deviceDescriptorClass = NULL;
    jmethodID constructor = NULL;
    jobject deviceDescriptor = NULL;

    deviceDescriptorClass = env->FindClass(deviceDescriptorClassName);
    if(deviceDescriptorClass == NULL){ return NULL; }

    constructor = env->GetMethodID(deviceDescriptorClass, "<init>", "()V");
    if(deviceDescriptorClass == NULL){ return NULL; }

    deviceDescriptor = env->NewObject(deviceDescriptorClass, constructor);
    if(deviceDescriptor == NULL){ return NULL; }
    
    printf("Fill DeviceDescriptor\n");
    if(env->ExceptionCheck() == JNI_TRUE) return NULL;
    SetLongField(env, deviceDescriptor, "signature1", data->Signature1);
    SetLongField(env, deviceDescriptor, "signature2", data->Signature2);
    SetLongField(env, deviceDescriptor, "version", data->Version);
    SetIntField(env, deviceDescriptor, "vendorID", data->VendorId);
    SetIntField(env, deviceDescriptor, "productID", data->ProductId);
    SetStringField(env, deviceDescriptor, "manufacturer", data->Manufacturer);
    SetStringField(env, deviceDescriptor, "manufacturerID", data->ManufacturerId);
    SetStringField(env, deviceDescriptor, "productDescription", data->Description);
    SetStringField(env, deviceDescriptor, "serialNumber", data->SerialNumber);
    SetIntField(env, deviceDescriptor, "maxPower", data->MaxPower);
    SetBooleanField(env, deviceDescriptor, "pnpEnabled", data->PnP);
    SetBooleanField(env, deviceDescriptor, "selfPowered", data->SelfPowered);
    SetBooleanField(env, deviceDescriptor, "remoteWakeupCapable", data->RemoteWakeup);
    
    printf("DeviceDescriptor created \n");    
    return deviceDescriptor;
}

/**
 * Fills the data to write to the EEPROM according to a particular
 * @param env The JNI environment pointer.
 * @param deviceDescriptor The <code>DeviceDescriptor</code> object to operate on.
 * @param data The data to write to the EEPROM.
 */
void FillProgramData(JNIEnv* env, jobject deviceDescriptor, FT_PROGRAM_DATA* data){

    if(env->ExceptionCheck() == JNI_TRUE) return;

    data->Signature1 = GetLongField(env, deviceDescriptor, "signature1");
    data->Signature2 = GetLongField(env, deviceDescriptor, "signature2");
    data->Version = GetLongField(env, deviceDescriptor, "version");
    data->VendorId = GetIntField(env, deviceDescriptor, "vendorID");
    data->ProductId = GetIntField(env, deviceDescriptor, "productID");

    GetStringField(env, deviceDescriptor, "manufacturer", data->Manufacturer);
    GetStringField(env, deviceDescriptor, "manufacturerID", data->ManufacturerId);
    GetStringField(env, deviceDescriptor, "productDescription", data->Description);
    GetStringField(env, deviceDescriptor, "serialNumber", data->SerialNumber);

    data->MaxPower = GetIntField(env, deviceDescriptor, "maxPower");
    data->PnP = GetBooleanField(env, deviceDescriptor, "pnpEnabled");
    data->SelfPowered = GetBooleanField(env, deviceDescriptor, "selfPowered");
    data->RemoteWakeup = GetBooleanField(env, deviceDescriptor, "remoteWakeupCapable");
}

/*********************             DEVICE             *************************/

JNIEXPORT jlong JNICALL Java_web_Device_open(JNIEnv *env, jclass deviceClass ,jlong deviceIndex){
    FT_HANDLE ftHandle = NULL;
    FT_Open(deviceIndex, &ftHandle);
    return (jlong)ftHandle;
  }

JNIEXPORT jint JNICALL Java_web_Device_close(JNIEnv *env, jclass deviceClass, jlong handle){
    FT_HANDLE ftHandle = (FT_HANDLE)handle;
    FT_STATUS result = FT_OK;
    result = FT_Close(ftHandle);
    return result;
 }

JNIEXPORT jint JNICALL Java_web_Device_config(JNIEnv *env, jclass deviceClass, jlong handle, jlong bufferSize, jint baundRate, jint rxTime, jint txTime){
    FT_HANDLE ftHandle = (FT_HANDLE)handle;
    FT_STATUS result = FT_OK;
    FT_SetBaudRate(ftHandle, baundRate);
    if(result != FT_OK){ return result; }
    result = FT_SetUSBParameters(ftHandle, (DWORD)bufferSize, (DWORD)bufferSize);
    if(result != FT_OK){ return result; }
    result = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_2, FT_PARITY_ODD);
    if(result != FT_OK){ return result; }
    result = FT_SetFlowControl(ftHandle,FT_FLOW_NONE, 0,0);   //Podemos ver também CTS,RTS
    if(result != FT_OK){ return result; }
    result = FT_SetTimeouts(ftHandle, rxTime, txTime);
    if(result != FT_OK){ return result; }
    result = FT_Purge(ftHandle, FT_PURGE_RX | FT_PURGE_TX);
    if(result != FT_OK){ return result; }
    return result;
 }

JNIEXPORT jobjectArray JNICALL Java_web_Device_listDevices(JNIEnv *env, jclass service){

    jclass deviceClass = NULL;
    jobjectArray devices = NULL;
    jmethodID deviceConstructor = NULL;
    DWORD numDevices = 0;
    DWORD i = 0;

    FT_DEVICE_LIST_INFO_NODE deviceList[MAX_NUM_DEVICES];
    FT_STATUS result = FT_CreateDeviceInfoList(&numDevices);
    if(result != FT_OK){ return NULL; }

    result = FT_GetDeviceInfoList(deviceList, &numDevices);
    if(result != FT_OK){ return NULL; }

    deviceClass = env->FindClass(DEVICE_CLASS);
    if(deviceClass == NULL){ return NULL; }

    devices = env->NewObjectArray(numDevices, deviceClass, NULL);
    if(devices == NULL){ return NULL; }

    deviceConstructor = env->GetMethodID(deviceClass, "<init>", "(JJ)V");
    if(deviceConstructor == NULL){ return NULL; }

    /* Create devices by their location IDs and fill devices array  */
    for(i = 0; i < numDevices; i++){
        jobject device = NULL;

        device = env->NewObject(deviceClass, deviceConstructor, (jlong)i, (jlong)deviceList[i].Type);
        if(device == NULL) { return NULL; }

        env->SetObjectArrayElement(devices, i, device);
        if(env->ExceptionCheck() == JNI_TRUE) { return NULL; }
    }
    return devices;
  }

JNIEXPORT jint JNICALL Java_web_Device_read (JNIEnv *env, jclass deviceClass, jlong handle, jbyteArray buffer, jint offset, jint length){
    DWORD numBytesRead = -1;
    jbyte* nativeBuffer = (jbyte*)malloc(length * sizeof(jbyte));
    DWORD RxBytes; 
    FT_HANDLE ftHandle = (FT_HANDLE)handle;
    
    FT_GetQueueStatus(ftHandle,&RxBytes); 
    env->GetByteArrayRegion(buffer, offset, length, nativeBuffer);  
    FT_Read(ftHandle, nativeBuffer, (DWORD)length, &numBytesRead);
    env->SetByteArrayRegion(buffer, offset, length, nativeBuffer);
    free(nativeBuffer);
    return RxBytes;
  }

JNIEXPORT jint JNICALL Java_web_Device_write (JNIEnv *env, jclass deviceClass, jlong handle, jbyteArray buffer, jint offset, jint length) {

    FT_HANDLE ftHandle = (FT_HANDLE)handle;
    FT_STATUS result = FT_OK;
    DWORD totalBytesWritten = 0;
    jbyte* nativeBuffer = (jbyte*)malloc(length * sizeof(jbyte));

    env->GetByteArrayRegion(buffer, offset, length, nativeBuffer);

    if(env->ExceptionCheck() == JNI_FALSE){
        while(result == FT_OK && totalBytesWritten < (DWORD)length) {
            DWORD numBytesWritten = 0;
            result = FT_Write(ftHandle, &nativeBuffer[offset + totalBytesWritten], ((DWORD)length) - totalBytesWritten, &numBytesWritten);
            totalBytesWritten += numBytesWritten;
        }
        printf("Final Result %lu \n",result);
    }
    free(nativeBuffer);
    return result;
}

JNIEXPORT jobject JNICALL Java_web_Device_readDeviceDescriptor (JNIEnv *env, jclass eeprom, jlong handle){

    FT_STATUS result = FT_OK;
    FT_HANDLE ftHandle = (FT_HANDLE)handle;

    char manufacturer[MAX_TEXT_SIZE] = {0};
    char manufacturerID[MAX_TEXT_SIZE] = {0};
    char description[MAX_TEXT_SIZE] = {0};
    char serialNumber[MAX_TEXT_SIZE] = {0};
    printf("Starts DeviceDescriptor creation\n");

    FT_PROGRAM_DATA data = {0};
    data.Signature1 = 0;
    data.Signature2 = -1;
    data.Version = 5;
    data.VendorId = 0x0403;
    data.ProductId = 0x6001;
    data.Manufacturer = manufacturer;
    data.ManufacturerId = manufacturerID;
    data.Description = description;
    data.SerialNumber = serialNumber;

    result = FT_EE_Read(ftHandle, &data);
    if(result == FT_EEPROM_NOT_PROGRAMMED){
        printf("EEPROM not programed: Programing EEPROM %lu %lu \n", ftHandle, result);
        data.Manufacturer = (char*)"FTDI";
        data.ManufacturerId = (char*)"FT";
        data.Description = (char*)"USB HS Serial Converter";
        data.SerialNumber = (char*)"FT000001";
        data.SelfPowered = 1;
        data.MaxPower = 200;
        data.PnP = 1;
        data.RemoteWakeup = 1;
        result = FT_EE_Program(ftHandle, &data);
        if(result == FT_EEPROM_WRITE_FAILED){
            printf("ALRIGHT! NO EEPROM! \n");
        }else if(result != FT_OK){
            printf("ERROR: Can't program EEPROM %lu\n", result);
            return NULL;
        }else{
           printf("ALRIGHT! EEPROM programmed \n");
        }
    }else if(result != FT_OK){  printf("FATAL ERROR! %lu\n", result); return NULL; }
    return CreateDeviceDescriptor(env, &data);
}

#ifdef __cplusplus
}
#endif