/**
 * Spine NAPI 模块实现
 * 实现所有与 ArkTS 交互的 NAPI 接口
 */

#include "spine_napi.h"
#include <iostream>
#include <memory>
#include "manager/SpineManager.h"
#include "common/common.h"

using namespace std;

/**
 * 全局事件回调函数（静态函数，无捕获）
 */
static void GlobalSpineEventCallback(int32_t instanceId, const SpineAnimationEvent& event) {
    SpineInstanceRegistry::getInstance().TriggerEvent(instanceId, event);
}

/**
 * NAPI 模块初始化
 */
napi_value SpineNapiInit(napi_env env, napi_value exports) {
    // 定义导出的函数
    

    // 这里需要调用实际的NAPI函数来定义属性
    // napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    
    return exports;
}

namespace SpineNapi {

/**
 * 创建 Spine 实例
 */
napi_value CreateSpineInstance(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    // napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    string surfaceId = "";
    if (argc > 0) {
        SpineNapiUtils::ParseString(env, args[0], &surfaceId);
    }
    
    int32_t instanceId = SpineInstanceFactory::CreateInstance(surfaceId);
    return SpineNapiUtils::CreateInt32(env, instanceId);
}

/**
 * 销毁 Spine 实例
 */
napi_value DestroySpineInstance(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    // napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    int32_t instanceId;
    if (!SpineNapiUtils::ParseInt32(env, args[0], &instanceId)) {
        return SpineNapiUtils::ThrowTypeError(env, "Invalid instance ID");
    }
    
    bool success = SpineInstanceFactory::DestroyInstance(instanceId);
    return SpineNapiUtils::CreateBool(env, success);
}

/**
 * 设置事件回调
 */
napi_value SetEventCallback(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    // napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    int32_t instanceId;
    if (!SpineNapiUtils::ParseInt32(env, args[0], &instanceId)) {
        return SpineNapiUtils::ThrowTypeError(env, "Invalid instance ID");
    }
    
    // 创建回调引用
    napi_ref callbackRef;
    // napi_create_reference(env, args[1], 1, &callbackRef);
    
    SpineInstanceRegistry::getInstance().SetEventCallback(instanceId, env, callbackRef);
    return SpineNapiUtils::CreateBool(env, true);
}

/**
 * 加载 Spine 数据
 */
napi_value LoadSpineData(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    // napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    int32_t instanceId;
    string spineDataPath, atlasDataPath;
    SpineLoadOptions options;
    
    if (!SpineNapiUtils::ParseInt32(env, args[0], &instanceId) ||
        !SpineNapiUtils::ParseString(env, args[1], &spineDataPath) ||
        !SpineNapiUtils::ParseString(env, args[2], &atlasDataPath) ||
        !SpineNapiUtils::ParseLoadOptions(env, args[3], &options)) {
        return SpineNapiUtils::ThrowTypeError(env, "Invalid arguments");
    }
    SpineManager* manager = SpineInstanceRegistry::getInstance().GetInstance(instanceId);
    if (!manager) {
        return SpineNapiUtils::ThrowError(env, "Invalid instance ID");
    }

    bool success = manager->LoadSpineData(spineDataPath, atlasDataPath, options);
    return SpineNapiUtils::CreateBool(env, success);
}

/**
 * 设置动画
 */
napi_value SetAnimation(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    // napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    int32_t instanceId, trackIndex;
    string animationName;
    bool loop;
    
    if (!SpineNapiUtils::ParseInt32(env, args[0], &instanceId) ||
        !SpineNapiUtils::ParseInt32(env, args[1], &trackIndex) ||
        !SpineNapiUtils::ParseString(env, args[2], &animationName) ||
        !SpineNapiUtils::ParseBool(env, args[3], &loop)) {
        return SpineNapiUtils::ThrowTypeError(env, "Invalid arguments");
    }
    SpineManager* manager = SpineInstanceRegistry::getInstance().GetInstance(instanceId);
    if (!manager) {
        return SpineNapiUtils::ThrowError(env, "Invalid instance ID");
    }

    bool success = manager->SetAnimation(trackIndex, animationName, loop);
    return SpineNapiUtils::CreateBool(env, success);
}

/**
 * 添加动画到队列
 */
napi_value AddAnimation(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    
    int32_t instanceId, trackIndex;
    string animationName;
    bool loop;
    float delay;
    
    if (!SpineNapiUtils::ParseInt32(env, args[0], &instanceId) ||
        !SpineNapiUtils::ParseInt32(env, args[1], &trackIndex) ||
        !SpineNapiUtils::ParseString(env, args[2], &animationName) ||
        !SpineNapiUtils::ParseBool(env, args[3], &loop) ||
        !SpineNapiUtils::ParseFloat(env, args[4], &delay)) {
        return SpineNapiUtils::ThrowTypeError(env, "Invalid arguments");
    }
    SpineManager* manager = SpineInstanceRegistry::getInstance().GetInstance(instanceId);
    if (!manager) {
        return SpineNapiUtils::ThrowError(env, "Invalid instance ID");
    }

    bool success = manager->AddAnimation(trackIndex, animationName, loop, delay);
    return SpineNapiUtils::CreateBool(env, success);
}

/**
 * 获取动画列表
 */
napi_value GetAnimations(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    
    int32_t instanceId;
    if (!SpineNapiUtils::ParseInt32(env, args[0], &instanceId)) {
        return SpineNapiUtils::ThrowTypeError(env, "Invalid instance ID");
    }
    SpineManager* manager = SpineInstanceRegistry::getInstance().GetInstance(instanceId);
    if (!manager) {
        return SpineNapiUtils::ThrowError(env, "Invalid instance ID");
    }

    vector<string> animations = manager->GetAnimations();
    return SpineNapiUtils::CreateStringArray(env, animations);
}

// 其他函数的实现类似，这里省略...
napi_value SetSkin(napi_env env, napi_callback_info info) { return nullptr; }
napi_value SetMix(napi_env env, napi_callback_info info) { return nullptr; }
napi_value SetTimeScale(napi_env env, napi_callback_info info) { return nullptr; }
napi_value Pause(napi_env env, napi_callback_info info) { return nullptr; }
napi_value Resume(napi_env env, napi_callback_info info) { return nullptr; }
napi_value ClearTracks(napi_env env, napi_callback_info info) { return nullptr; }
napi_value ClearTrack(napi_env env, napi_callback_info info) { return nullptr; }
napi_value UpdateViewSize(napi_env env, napi_callback_info info) { return nullptr; }
napi_value GetSkins(napi_env env, napi_callback_info info) { return nullptr; }
napi_value Cleanup(napi_env env, napi_callback_info info) { return nullptr; }
napi_value Update(napi_env env, napi_callback_info info) { return nullptr; }
napi_value Render(napi_env env, napi_callback_info info) { return nullptr; }

} // namespace SpineNapi

/**
 * 工具函数实现
 */
#include <node_api.h>
#include <string>
#include <vector>
#include <cassert>

namespace SpineNapiUtils {

using std::string;
using std::vector;

/* ---------- 通用工具 ---------- */
inline bool Check(napi_status status, napi_env env, const char* msg = nullptr) {
    if (status == napi_ok) return true;
    const char* what = msg ? msg : "N-API call failed";
    napi_throw_error(env, nullptr, what);
    return false;
}

/* ---------- 解析基础类型 ---------- */
inline bool ParseInt32(napi_env env, napi_value value, int32_t* result) {
    return Check(napi_get_value_int32(env, value, result), env,
                 "Expected an int32");
}

inline bool ParseFloat(napi_env env, napi_value value, float* result) {
    double d;
    if (!Check(napi_get_value_double(env, value, &d), env,
               "Expected a number"))
        return false;
    *result = static_cast<float>(d);
    return true;
}

inline bool ParseBool(napi_env env, napi_value value, bool* result) {
    return Check(napi_get_value_bool(env, value, result), env,
                 "Expected a boolean");
}

inline bool ParseString(napi_env env, napi_value value, string* result) {
    // 先拿到长度（不含结尾 '\0'）
    size_t len = 0;
    if (!Check(napi_get_value_string_utf8(env, value, nullptr, 0, &len),
               env, "Expected a string"))
        return false;

    result->resize(len);
    size_t written = 0;
    if (!Check(napi_get_value_string_utf8(
                   env, value, result->data(), len + 1, &written),
               env, "Unable to read string"))
        return false;
    return true;
}

/* ---------- 解析自定义选项对象 ---------- */
inline bool ParseLoadOptions(napi_env env,
                             napi_value value,
                             SpineLoadOptions* options) {
    napi_valuetype vt;
    if (!Check(napi_typeof(env, value, &vt), env) || vt != napi_object)
        return false;  // 上面 Check 已抛异常

    auto get_prop = [&](const char* name, napi_value* out) -> bool {
        napi_value key;
        if (!Check(napi_create_string_utf8(env, name, NAPI_AUTO_LENGTH, &key),
                   env))
            return false;
        bool has_prop = false;
        if (!Check(napi_has_property(env, value, key, &has_prop), env))
            return false;
        if (!has_prop) return false;
        return Check(napi_get_named_property(env, value, name, out), env);
    };

    napi_value v;

    /* scale: number */
    if (get_prop("scale", &v))
        ParseFloat(env, v, &options->scale);  // 已内部抛错

    /* premultipliedAlpha: boolean */
    if (get_prop("premultipliedAlpha", &v))
        ParseBool(env, v, &options->premultipliedAlpha);

    /* debugMode: boolean */
    if (get_prop("debugMode", &v))
        ParseBool(env, v, &options->debugMode);

    return true;  // 任何字段出错都会提前抛异常
}

/* ---------- 创建 JS 基础值 ---------- */
inline napi_value CreateBool(napi_env env, bool value) {
    napi_value result;
    Check(napi_get_boolean(env, value, &result), env);
    return result;
}

inline napi_value CreateInt32(napi_env env, int32_t value) {
    napi_value result;
    Check(napi_create_int32(env, value, &result), env);
    return result;
}

inline napi_value CreateStringArray(napi_env env,
                                    const vector<string>& strings) {
    napi_value array;
    Check(napi_create_array_with_length(env,
                                        static_cast<uint32_t>(strings.size()),
                                        &array),
          env);

    for (size_t i = 0; i < strings.size(); ++i) {
        napi_value str;
        Check(napi_create_string_utf8(env,
                                      strings[i].c_str(),
                                      strings[i].length(),
                                      &str),
              env);
        Check(napi_set_element(env, array, static_cast<uint32_t>(i), str), env);
    }
    return array;
}

/* ---------- 抛异常辅助 ---------- */
inline napi_value ThrowError(napi_env env, const string& message) {
    napi_throw_error(env, nullptr, message.c_str());
    return nullptr;
}

inline napi_value ThrowTypeError(napi_env env, const string& message) {
    napi_throw_type_error(env, nullptr, message.c_str());
    return nullptr;
}

}  // namespace SpineNapiUtils


/**
 * SpineInstanceRegistry 实现
 */
SpineInstanceRegistry& SpineInstanceRegistry::getInstance() {
    static SpineInstanceRegistry instance;
    return instance;
}

int32_t SpineInstanceRegistry::RegisterInstance(std::unique_ptr<SpineManager> manager) {
    lock_guard<mutex> lock(instancesMutex_);
    
    int32_t instanceId = nextInstanceId_++;
    InstanceData data;
    data.manager = std::move(manager);
    data.surfaceId = data.manager->GetSurfaceId();
    data.renderThreadId = this_thread::get_id();
    
    instances_[instanceId] = std::move(data);
    return instanceId;
}

bool SpineInstanceRegistry::UnregisterInstance(int32_t instanceId) {
    lock_guard<mutex> lock(instancesMutex_);
    
    auto it = instances_.find(instanceId);
    if (it != instances_.end()) {
        // 清理回调引用
        if (it->second.callbackRef != nullptr) {
            // napi_delete_reference(it->second.env, it->second.callbackRef);
        }
        instances_.erase(it);
        return true;
    }
    return false;
}

SpineManager* SpineInstanceRegistry::GetInstance(int32_t instanceId) {
    lock_guard<mutex> lock(instancesMutex_);
    
    auto it = instances_.find(instanceId);
    if (it != instances_.end()) {
        return it->second.manager.get();
    }
    return nullptr;
}

void SpineInstanceRegistry::SetEventCallback(int32_t instanceId, napi_env env, napi_ref callbackRef) {
    lock_guard<mutex> lock(instancesMutex_);
    
    auto it = instances_.find(instanceId);
    if (it != instances_.end()) {
        it->second.env = env;
        it->second.callbackRef = callbackRef;
         // 设置全局C++回调到管理器
        it->second.manager->SetGlobalEventCallback(GlobalSpineEventCallback, instanceId);
    }
}

void SpineInstanceRegistry::TriggerEvent(int32_t instanceId, const SpineAnimationEvent& event) {
    lock_guard<mutex> lock(instancesMutex_);
    
    auto it = instances_.find(instanceId);
    if (it != instances_.end() && it->second.callbackRef != nullptr) {
        // 这里需要在主线程中调用JavaScript回调
        // 创建事件对象并调用回调
        // napi_value eventObj;
        // napi_create_object(it->second.env, &eventObj);
        // ... 设置事件属性
        // napi_call_function(it->second.env, ..., it->second.callbackRef, ...);
    }
}

SpineInstanceRegistry::~SpineInstanceRegistry() {
    // 清理所有实例
    for (auto& pair : instances_) {
        if (pair.second.callbackRef != nullptr) {
            // napi_delete_reference(pair.second.env, pair.second.callbackRef);
        }
    }
}

/**
 * SpineInstanceFactory 实现
 */
int32_t SpineInstanceFactory::CreateInstance(const string& surfaceId) {
    try {
        // 创建独立的渲染上下文
        auto renderContext = std::make_unique<SpineRenderContext>(surfaceId);
//        renderContext->eglDisplay = CreateRenderContext(surfaceId);
//        renderContext->isValid = (renderContext->eglDisplay != nullptr);
        
        // 创建 SpineManager 实例
        auto manager = make_unique<SpineManager>(surfaceId, std::move(renderContext));
        
        // 注册到注册表
        return SpineInstanceRegistry::getInstance().RegisterInstance(std::move(manager));
    } catch (const exception& e) {
        // 错误处理
        return -1;
    }
}

bool SpineInstanceFactory::DestroyInstance(int32_t instanceId) {
    return SpineInstanceRegistry::getInstance().UnregisterInstance(instanceId);
}

void* SpineInstanceFactory::CreateRenderContext(const string& surfaceId) {
    // 这里需要实现创建独立的 EGL 上下文
    // 每个实例都有自己的渲染上下文，避免共享状态
    // 临时返回
    return nullptr;
}
