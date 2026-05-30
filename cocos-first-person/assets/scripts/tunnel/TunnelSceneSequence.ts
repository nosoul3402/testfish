import {
  _decorator,
  Component,
  Sprite,
  SpriteFrame,
  Node,
  CCInteger,
  CCBoolean,
} from 'cc';
import { GameEvents } from '../core/GameEvents';
import { TunnelForwardController } from './TunnelForwardController';

const { ccclass, property } = _decorator;

/**
 * 多段场景帧：每次前进结束后可换外层/内层贴图，实现“无限走廊”或关卡衔接。
 *
 * - frames：按顺序播放的场景 PNG（SpriteFrame）
 * - 在最后一帧可触发换场景（配合 Director.loadScene）
 * - loopSequence：到末尾后回到第 0 张，实现无限前进
 */
@ccclass('TunnelSceneSequence')
export class TunnelSceneSequence extends Component {
  @property([SpriteFrame])
  frames: SpriteFrame[] = [];

  /** 外层门框图（当前走廊） */
  @property(Sprite)
  outerFrame: Sprite | null = null;

  /** 内层嵌套图 */
  @property(Sprite)
  innerFrame: Sprite | null = null;

  @property(TunnelForwardController)
  tunnel: TunnelForwardController | null = null;

  @property(Node)
  eventBus: Node | null = null;

  /** 每前进几次换下一帧（1 = 每次前进都换） */
  @property({ type: CCInteger })
  stepsPerFrame = 1;

  @property({ type: CCBoolean })
  loopSequence = true;

  /** 是否在「刚进入最后一帧」时发事件（用于接 loadScene） */
  @property({ type: CCBoolean })
  emitOnLastFrame = true;

  /** 为 true 时仅在到达最后一帧时换图（不在每步换） */
  @property({ type: CCBoolean })
  changeTextureOnlyOnLastFrame = false;

  private frameIndex = 0;
  private stepCount = 0;

  onLoad(): void {
    const bus = this.eventBus ?? this.node;
    bus.on(GameEvents.TUNNEL_STEP_DONE, this.onStepDone, this);
    this.applyFrame(0);
  }

  onDestroy(): void {
    const bus = this.eventBus ?? this.node;
    bus.off(GameEvents.TUNNEL_STEP_DONE, this.onStepDone, this);
  }

  private onStepDone(): void {
    this.stepCount += 1;
    if (this.stepCount < this.stepsPerFrame) return;
    this.stepCount = 0;

    const lastIndex = this.frames.length - 1;
    if (this.changeTextureOnlyOnLastFrame) {
      if (this.frameIndex < lastIndex) {
        const next = this.frameIndex + 1;
        this.emit(GameEvents.SCENE_FRAME_WILL_CHANGE, { index: next });
        this.applyFrame(next);
        this.emit(GameEvents.SCENE_FRAME_CHANGED, {
          index: next,
          isLast: next === lastIndex,
        });
      } else if (this.loopSequence) {
        this.applyFrame(0);
      } else if (this.emitOnLastFrame) {
        this.emit(GameEvents.SCENE_FRAME_CHANGED, { index: lastIndex, isLast: true });
      }
      return;
    }

    const next = this.frameIndex + 1;
    if (next >= this.frames.length) {
      if (this.loopSequence) {
        this.applyFrame(0);
      } else if (this.emitOnLastFrame) {
        this.emit(GameEvents.SCENE_FRAME_CHANGED, { index: this.frameIndex, isLast: true });
      }
      return;
    }

    this.emit(GameEvents.SCENE_FRAME_WILL_CHANGE, { index: next });
    this.applyFrame(next);
    this.emit(GameEvents.SCENE_FRAME_CHANGED, {
      index: next,
      isLast: next === lastIndex,
    });
  }

  private applyFrame(index: number): void {
    if (!this.frames.length) return;
    this.frameIndex = index % this.frames.length;
    const sf = this.frames[this.frameIndex];
    if (this.outerFrame) this.outerFrame.spriteFrame = sf;
    if (this.innerFrame) {
      const nextSf = this.frames[(this.frameIndex + 1) % this.frames.length] ?? sf;
      this.innerFrame.spriteFrame = nextSf;
    }
  }

  private emit(event: string, detail?: unknown): void {
    this.eventBus?.emit(event, detail);
    this.node.emit(event, detail);
  }
}
