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

//#include "framework/glm/glm/glm.hpp"
//#include "framework/glm/glm/gtc/type_ptr.hpp"
//#include "framework/glm/glm/gtc/matrix_transform.hpp"
//#include "framework/glm/glm/gtc/quaternion.hpp"
//#include "framework/glm/glm/gtx/quaternion.hpp"
#include "framework/math/math.h"

#include "framework/graphics/camera.h"
#include "framework/graphics/vertex.h"

#include "framework/util/file_utils.h"

#include "framework/states/state_manager.h"
