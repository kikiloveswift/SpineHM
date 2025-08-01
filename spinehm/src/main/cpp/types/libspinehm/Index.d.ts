/**
 * Spine 加载选项
 */
export interface SpineLoadOptions {
  scale: number;
  premultipliedAlpha: boolean;
  debugMode: boolean;
}

/**
 * Spine 事件数据
 */
export interface SpineEventData {
  name: string;
  intValue: number;
  floatValue: number;
  stringValue: string;
  time: number;
  balance: number;
  volume: number;
}

/**
 * Spine 动画事件
 */
export interface SpineAnimationEvent {
  type: 'start' | 'interrupt' | 'end' | 'dispose' | 'complete' | 'event';
  trackIndex: number;
  animation: string;
  eventData?: SpineEventData;
}

/**
 * 事件回调函数类型
 */
export type SpineEventCallback = (event: SpineAnimationEvent) => void;

/**
 * Spine Native 模块接口
 */
declare namespace spineNative {

  /**
   * 创建 Spine 实例
   * @returns 实例ID，失败返回 -1
   */
  function createSpineInstance(surfaceId: string): number;

  /**
   * 销毁 Spine 实例
   * @param instanceId 实例ID
   * @returns 是否成功
   */
  function destroySpineInstance(instanceId: number): boolean;

  /**
   * 设置事件回调
   * @param instanceId 实例ID
   * @param callback 事件回调函数
   * @returns 是否成功
   */
  function setEventCallback(instanceId: number, callback: SpineEventCallback): boolean;

  /**
   * 加载 Spine 数据
   * @param instanceId 实例ID
   * @param spineDataPath Spine 数据文件路径
   * @param atlasDataPath 图集文件路径
   * @param options 加载选项
   * @returns 是否成功
   */
  function loadSpineData(
    instanceId: number,
    spineDataPath: string,
    atlasDataPath: string,
    options: SpineLoadOptions
  ): boolean;

  /**
   * 设置动画
   * @param instanceId 实例ID
   * @param trackIndex 轨道索引
   * @param animationName 动画名称
   * @param loop 是否循环
   * @returns 是否成功
   */
  function setAnimation(
    instanceId: number,
    trackIndex: number,
    animationName: string,
    loop: boolean
  ): boolean;

  /**
   * 添加动画到队列
   * @param instanceId 实例ID
   * @param trackIndex 轨道索引
   * @param animationName 动画名称
   * @param loop 是否循环
   * @param delay 延迟时间（秒）
   * @returns 是否成功
   */
  function addAnimation(
    instanceId: number,
    trackIndex: number,
    animationName: string,
    loop: boolean,
    delay: number
  ): boolean;

  /**
   * 设置皮肤
   * @param instanceId 实例ID
   * @param skinName 皮肤名称
   * @returns 是否成功
   */
  function setSkin(instanceId: number, skinName: string): boolean;

  /**
   * 设置动画混合时间
   * @param instanceId 实例ID
   * @param fromAnimation 源动画名称
   * @param toAnimation 目标动画名称
   * @param duration 混合时间（秒）
   * @returns 是否成功
   */
  function setMix(
    instanceId: number,
    fromAnimation: string,
    toAnimation: string,
    duration: number
  ): boolean;

  /**
   * 设置时间缩放
   * @param instanceId 实例ID
   * @param timeScale 时间缩放值
   * @returns 是否成功
   */
  function setTimeScale(instanceId: number, timeScale: number): boolean;

  /**
   * 暂停动画
   * @param instanceId 实例ID
   * @returns 是否成功
   */
  function pause(instanceId: number): boolean;

  /**
   * 恢复动画
   * @param instanceId 实例ID
   * @returns 是否成功
   */
  function resume(instanceId: number): boolean;

  /**
   * 清除所有轨道
   * @param instanceId 实例ID
   * @returns 是否成功
   */
  function clearTracks(instanceId: number): boolean;

  /**
   * 清除指定轨道
   * @param instanceId 实例ID
   * @param trackIndex 轨道索引
   * @returns 是否成功
   */
  function clearTrack(instanceId: number, trackIndex: number): boolean;

  /**
   * 更新视图尺寸
   * @param instanceId 实例ID
   * @param width 宽度
   * @param height 高度
   * @returns 是否成功
   */
  function updateViewSize(instanceId: number, width: number, height: number): boolean;

  /**
   * 获取动画列表
   * @param instanceId 实例ID
   * @returns 动画名称数组
   */
  function getAnimations(instanceId: number): string[];

  /**
   * 获取皮肤列表
   * @param instanceId 实例ID
   * @returns 皮肤名称数组
   */
  function getSkins(instanceId: number): string[];

  /**
   * 清理资源
   * @param instanceId 实例ID
   * @returns 是否成功
   */
  function cleanup(instanceId: number): boolean;

  /**
   * 更新动画（每帧调用）
   * @param instanceId 实例ID
   * @param deltaTime 帧间隔时间（秒）
   * @returns 是否成功
   */
  function update(instanceId: number, deltaTime: number): boolean;

  /**
   * 渲染（每帧调用）
   * @param instanceId 实例ID
   * @returns 是否成功
   */
  function render(instanceId: number): boolean;
}

export default spineNative; 