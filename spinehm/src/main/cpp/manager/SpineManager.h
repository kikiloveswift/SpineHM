//
// Created on 2025/8/1.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef SPINEHM_SPINEMANAGER_H
#define SPINEHM_SPINEMANAGER_H
/**
 * SpineManager - Spine 实例管理器
 * 负责管理单个 Spine 动画实例的生命周期和状态
 */

#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <functional>

// 暂时注释掉 Spine 4.2 相关头文件
// #include <spine/spine.h>
// #include <spine/SkeletonData.h>
// #include <spine/SkeletonJson.h>
// #include <spine/Atlas.h>
// #include <spine/AnimationState.h>
// #include <spine/AnimationStateData.h>

// 前置声明
struct SpineAnimationEvent;
struct SpineLoadOptions;
struct SpineEventData;

using std::string;

/**
 * 每个 Spine 实例的渲染上下文
 * 为 Skia 渲染做准备
 */
struct SpineRenderContext {
    string surfaceId;
    
    // Skia 相关成员（待实现）
    // sk_sp<SkSurface> surface;
    // sk_sp<SkCanvas> canvas;
    // SkMatrix viewMatrix;
    
    // 视口信息
    int32_t viewWidth = 0;
    int32_t viewHeight = 0;
    float scale = 1.0f;
    bool premultipliedAlpha = true;
    
    SpineRenderContext(const string& surfaceId) : surfaceId(surfaceId) {}
};

/**
 * Spine 动画管理器
 * 负责管理单个 Spine 实例的动画播放和渲染
 */
class SpineManager {
public:
    /**
     * 构造函数
     * @param surfaceId 渲染表面ID
     * @param renderContext 渲染上下文
     */
    SpineManager(const string& surfaceId, std::unique_ptr<SpineRenderContext> renderContext);
    
    /**
     * 析构函数
     */
    ~SpineManager();

    // ==================== 数据加载 ====================
    
    /**
     * 加载 Spine 数据
     * @param spineDataPath .skel 或 .json 文件路径
     * @param atlasDataPath .atlas 文件路径
     * @param options 加载选项
     * @return 是否加载成功
     */
    bool LoadSpineData(const string& spineDataPath, const string& atlasDataPath, const SpineLoadOptions& options);
    
    /**
     * 获取可用的动画列表
     * @return 动画名称列表
     */
    std::vector<string> GetAnimations() const;
    
    /**
     * 获取可用的皮肤列表
     * @return 皮肤名称列表
     */
    std::vector<string> GetSkins() const;
    
    // ==================== 动画控制 ====================
    
    /**
     * 设置动画
     * @param trackIndex 轨道索引
     * @param animationName 动画名称
     * @param loop 是否循环
     * @return 是否设置成功
     */
    bool SetAnimation(int32_t trackIndex, const string& animationName, bool loop);
    
    /**
     * 添加动画到队列
     * @param trackIndex 轨道索引
     * @param animationName 动画名称
     * @param loop 是否循环
     * @param delay 延迟时间（秒）
     * @return 是否添加成功
     */
    bool AddAnimation(int32_t trackIndex, const string& animationName, bool loop, float delay);
    
    /**
     * 清除指定轨道的动画
     * @param trackIndex 轨道索引
     */
    void ClearTrack(int32_t trackIndex);
    
    /**
     * 清除所有轨道的动画
     */
    void ClearTracks();
    
    // ==================== 外观控制 ====================
    
    /**
     * 设置皮肤
     * @param skinName 皮肤名称
     * @return 是否设置成功
     */
    bool SetSkin(const string& skinName);
    
    /**
     * 设置动画混合时间
     * @param fromAnimation 起始动画
     * @param toAnimation 目标动画
     * @param duration 混合时间（秒）
     */
    void SetMix(const string& fromAnimation, const string& toAnimation, float duration);
    
    // ==================== 播放控制 ====================
    
    /**
     * 设置时间缩放
     * @param timeScale 时间缩放比例（1.0 = 正常速度）
     */
    void SetTimeScale(float timeScale);
    
    /**
     * 暂停动画
     */
    void Pause();
    
    /**
     * 恢复动画
     */
    void Resume();
    
    /**
     * 停止所有动画
     */
    void Stop();
    
    /**
     * 获取动画状态
     * @return 动画状态信息的JSON字符串
     */
    string GetState() const;
    
    // ==================== 视图控制 ====================
    
    /**
     * 更新视图大小
     * @param width 视图宽度
     * @param height 视图高度
     */
    void UpdateViewSize(int32_t width, int32_t height);
    
    /**
     * 设置缩放
     * @param scale 缩放比例
     */
    void SetScale(float scale);
    
    /**
     * 设置是否预乘Alpha
     * @param premultipliedAlpha 是否预乘Alpha
     */
    void SetPremultipliedAlpha(bool premultipliedAlpha);
    
    // ==================== 渲染循环 ====================
    
    /**
     * 更新动画（每帧调用）
     * @param deltaTime 帧时间间隔（秒）
     */
    void Update(float deltaTime);
    
    /**
     * 渲染到 Skia Canvas（每帧调用）
     */
    void Render();
    
    // ==================== 事件系统 ====================
    
    /**
     * 设置事件回调函数
     * @param callback 事件回调函数
     */
    void SetEventCallback(void (*callback)(const SpineAnimationEvent&));
    
    /**
     * 设置全局事件回调函数
     * @param callback 全局事件回调函数
     * @param instanceId 实例ID
     */
    void SetGlobalEventCallback(void (*callback)(int32_t, const SpineAnimationEvent&), int32_t instanceId);
    
    /**
     * 触发事件
     * @param event 事件数据
     */
    void TriggerEvent(const SpineAnimationEvent& event);
    
    // ==================== 生命周期 ====================
    
    /**
     * 清理资源
     */
    void Cleanup();
    
    /**
     * 获取表面ID
     * @return 表面ID
     */
    const string& GetSurfaceId() const { return renderContext_->surfaceId; }

private:
    // ==================== 私有成员变量 ====================
    
    // 渲染上下文
    std::unique_ptr<SpineRenderContext> renderContext_;
    
    // 暂时注释掉 Spine 4.2 相关对象
    // spine::Atlas* atlas_;
    // spine::SkeletonData* skeletonData_;
    // spine::SkeletonJson* skeletonJson_;
    // spine::Skeleton* skeleton_;
    // spine::AnimationState* animationState_;
    // spine::AnimationStateData* animationStateData_;
    
    // 基本状态
    bool isLoaded_;
    bool isPaused_;
    float timeScale_;
    
    // 动画数据（临时用 string 列表代替）
    std::vector<string> availableAnimations_;
    std::vector<string> availableSkins_;
    
    // 事件回调
    void (*eventCallback_)(const SpineAnimationEvent&);
    void (*globalEventCallback_)(int32_t, const SpineAnimationEvent&);
    int32_t callbackInstanceId_;
    
    // 线程安全
    mutable std::mutex dataMutex_;
    
    // ==================== 私有方法 ====================
    
    /**
     * 初始化渲染资源
     * @return 是否初始化成功
     */
    bool InitializeRenderResources();
    
    /**
     * 清理渲染资源
     */
    void CleanupRenderResources();
    
    /**
     * 创建默认动画数据（临时）
     */
    void CreateDefaultData();
    
    // 友元类声明
    friend class SpineEventListener;
};

#endif //SPINEHM_SPINEMANAGER_H
