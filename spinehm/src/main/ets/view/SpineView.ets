import { SpineController, SpineDataOption } from '../controller/SpineController';
import XComponentContext from '../interface/XComponentContext';

@Component
export struct SpineView {
  // Spine 控制器
  private controller: SpineController = new SpineController();

  // XComponent 相关属性
  private xComponentId: string = '';
  private surfaceId: string = '';

  // 视图尺寸
  @State private viewWidth: number = 0;
  @State private viewHeight: number = 0;

  // 初始化参数
  @Prop spineData?: string; // Spine 数据文件路径
  @Prop atlasData?: string; // 图集文件路径
  @Prop scaleFactor?: number; // 缩放比例
  @Prop premultipliedAlpha?: boolean; // 是否预乘 Alpha

  // 动画事件回调
  @Prop onAnimationStart?: (trackIndex: number, animation: string) => void;
  @Prop onAnimationComplete?: (trackIndex: number, animation: string) => void;
  @Prop onAnimationEvent?: (trackIndex: number, event: string) => void;

  // 组件构建回调
  @BuilderParam contentBuilder?: () => void;

  private xComponentContext: XComponentContext | undefined = undefined;

  aboutToAppear() {
    // 生成唯一的组件ID
    this.xComponentId = `spine_view_${Date.now()}_${Math.random().toString(36).substr(2, 9)}`;

    // 初始化控制器
    this.controller.setEventCallbacks({
      onAnimationStart: this.onAnimationStart,
      onAnimationComplete: this.onAnimationComplete,
      onAnimationEvent: this.onAnimationEvent
    });
  }

  aboutToDisappear() {
    // 清理资源
    this.controller.destroy();
  }

  build() {
    Stack() {
      XComponent({
        id: this.xComponentId,
        type: XComponentType.SURFACE,
        libraryname: 'spine' // 对应的原生库名称
      })
        .onLoad((xComponentContext) => {
          this.xComponentContext = xComponentContext as XComponentContext;
          this.controller.setSurfaceId(this.xComponentId);

          // 初始化 Spine 渲染器
          this.initializeSpineRenderer();
        })
        .onDestroy(() => {
          // XComponent 销毁时清理资源
          this.controller.cleanup();
        })
        .backgroundColor(Color.Transparent)
        .width('100%')
        .height('100%')

      // 如果有自定义内容构建器，则渲染
      if (this.contentBuilder) {
        this.contentBuilder();
      }
    }
    .width('100%')
    .height('100%')
    .onAreaChange((oldArea, newArea) => {
      // 监听区域变化，更新视图尺寸
      this.viewWidth = newArea.width as number;
      this.viewHeight = newArea.height as number;
      this.controller.updateViewSize(this.viewWidth, this.viewHeight);
    })
  }

  /**
   * 初始化 Spine 渲染器
   */
  private initializeSpineRenderer() {
    if (this.spineData && this.atlasData) {
      this.controller.loadSpineData(
        this.spineData,
        this.atlasData,
        {
          scale: this.scaleFactor ?? 1.0,
          premultipliedAlpha: this.premultipliedAlpha ?? true
        }
      );
    }
  }

  /**
   * 获取 Spine 控制器实例
   * @returns SpineController 实例
   */
  getController(): SpineController {
    return this.controller;
  }

  /**
   * 设置 Spine 数据
   * @param spineDataPath Spine 数据文件路径
   * @param atlasDataPath 图集文件路径
   * @param options 可选参数
   */
  setSpineData(spineDataPath: string, atlasDataPath: string, options?: SpineDataOption) {
    this.controller.loadSpineData(spineDataPath, atlasDataPath, options);
  }

  /**
   * 播放动画
   * @param animationName 动画名称
   * @param loop 是否循环
   * @param trackIndex 动画轨道索引
   */
  setAnimation(animationName: string, loop: boolean = true, trackIndex: number = 0) {
    this.controller.setAnimation(trackIndex, animationName, loop);
  }

  /**
   * 添加动画到队列
   * @param animationName 动画名称
   * @param loop 是否循环
   * @param delay 延迟时间
   * @param trackIndex 动画轨道索引
   */
  addAnimation(animationName: string, loop: boolean = false, delay: number = 0, trackIndex: number = 0) {
    this.controller.addAnimation(trackIndex, animationName, loop, delay);
  }

  /**
   * 设置皮肤
   * @param skinName 皮肤名称
   */
  setSkin(skinName: string) {
    this.controller.setSkin(skinName);
  }

  /**
   * 设置时间缩放
   * @param timeScale 时间缩放值
   */
  setTimeScale(timeScale: number) {
    this.controller.setTimeScale(timeScale);
  }

  /**
   * 暂停动画
   */
  pause() {
    this.controller.pause();
  }

  /**
   * 恢复动画
   */
  resume() {
    this.controller.resume();
  }

  /**
   * 停止所有动画
   */
  stop() {
    this.controller.stop();
  }
}