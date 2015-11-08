#ifndef DS_LOGGING_H
#define DS_LOGGING_H

#if ANDROID

#include <android/log.h>

#define LOGI_TAG(tag, ...) __android_log_print(ANDROID_LOG_INFO, tag, __VA_ARGS__)
#define LOGE_TAG(tag, ...) __android_log_print(ANDROID_LOG_FATAL, tag, __VA_ARGS__)

#else

#include <stdio.h>

#define LOGI_TAG(...) fprintf(stdout, __VA_ARGS__)
#define LOGE_TAG(...) fprintf(stderr, __VA_ARGS__)

#endif

#define LOGI(...) LOGI_TAG("native-interop", __VA_ARGS__)
#define LOGE(...) LOGE_TAG("native-interop", __VA_ARGS__)

#endif
