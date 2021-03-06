//
// Created by byteflow on 2020/6/16.
//
#include <cstdio>
#include <cstring>
#include <FFMediaPlayer.h>
#include <render/video/OpenGLRender.h>
#include <render/audio/OpenSLRender.h>
#include "util/LogUtil.h"
#include "jni.h"

extern "C" {
#include <libavcodec/version.h>
#include <libavcodec/avcodec.h>
#include <libavformat/version.h>
#include <libavutil/version.h>
#include <libavfilter/version.h>
#include <libswresample/version.h>
#include <libswscale/version.h>
};

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_GetFFmpegVersion
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1GetFFmpegVersion
        (JNIEnv *env, jclass cls)
{
    char strBuffer[1024 * 4] = {0};
    strcat(strBuffer, "libavcodec : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVCODEC_VERSION));
    strcat(strBuffer, "\nlibavformat : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFORMAT_VERSION));
    strcat(strBuffer, "\nlibavutil : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVUTIL_VERSION));
    strcat(strBuffer, "\nlibavfilter : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFILTER_VERSION));
    strcat(strBuffer, "\nlibswresample : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWRESAMPLE_VERSION));
    strcat(strBuffer, "\nlibswscale : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWSCALE_VERSION));
    strcat(strBuffer, "\navcodec_configure : \n");
    strcat(strBuffer, avcodec_configuration());
    strcat(strBuffer, "\navcodec_license : ");
    strcat(strBuffer, avcodec_license());
    LOGCATE("GetFFmpegVersion\n%s", strBuffer);
    return env->NewStringUTF(strBuffer);
}

/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_Init
 * Signature: (JLjava/lang/String;Ljava/lang/Object;)J
 */
JNIEXPORT jlong JNICALL Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1Init
        (JNIEnv *env, jobject obj, jstring jurl, jint renderType, jobject surface)
{
    const char* url = env->GetStringUTFChars(jurl, nullptr);
    FFMediaPlayer *player = new FFMediaPlayer();
    player->Init(env, obj, const_cast<char *>(url), renderType, surface);
    env->ReleaseStringUTFChars(jurl, url);
    return reinterpret_cast<jlong>(player);
}

/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_Play
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1Play
(JNIEnv *env, jobject obj, jlong player_handle)
{
    if(player_handle != 0)
    {
        FFMediaPlayer *ffMediaPlayer = reinterpret_cast<FFMediaPlayer *>(player_handle);
        ffMediaPlayer->Play();
    }

}

JNIEXPORT void JNICALL
Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1SeekToPosition(JNIEnv *env, jobject thiz,
                                                                      jlong player_handle, jfloat position) {
    if(player_handle != 0)
    {
        FFMediaPlayer *ffMediaPlayer = reinterpret_cast<FFMediaPlayer *>(player_handle);
        ffMediaPlayer->SeekToPosition(position);
    }
}

JNIEXPORT jlong JNICALL
Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1GetMediaParams(JNIEnv *env, jobject thiz,
                                                                         jlong player_handle,
                                                                         jint param_type) {
    long value = 0;
    if(player_handle != 0)
    {
        FFMediaPlayer *ffMediaPlayer = reinterpret_cast<FFMediaPlayer *>(player_handle);
        value = ffMediaPlayer->GetMediaParams(param_type);
    }
    return value;
}

/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_Pause
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1Pause
(JNIEnv *env, jobject obj, jlong player_handle)
{
    if(player_handle != 0)
    {
        FFMediaPlayer *ffMediaPlayer = reinterpret_cast<FFMediaPlayer *>(player_handle);
        ffMediaPlayer->Pause();
    }
}

/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_Stop
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1Stop
(JNIEnv *env, jobject obj, jlong player_handle)
{
    if(player_handle != 0)
    {
        FFMediaPlayer *ffMediaPlayer = reinterpret_cast<FFMediaPlayer *>(player_handle);
        ffMediaPlayer->Stop();
    }
}

/*
 * Class:     com_byteflow_learnffmpeg_media_FFMediaPlayer
 * Method:    native_UnInit
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1UnInit
(JNIEnv *env, jobject obj, jlong player_handle)
{
    if(player_handle != 0)
    {
        FFMediaPlayer *ffMediaPlayer = reinterpret_cast<FFMediaPlayer *>(player_handle);
        ffMediaPlayer->UnInit();
    }
}

JNIEXPORT void JNICALL
Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1OnSurfaceCreated(JNIEnv *env,
                                                                           jclass clazz) {
    OpenGLRender::GetInstance()->OnSurfaceCreated();
}

JNIEXPORT void JNICALL
Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1OnSurfaceChanged(JNIEnv *env,
                                                                           jclass clazz, jint width,
                                                                           jint height) {
    OpenGLRender::GetInstance()->OnSurfaceChanged(width, height);
}

JNIEXPORT void JNICALL
Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1OnDrawFrame(JNIEnv *env, jclass clazz) {
    OpenGLRender::GetInstance()->OnDrawFrame();
}

JNIEXPORT void JNICALL
Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1SetGesture(JNIEnv *env, jclass clazz,
                                                                     jfloat x_rotate_angle,
                                                                     jfloat y_rotate_angle,
                                                                     jfloat scale) {
    OpenGLRender::GetInstance()->UpdateMVPMatrix(x_rotate_angle, y_rotate_angle, scale, scale);
}

JNIEXPORT void JNICALL
Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1SetTouchLoc(JNIEnv *env, jclass clazz,
                                                                      jfloat touch_x,
                                                                      jfloat touch_y) {
    OpenGLRender::GetInstance()->SetTouchLoc(touch_x, touch_y);
}

//可视化音频的渲染接口
JNIEXPORT void JNICALL
Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1OnAudioVisualSurfaceCreated(JNIEnv *env,
                                                                                      jclass clazz) {
    AudioVisualRender::GetInstance()->OnAudioVisualSurfaceCreated();
}

JNIEXPORT void JNICALL
Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1OnAudioVisualSurfaceChanged(JNIEnv *env,
                                                                                      jclass clazz,
                                                                                      jint width,
                                                                                      jint height) {
    AudioVisualRender::GetInstance()->OnAudioVisualSurfaceChanged(width, height);
}

JNIEXPORT void JNICALL
Java_com_byteflow_learnffmpeg_media_FFMediaPlayer_native_1OnAudioVisualDrawFrame(JNIEnv *env,
                                                                                 jclass clazz) {
    AudioVisualRender::GetInstance()->OnAudioVisualDrawFrame();
}

#ifdef __cplusplus
}
#endif