#include <jni.h>
#include <errno.h>

#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/sensor.h>

#include <android/log.h>
#include "android_native_app_glue.h"
#include <android/asset_manager.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "asteroids.NativeActivity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "asteroids.NativeActivity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "asteroids.NativeActivity", __VA_ARGS__))

/* For debug builds, always enable the debug traces in this library */
#ifndef NDEBUG
#  define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_VERBOSE, "threaded_app", __VA_ARGS__))
#else
#  define LOGV(...)  ((void)0)
#endif

// uncomment this line to debug collision detection
//#define DEBUG_COLLISIONS

#include "framework/math/math.h"
#include "framework/ecs/ecs.h"
#include "framework/graphics/gfx.h"
#include "framework/util/circularArray.h"
#include "framework/particles/ps.h"
#include "framework/util/file_utils.h"
#include "framework/util/tweener.h"
#include "framework/input/input.h"
#include "framework/states/state_manager.h"

#include "game/entities/entity.h"
#include "game/util/util.h"