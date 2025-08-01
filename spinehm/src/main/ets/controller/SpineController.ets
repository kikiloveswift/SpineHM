// 引入原生模块（需要在原生代码中实现）
import spineNative from 'libspinehm.so';

/**
 * 动画轨道信息
 */
export interface SpineTrackEntry {
  trackIndex: number;
  animation: string;
  loop: boolean;
  delay: number;
  mixDuration: number;
}

interface SpineEventData {
  time: number;
  intValue: number;
  floatValue: number;
  stringValue?: string;
  voulume: number;
  balance: number;
}

/**
 * 动画事件类型
 */
export interface SpineAnimationEvent {
  type: 'start' | 'interrupt' | 'end' | 'dispose' | 'complete' | 'event';
  trackIndex: number;
  animation: string;
  data?: SpineEventData;
}

/**
 * 事件回调接口
 */
export interface SpineEventCallbacks {
  onAnimationStart?: (trackIndex: number, animation: string) => void;
  onAnimationComplete?: (trackIndex: number, animation: string) => void;
  onAnimationEvent?: (trackIndex: number, event: string) => void;
  onAnimationInterrupt?: (trackIndex: number, animation: string) => void;
  onAnimationEnd?: (trackIndex: number, animation: string) => void;
}

export interface SpineDataOption {
  scale?: number;
  premultipliedAlpha?: boolean;
}

interface GeneratedObjectLiteralInterface_1 {
  isInitialized: boolean;
  isPaused: boolean;
  timeScale: number;
  currentSpineData: string;
  currentAtlasData: string;
  trackCount: number;
}

interface GeneratedObjectLiteralInterface_2 {
  scale: number;
  premultipliedAlpha: boolean;
  debugMode: boolean;
}

export class SpineController {
  private nativeInstanceId: number = -1;
  private isInitialized: boolean = false;
  private isPaused: boolean = false;
  private timeScale: number = 1.0;
  private eventCallbacks: SpineEventCallbacks = {};
  // 当前加载的资源信息
  private currentSpineData: string = '';
  private currentAtlasData: string = '';
  // 动画轨道状态
  private trackEntries: Map<number, SpineTrackEntry> = new Map();

  constructor() {
    // 构造函数中初始化原生实例
    this.nativeInstanceId = this.createNativeInstance();
  }

  /**
   * 创建原生实例
   * @returns 原生实例ID
   */
  private createNativeInstance(): number {
    try {
      return spineNative.createSpineInstance();
    } catch (error) {
      console.error('Failed to create native spine instance:', error);
      return -1;
    }
  }

  /**
   * 设置 Surface ID
   * @param surfaceId XComponent 的 Surface ID
   */
  setSurfaceId(surfaceId: string) {
    if (this.nativeInstanceId !== -1) {
      spineNative.setSurfaceId(this.nativeInstanceId, surfaceId);
    }
  }

  /**
   * 设置事件回调
   * @param callbacks 事件回调对象
   */
  setEventCallbacks(callbacks: SpineEventCallbacks) {
    // this.eventCallbacks = { ...callbacks };

    // 设置原生事件回调
    if (this.nativeInstanceId !== -1) {
      spineNative.setEventCallback(this.nativeInstanceId, (event: SpineAnimationEvent) => {
        this.handleNativeEvent(event);
      });
    }
  }

  /**
   * 处理原生事件
   * @param event 动画事件
   */
  private handleNativeEvent(event: SpineAnimationEvent) {
    switch (event.type) {
      case 'start':
        this.eventCallbacks.onAnimationStart?.(event.trackIndex, event.animation);
        break;
      case 'complete':
        this.eventCallbacks.onAnimationComplete?.(event.trackIndex, event.animation);
        break;
      case 'event':
        this.eventCallbacks.onAnimationEvent?.(event.trackIndex, event.data?.stringValue ?? "");
        break;
      case 'interrupt':
        this.eventCallbacks.onAnimationInterrupt?.(event.trackIndex, event.animation);
        break;
      case 'end':
        this.eventCallbacks.onAnimationEnd?.(event.trackIndex, event.animation);
        break;
    }
  }

  /**
   * 加载 Spine 数据
   * @param spineDataPath Spine 数据文件路径（.json 或 .skel）
   * @param atlasDataPath 图集文件路径（.atlas）
   * @param options 加载选项
   * @returns 是否加载成功
   */
  loadSpineData(spineDataPath: string, atlasDataPath: string, options?: SpineDataOption): boolean {
    if (this.nativeInstanceId === -1) {
      console.error('Native instance not initialized');
      return false;
    }

    try {
      const loadOptions: GeneratedObjectLiteralInterface_2 = {
        scale: options?.scale ?? 1.0,
        premultipliedAlpha: options?.premultipliedAlpha ?? true,
        debugMode: false
      };

      const result = spineNative.loadSpineData(
        this.nativeInstanceId,
        spineDataPath,
        atlasDataPath,
        loadOptions
      );

      if (result) {
        this.currentSpineData = spineDataPath;
        this.currentAtlasData = atlasDataPath;
        this.isInitialized = true;
        console.log('Spine data loaded successfully');
      } else {
        console.error('Failed to load spine data');
      }

      return result;
    } catch (error) {
      console.error('Error loading spine data:', error);
      return false;
    }
  }

  /**
   * 设置动画
   * @param trackIndex 动画轨道索引
   * @param animationName 动画名称
   * @param loop 是否循环
   * @returns 动画轨道条目
   */
  setAnimation(trackIndex: number, animationName: string, loop: boolean = true): SpineTrackEntry | null {
    if (!this.isInitialized || this.nativeInstanceId === -1) {
      console.error('Spine not initialized');
      return null;
    }

    try {
      const result = spineNative.setAnimation(this.nativeInstanceId, trackIndex, animationName, loop);

      if (result) {
        const trackEntry: SpineTrackEntry = {
          trackIndex,
          animation: animationName,
          loop,
          delay: 0,
          mixDuration: 0
        };

        this.trackEntries.set(trackIndex, trackEntry);
        return trackEntry;
      }
    } catch (error) {
      console.error('Error setting animation:', error);
    }

    return null;
  }

  /**
   * 添加动画到队列
   * @param trackIndex 动画轨道索引
   * @param animationName 动画名称
   * @param loop 是否循环
   * @param delay 延迟时间（秒）
   * @returns 动画轨道条目
   */
  addAnimation(trackIndex: number, animationName: string, loop: boolean = false,
    delay: number = 0): SpineTrackEntry | null {
    if (!this.isInitialized || this.nativeInstanceId === -1) {
      console.error('Spine not initialized');
      return null;
    }

    try {
      const result = spineNative.addAnimation(this.nativeInstanceId, trackIndex, animationName, loop, delay);

      if (result) {
        const trackEntry: SpineTrackEntry = {
          trackIndex,
          animation: animationName,
          loop,
          delay,
          mixDuration: 0
        };

        return trackEntry;
      }
    } catch (error) {
      console.error('Error adding animation:', error);
    }

    return null;
  }

  /**
   * 设置皮肤
   * @param skinName 皮肤名称
   * @returns 是否设置成功
   */
  setSkin(skinName: string): boolean {
    if (!this.isInitialized || this.nativeInstanceId === -1) {
      console.error('Spine not initialized');
      return false;
    }

    try {
      return spineNative.setSkin(this.nativeInstanceId, skinName);
    } catch (error) {
      console.error('Error setting skin:', error);
      return false;
    }
  }

  /**
   * 设置动画混合时间
   * @param fromAnimation 源动画名称
   * @param toAnimation 目标动画名称
   * @param duration 混合时间（秒）
   */
  setMix(fromAnimation: string, toAnimation: string, duration: number) {
    if (!this.isInitialized || this.nativeInstanceId === -1) {
      console.error('Spine not initialized');
      return;
    }

    try {
      spineNative.setMix(this.nativeInstanceId, fromAnimation, toAnimation, duration);
    } catch (error) {
      console.error('Error setting mix:', error);
    }
  }

  /**
   * 设置时间缩放
   * @param timeScale 时间缩放值
   */
  setTimeScale(timeScale: number) {
    this.timeScale = timeScale;

    if (this.nativeInstanceId !== -1) {
      try {
        spineNative.setTimeScale(this.nativeInstanceId, timeScale);
      } catch (error) {
        console.error('Error setting time scale:', error);
      }
    }
  }

  /**
   * 暂停动画
   */
  pause() {
    this.isPaused = true;

    if (this.nativeInstanceId !== -1) {
      try {
        spineNative.pause(this.nativeInstanceId);
      } catch (error) {
        console.error('Error pausing animation:', error);
      }
    }
  }

  /**
   * 恢复动画
   */
  resume() {
    this.isPaused = false;

    if (this.nativeInstanceId !== -1) {
      try {
        spineNative.resume(this.nativeInstanceId);
      } catch (error) {
        console.error('Error resuming animation:', error);
      }
    }
  }

  /**
   * 停止所有动画
   */
  stop() {
    if (this.nativeInstanceId !== -1) {
      try {
        spineNative.clearTracks(this.nativeInstanceId);
        this.trackEntries.clear();
      } catch (error) {
        console.error('Error stopping animations:', error);
      }
    }
  }

  /**
   * 清除指定轨道的动画
   * @param trackIndex 动画轨道索引
   */
  clearTrack(trackIndex: number) {
    if (this.nativeInstanceId !== -1) {
      try {
        spineNative.clearTrack(this.nativeInstanceId, trackIndex);
        this.trackEntries.delete(trackIndex);
      } catch (error) {
        console.error('Error clearing track:', error);
      }
    }
  }

  /**
   * 更新视图尺寸
   * @param width 宽度
   * @param height 高度
   */
  updateViewSize(width: number, height: number) {
    if (this.nativeInstanceId !== -1) {
      try {
        spineNative.updateViewSize(this.nativeInstanceId, width, height);
      } catch (error) {
        console.error('Error updating view size:', error);
      }
    }
  }

  /**
   * 获取动画列表
   * @returns 动画名称数组
   */
  getAnimations(): string[] {
    if (!this.isInitialized || this.nativeInstanceId === -1) {
      return [];
    }

    try {
      return spineNative.getAnimations(this.nativeInstanceId) || [];
    } catch (error) {
      console.error('Error getting animations:', error);
      return [];
    }
  }

  /**
   * 获取皮肤列表
   * @returns 皮肤名称数组
   */
  getSkins(): string[] {
    if (!this.isInitialized || this.nativeInstanceId === -1) {
      return [];
    }

    try {
      return spineNative.getSkins(this.nativeInstanceId) || [];
    } catch (error) {
      console.error('Error getting skins:', error);
      return [];
    }
  }

  /**
   * 获取当前播放状态
   */
  getState() {
    return ({
      isInitialized: this.isInitialized,
      isPaused: this.isPaused,
      timeScale: this.timeScale,
      currentSpineData: this.currentSpineData,
      currentAtlasData: this.currentAtlasData,
      trackCount: this.trackEntries.size
    } as GeneratedObjectLiteralInterface_1);
  }

  /**
   * 清理资源
   */
  cleanup() {
    this.stop();

    if (this.nativeInstanceId !== -1) {
      try {
        spineNative.cleanup(this.nativeInstanceId);
      } catch (error) {
        console.error('Error during cleanup:', error);
      }
    }
  }

  /**
   * 销毁控制器
   */
  destroy() {
    this.cleanup();

    if (this.nativeInstanceId !== -1) {
      try {
        spineNative.destroySpineInstance(this.nativeInstanceId);
        this.nativeInstanceId = -1;
      } catch (error) {
        console.error('Error destroying spine instance:', error);
      }
    }

    this.isInitialized = false;
    this.trackEntries.clear();
    this.eventCallbacks = {};
  }
}