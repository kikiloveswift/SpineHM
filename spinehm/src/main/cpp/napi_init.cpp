#include <napi/native_api.h>
#include <hilog/log.h>
#include "spine_napi.h"


//static napi_value NAPI_Global_createSpineInstance(napi_env env, napi_callback_info info)
//{
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_destroySpineInstance(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//
//static napi_value NAPI_Global_setSurfaceId(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_setEventCallback(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_loadSpineData(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_setAnimation(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_addAnimation(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_setSkin(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_setMix(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_setTimeScale(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_pause(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_resume(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_render(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_update(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_cleanup(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_getSkins(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_getAnimations(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_updateViewSize(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_clearTrack(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}
//static napi_value NAPI_Global_clearTracks(napi_env env, napi_callback_info info) {
//    // TODO: implements the code;
//}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"createSpineInstance", nullptr, SpineNapi::CreateSpineInstance, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"destroySpineInstance", nullptr, SpineNapi::DestroySpineInstance, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setEventCallback", nullptr, SpineNapi::SetEventCallback, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"loadSpineData", nullptr, SpineNapi::LoadSpineData, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setAnimation", nullptr, SpineNapi::SetAnimation, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"addAnimation", nullptr, SpineNapi::AddAnimation, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setSkin", nullptr, SpineNapi::SetSkin, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setMix", nullptr, SpineNapi::SetMix, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setTimeScale", nullptr, SpineNapi::SetTimeScale, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"pause", nullptr, SpineNapi::Pause, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"resume", nullptr, SpineNapi::Resume, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"clearTracks", nullptr, SpineNapi::ClearTracks, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"clearTrack", nullptr, SpineNapi::ClearTrack, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"updateViewSize", nullptr, SpineNapi::UpdateViewSize, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getAnimations", nullptr, SpineNapi::GetAnimations, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getSkins", nullptr, SpineNapi::GetSkins, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"cleanup", nullptr, SpineNapi::Cleanup, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"update", nullptr, SpineNapi::Update, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"render", nullptr, SpineNapi::Render, nullptr, nullptr, nullptr, napi_default, nullptr},
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module spineModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "spinehm",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterSpinehmModule(void)
{
    napi_module_register(&spineModule);
}
