/**
 * Spine NAPI 模块头文件
 * 定义所有与 ArkTS 交互的 NAPI 接口
 */

#ifndef SPINE_NAPI_H
#define SPINE_NAPI_H

#include <napi/native_api.h>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <atomic>
#include "manager/SpineManager.h"

using namespace std;



/**
 * NAPI 模块初始化
 */
napi_value SpineNapiInit(napi_env env, napi_value exports);

/**
 * NAPI 函数声明
 */
namespace SpineNapi {

// 实例管理
napi_value CreateSpineInstance(napi_env env, napi_callback_info info);
napi_value DestroySpineInstance(napi_env env, napi_callback_info info);

// 渲染设置
napi_value SetEventCallback(napi_env env, napi_callback_info info);

// 数据加载
napi_value LoadSpineData(napi_env env, napi_callback_info info);

// 动画控制
napi_value SetAnimation(napi_env env, napi_callback_info info);
napi_value AddAnimation(napi_env env, napi_callback_info info);
napi_value SetSkin(napi_env env, napi_callback_info info);
napi_value SetMix(napi_env env, napi_callback_info info);
napi_value SetTimeScale(napi_env env, napi_callback_info info);

// 播放控制
napi_value Pause(napi_env env, napi_callback_info info);
napi_value Resume(napi_env env, napi_callback_info info);
napi_value ClearTracks(napi_env env, napi_callback_info info);
napi_value ClearTrack(napi_env env, napi_callback_info info);

// 视图管理
napi_value UpdateViewSize(napi_env env, napi_callback_info info);

// 信息获取
napi_value GetAnimations(napi_env env, napi_callback_info info);
napi_value GetSkins(napi_env env, napi_callback_info info);

// 资源管理
napi_value Cleanup(napi_env env, napi_callback_info info);

// 渲染循环
napi_value Update(napi_env env, napi_callback_info info);
napi_value Render(napi_env env, napi_callback_info info);

} // namespace SpineNapi

/**
 * 工具函数
 */
namespace SpineNapiUtils {

// 参数解析
inline bool ParseInt32(napi_env env, napi_value value, int32_t* result);
inline bool ParseFloat(napi_env env, napi_value value, float* result);
inline bool ParseBool(napi_env env, napi_value value, bool* result);
inline bool ParseString(napi_env env, napi_value value, std::string* result);
inline bool ParseLoadOptions(napi_env env, napi_value value, SpineLoadOptions* options);

// 返回值创建
inline napi_value CreateBool(napi_env env, bool value);
inline napi_value CreateInt32(napi_env env, int32_t value);
inline napi_value CreateStringArray(napi_env env, const std::vector<std::string>& strings);

// 错误处理
inline napi_value ThrowError(napi_env env, const std::string& message);
inline napi_value ThrowTypeError(napi_env env, const std::string& message);

} // namespace SpineNapiUtils

/**
 * 实例注册表 - 线程安全的实例管理
 */
class SpineInstanceRegistry {
public:
    static SpineInstanceRegistry& getInstance();
    
    // 实例注册和注销
    int32_t RegisterInstance(std::unique_ptr<SpineManager> manager);
    bool UnregisterInstance(int32_t instanceId);
    SpineManager* GetInstance(int32_t instanceId);
    
    // 回调管理
    void SetEventCallback(int32_t instanceId, napi_env env, napi_ref callbackRef);
    void TriggerEvent(int32_t instanceId, const SpineAnimationEvent& event);
    
private:
    SpineInstanceRegistry() : nextInstanceId_(1) {}
    ~SpineInstanceRegistry();
    
    struct InstanceData {
        std::unique_ptr<SpineManager> manager;
        napi_env env = nullptr;
        napi_ref callbackRef = nullptr;
        std::string surfaceId;           // 独立的渲染表面
        std::thread::id renderThreadId;  // 渲染线程ID
    };
    
    std::unordered_map<int32_t, InstanceData> instances_;
    std::atomic<int32_t> nextInstanceId_;
    mutable std::mutex instancesMutex_;  // 保护实例映射表
};

/**
 * Spine 实例工厂 - 负责创建完全独立的实例
 */
class SpineInstanceFactory {
public:
    /**
     * 创建独立的 Spine 实例
     * @param surfaceId 渲染表面ID
     * @return 实例ID，失败返回 -1
     */
    static int32_t CreateInstance(const string& surfaceId = "");
    
    /**
     * 销毁实例
     * @param instanceId 实例ID
     * @return 是否成功
     */
    static bool DestroyInstance(int32_t instanceId);
    
private:
    /**
     * 为每个实例创建独立的渲染上下文
     * @param surfaceId 渲染表面ID
     * @return 渲染上下文
     */
    static void* CreateRenderContext(const string& surfaceId);
};

#endif // SPINE_NAPI_H 