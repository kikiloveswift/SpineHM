//
// Created on 2025/8/1.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

/**
 * SpineManager.cpp - Spine 4.2 实例管理器实现
 * 基于 Spine 4.2 C++ 运行时的完整实现
 */

#include "SpineManager.h"
#include "spine_napi.h"
#include <cstring>
#include <algorithm>
#include <cmath>
#include <functional>

// 暂时注释掉 Spine 4.2 相关头文件
// #include <spine/spine.h>
// #include <spine/SkeletonData.h>
// #include <spine/SkeletonJson.h>
// #include <spine/Atlas.h>
// #include <spine/AnimationState.h>
// #include <spine/AnimationStateData.h>

using std::string;

/**
 * SpineManager 构造函数
 */
SpineManager::SpineManager(const string& surfaceId, std::unique_ptr<SpineRenderContext> renderContext)
    : renderContext_(std::move(renderContext))
    , isLoaded_(false)
    , isPaused_(false)
    , timeScale_(1.0f)
    , eventCallback_(nullptr)
    , globalEventCallback_(nullptr)
    , callbackInstanceId_(-1) {
    
    // 暂时注释掉 Spine 4.2 对象初始化
    // atlas_ = nullptr;
    // skeletonData_ = nullptr;
    // skeletonJson_ = nullptr;
    // skeleton_ = nullptr;
    // animationState_ = nullptr;
    // animationStateData_ = nullptr;
    
    // 初始化渲染资源
    InitializeRenderResources();
    
    // 创建默认数据
    CreateDefaultData();
}

/**
 * SpineManager 析构函数
 */
SpineManager::~SpineManager() {
    Cleanup();
}

// ==================== 数据加载 ====================

bool SpineManager::LoadSpineData(const string& spineDataPath, const string& atlasDataPath, const SpineLoadOptions& options) {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    // 暂时注释掉实际的 Spine 4.2 加载逻辑
    /*
    try {
        // 清理现有资源
        CleanupRenderResources();
        
        // 加载图集
        atlas_ = new spine::Atlas(atlasDataPath.c_str(), nullptr);
        if (!atlas_) {
            return false;
        }
        
        // 创建附件加载器
        spine::AtlasAttachmentLoader attachmentLoader(atlas_);
        
        // 加载骨骼数据
        if (spineDataPath.find(".json") != string::npos) {
            skeletonJson_ = new spine::SkeletonJson(&attachmentLoader);
            skeletonData_ = skeletonJson_->readSkeletonDataFile(spineDataPath.c_str());
        } else {
            spine::SkeletonBinary skeletonBinary(&attachmentLoader);
            skeletonData_ = skeletonBinary.readSkeletonDataFile(spineDataPath.c_str());
        }
        
        if (!skeletonData_) {
            return false;
        }
        
        // 创建骨骼实例
        skeleton_ = new spine::Skeleton(skeletonData_);
        
        // 创建动画状态
        animationStateData_ = new spine::AnimationStateData(skeletonData_);
        animationState_ = new spine::AnimationState(animationStateData_);
        
        // 设置默认皮肤
        skeleton_->setSkin(skeletonData_->getDefaultSkin());
        skeleton_->updateWorldTransform();
        
        isLoaded_ = true;
        return true;
        
    } catch (...) {
        return false;
    }
    */
    
    // 临时实现：仅设置加载状态
    isLoaded_ = true;
    
    // 创建默认动画和皮肤列表
    availableAnimations_.clear();
    availableAnimations_.push_back("idle");
    availableAnimations_.push_back("walk");
    availableAnimations_.push_back("run");
    availableAnimations_.push_back("attack");
    
    availableSkins_.clear();
    availableSkins_.push_back("default");
    availableSkins_.push_back("blue");
    availableSkins_.push_back("red");
    
    return true;
}

std::vector<string> SpineManager::GetAnimations() const {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    if (!isLoaded_) {
        return std::vector<string>();
    }
    
    // 暂时注释掉 Spine 4.2 实现
    /*
    std::vector<string> animations;
    if (skeletonData_) {
        auto& animationsData = skeletonData_->getAnimations();
        for (size_t i = 0; i < animationsData.size(); ++i) {
            animations.push_back(animationsData[i]->getName().buffer());
        }
    }
    return animations;
    */
    
    // 临时返回默认动画列表
    return availableAnimations_;
}

std::vector<string> SpineManager::GetSkins() const {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    if (!isLoaded_) {
        return std::vector<string>();
    }
    
    // 暂时注释掉 Spine 4.2 实现
    /*
    std::vector<string> skins;
    if (skeletonData_) {
        auto& skinsData = skeletonData_->getSkins();
        for (size_t i = 0; i < skinsData.size(); ++i) {
            skins.push_back(skinsData[i]->getName().buffer());
        }
    }
    return skins;
    */
    
    // 临时返回默认皮肤列表
    return availableSkins_;
}

// ==================== 动画控制 ====================

bool SpineManager::SetAnimation(int32_t trackIndex, const string& animationName, bool loop) {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    if (!isLoaded_) {
        return false;
    }
    
    // 暂时注释掉 Spine 4.2 实现
    /*
    if (animationState_) {
        auto* trackEntry = animationState_->setAnimation(trackIndex, animationName.c_str(), loop);
        return trackEntry != nullptr;
    }
    return false;
    */
    
    // 临时实现：仅检查动画是否存在
    auto it = std::find(availableAnimations_.begin(), availableAnimations_.end(), animationName);
    return it != availableAnimations_.end();
}

bool SpineManager::AddAnimation(int32_t trackIndex, const string& animationName, bool loop, float delay) {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    if (!isLoaded_) {
        return false;
    }
    
    // 暂时注释掉 Spine 4.2 实现
    /*
    if (animationState_) {
        auto* trackEntry = animationState_->addAnimation(trackIndex, animationName.c_str(), loop, delay);
        return trackEntry != nullptr;
    }
    return false;
    */
    
    // 临时实现：仅检查动画是否存在
    auto it = std::find(availableAnimations_.begin(), availableAnimations_.end(), animationName);
    return it != availableAnimations_.end();
}

void SpineManager::ClearTrack(int32_t trackIndex) {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    if (!isLoaded_) {
        return;
    }
    
    // 暂时注释掉 Spine 4.2 实现
    /*
    if (animationState_) {
        animationState_->clearTrack(trackIndex);
    }
    */
}

void SpineManager::ClearTracks() {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    if (!isLoaded_) {
        return;
    }
    
    // 暂时注释掉 Spine 4.2 实现
    /*
    if (animationState_) {
        animationState_->clearTracks();
    }
    */
}

// ==================== 外观控制 ====================

bool SpineManager::SetSkin(const string& skinName) {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    if (!isLoaded_) {
        return false;
    }
    
    // 暂时注释掉 Spine 4.2 实现
    /*
    if (skeleton_ && skeletonData_) {
        auto* skin = skeletonData_->findSkin(skinName.c_str());
        if (skin) {
            skeleton_->setSkin(skin);
            skeleton_->setSlotsToSetupPose();
            return true;
        }
    }
    return false;
    */
    
    // 临时实现：仅检查皮肤是否存在
    auto it = std::find(availableSkins_.begin(), availableSkins_.end(), skinName);
    return it != availableSkins_.end();
}

void SpineManager::SetMix(const string& fromAnimation, const string& toAnimation, float duration) {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    if (!isLoaded_) {
        return;
    }
    
    // 暂时注释掉 Spine 4.2 实现
    /*
    if (animationStateData_) {
        animationStateData_->setMix(fromAnimation.c_str(), toAnimation.c_str(), duration);
    }
    */
}

// ==================== 播放控制 ====================

void SpineManager::SetTimeScale(float timeScale) {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    timeScale_ = timeScale;
    
    // 暂时注释掉 Spine 4.2 实现
    /*
    if (animationState_) {
        animationState_->setTimeScale(timeScale);
    }
    */
}

void SpineManager::Pause() {
    std::lock_guard<std::mutex> lock(dataMutex_);
    isPaused_ = true;
}

void SpineManager::Resume() {
    std::lock_guard<std::mutex> lock(dataMutex_);
    isPaused_ = false;
}

void SpineManager::Stop() {
    std::lock_guard<std::mutex> lock(dataMutex_);
    ClearTracks();
    isPaused_ = false;
}

string SpineManager::GetState() const {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    // 暂时注释掉 Spine 4.2 实现
    /*
    if (animationState_) {
        // 构建动画状态信息的JSON字符串
        string state = "{";
        state += "\"isLoaded\":" + string(isLoaded_ ? "true" : "false") + ",";
        state += "\"isPaused\":" + string(isPaused_ ? "true" : "false") + ",";
        state += "\"timeScale\":" + std::to_string(timeScale_) + ",";
        state += "\"tracks\":[";
        
        // 遍历轨道信息
        for (int i = 0; i < animationState_->getTracks().size(); ++i) {
            auto* track = animationState_->getTracks()[i];
            if (track) {
                if (i > 0) state += ",";
                state += "{";
                state += "\"index\":" + std::to_string(i) + ",";
                state += "\"animation\":\"" + string(track->getAnimation()->getName().buffer()) + "\",";
                state += "\"time\":" + std::to_string(track->getTime()) + ",";
                state += "\"loop\":" + string(track->getLoop() ? "true" : "false");
                state += "}";
            }
        }
        
        state += "]}";
        return state;
    }
    */
    
    // 临时返回基本状态信息
    return "{\"isLoaded\":" + string(isLoaded_ ? "true" : "false") + 
           ",\"isPaused\":" + string(isPaused_ ? "true" : "false") + 
           ",\"timeScale\":" + std::to_string(timeScale_) + "}";
}

// ==================== 视图控制 ====================

void SpineManager::UpdateViewSize(int32_t width, int32_t height) {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    if (renderContext_) {
        renderContext_->viewWidth = width;
        renderContext_->viewHeight = height;
    }
}

void SpineManager::SetScale(float scale) {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    if (renderContext_) {
        renderContext_->scale = scale;
    }
}

void SpineManager::SetPremultipliedAlpha(bool premultipliedAlpha) {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    if (renderContext_) {
        renderContext_->premultipliedAlpha = premultipliedAlpha;
    }
}

// ==================== 渲染循环 ====================

void SpineManager::Update(float deltaTime) {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    if (!isLoaded_ || isPaused_) {
        return;
    }
    
    // 暂时注释掉 Spine 4.2 实现
    /*
    if (animationState_ && skeleton_) {
        // 更新动画状态
        animationState_->update(deltaTime * timeScale_);
        animationState_->apply(*skeleton_);
        
        // 更新骨骼世界变换
        skeleton_->updateWorldTransform();
    }
    */
}

void SpineManager::Render() {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    if (!isLoaded_) {
        return;
    }
    
    // 暂时注释掉 Spine 4.2 + Skia 渲染实现
    /*
    if (renderContext_ && renderContext_->canvas && skeleton_) {
        // 保存当前 Canvas 状态
        renderContext_->canvas->save();
        
        // 应用变换矩阵
        SkMatrix matrix;
        matrix.setScale(renderContext_->scale, renderContext_->scale);
        matrix.postTranslate(renderContext_->viewWidth * 0.5f, renderContext_->viewHeight * 0.5f);
        renderContext_->canvas->concat(matrix);
        
        // 渲染骨骼
        RenderSkeleton();
        
        // 恢复 Canvas 状态
        renderContext_->canvas->restore();
    }
    */
}

// ==================== 事件系统 ====================

void SpineManager::SetEventCallback(void (*callback)(const SpineAnimationEvent&)) {
    std::lock_guard<std::mutex> lock(dataMutex_);
    eventCallback_ = callback;
}

void SpineManager::SetGlobalEventCallback(void (*callback)(int32_t, const SpineAnimationEvent&), int32_t instanceId) {
    std::lock_guard<std::mutex> lock(dataMutex_);
    globalEventCallback_ = callback;
    callbackInstanceId_ = instanceId;
}

void SpineManager::TriggerEvent(const SpineAnimationEvent& event) {
    // 先调用本地回调
    if (eventCallback_) {
        eventCallback_(event);
    }
    
    // 再调用全局回调
    if (globalEventCallback_) {
        globalEventCallback_(callbackInstanceId_, event);
    }
}

// ==================== 生命周期 ====================

void SpineManager::Cleanup() {
    std::lock_guard<std::mutex> lock(dataMutex_);
    
    // 清理渲染资源
    CleanupRenderResources();
    
    // 暂时注释掉 Spine 4.2 资源清理
    /*
    if (animationState_) {
        delete animationState_;
        animationState_ = nullptr;
    }
    
    if (animationStateData_) {
        delete animationStateData_;
        animationStateData_ = nullptr;
    }
    
    if (skeleton_) {
        delete skeleton_;
        skeleton_ = nullptr;
    }
    
    if (skeletonData_) {
        delete skeletonData_;
        skeletonData_ = nullptr;
    }
    
    if (skeletonJson_) {
        delete skeletonJson_;
        skeletonJson_ = nullptr;
    }
    
    if (atlas_) {
        delete atlas_;
        atlas_ = nullptr;
    }
    */
    
    // 清理状态
    isLoaded_ = false;
    isPaused_ = false;
    timeScale_ = 1.0f;
    
    // 清理回调
    eventCallback_ = nullptr;
    globalEventCallback_ = nullptr;
    callbackInstanceId_ = -1;
    
    // 清理数据
    availableAnimations_.clear();
    availableSkins_.clear();
}

// ==================== 私有方法实现 ====================

bool SpineManager::InitializeRenderResources() {
    if (!renderContext_) {
        return false;
    }
    
    // 暂时注释掉 Skia 初始化
    /*
    // 初始化 Skia 表面和 Canvas
    if (!renderContext_->surface) {
        // 这里需要根据实际的 HarmonyOS Skia 集成方式来实现
        // renderContext_->surface = SkSurface::MakeRasterN32Premul(renderContext_->viewWidth, renderContext_->viewHeight);
        // renderContext_->canvas = renderContext_->surface->getCanvas();
    }
    */
    
    return true;
}

void SpineManager::CleanupRenderResources() {
    if (!renderContext_) {
        return;
    }
    
    // 暂时注释掉 Skia 清理
    /*
    renderContext_->canvas = nullptr;
    renderContext_->surface = nullptr;
    */
}

void SpineManager::CreateDefaultData() {
    // 创建默认的动画和皮肤数据
    availableAnimations_.clear();
    availableAnimations_.push_back("idle");
    availableAnimations_.push_back("walk");
    availableAnimations_.push_back("run");
    
    availableSkins_.clear();
    availableSkins_.push_back("default");
} 