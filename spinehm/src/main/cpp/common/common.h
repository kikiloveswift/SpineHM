//
// Created on 2025/8/1.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef SPINEHM_COMMON_H
#define SPINEHM_COMMON_H
#include <iostream>

/**
 * Spine 加载选项结构
 */
struct SpineLoadOptions {
    float scale = 1.0f;
    bool premultipliedAlpha = true;
    bool debugMode = false;
};

/**
 * Spine 事件数据结构
 */
struct SpineEventData {
    std::string name;
    int intValue;
    float floatValue;
    std::string stringValue;
    float time;
    float balance;
    float volume;
};

/**
 * Spine 动画事件结构
 */
struct SpineAnimationEvent {
    std::string type;
    int trackIndex;
    std::string animation;
    SpineEventData* eventData;
};

/**
 * 事件回调函数类型
 */
typedef void (*SpineEventCallback)(const SpineAnimationEvent& event);



#endif //SPINEHM_COMMON_H
