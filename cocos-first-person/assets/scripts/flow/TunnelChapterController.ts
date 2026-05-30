import { _decorator, Component, Node, Sprite, Label, CCBoolean } from 'cc';
import { GameEvents } from '../core/GameEvents';
import { GameChapterConfig } from './GameChapterConfig';
import { TunnelSceneSequence } from '../tunnel/TunnelSceneSequence';

const { ccclass, property } = _decorator;

/**
 * 隧道循环 + 达标后最深处换「城镇大门」贴图。
 */
@ccclass('TunnelChapterController')
export class TunnelChapterController extends Component {
  @property(GameChapterConfig)
  chapter: GameChapterConfig | null = null;

  @property(TunnelSceneSequence)
  tunnelSequence: TunnelSceneSequence | null = null;

  /** 最深处 Inner 或专用 GateSprite（与隧道透视对齐） */
  @property(Sprite)
  deepLayerSprite: Sprite | null = null;

  @property(Node)
  gateInteractRoot: Node | null = null;

  @property(Label)
  hintLabel: Label | null = null;

  @property(Node)
  eventBus: Node | null = null;

  @property({ type: CCBoolean })
  gateRevealed = false;

  private totalSteps = 0;
  private totalKills = 0;
  private stepsSinceGate = 0;

  onLoad(): void {
    const bus = this.eventBus ?? this.node;
    bus.on(GameEvents.TUNNEL_STEP_DONE, this.onStep, this);
    bus.on(GameEvents.MONSTER_DEFEATED, this.onKill, this);
    this.applyLoopFrames();
    if (this.gateInteractRoot) this.gateInteractRoot.active = false;
  }

  onDestroy(): void {
    const bus = this.eventBus ?? this.node;
    bus.off(GameEvents.TUNNEL_STEP_DONE, this.onStep, this);
    bus.off(GameEvents.MONSTER_DEFEATED, this.onKill, this);
  }

  private applyLoopFrames(): void {
    const cfg = this.chapter;
    if (!cfg?.tunnelLoopFrames.length || !this.tunnelSequence) return;
    this.tunnelSequence.frames = cfg.tunnelLoopFrames;
    this.tunnelSequence.loopSequence = true;
  }

  private onStep(): void {
    this.totalSteps += 1;
    if (!this.gateRevealed) {
      this.checkRevealGate();
      return;
    }
    this.stepsSinceGate += 1;
    this.updateGateHint();
  }

  private onKill(): void {
    this.totalKills += 1;
    if (!this.gateRevealed) this.checkRevealGate();
  }

  private checkRevealGate(): void {
    const cfg = this.chapter;
    if (!cfg) return;

    const stepsOk = this.totalSteps >= cfg.stepsToRevealGate;
    const killsOk = this.totalKills >= cfg.killsToRevealGate;
    const reveal = cfg.requireBothForGate ? stepsOk && killsOk : stepsOk || killsOk;

    if (!reveal || !cfg.gateFrame) return;

    this.gateRevealed = true;
    if (this.deepLayerSprite) {
      this.deepLayerSprite.spriteFrame = cfg.gateFrame;
    }
    if (this.tunnelSequence) this.tunnelSequence.loopSequence = false;

    this.emit(GameEvents.GATE_REVEALED, {
      steps: this.totalSteps,
      kills: this.totalKills,
    });
    this.updateGateHint();
  }

  private updateGateHint(): void {
    const cfg = this.chapter;
    if (!cfg || !this.gateRevealed) return;

    const canEnter = this.stepsSinceGate >= cfg.stepsAfterGateToEnter;
    if (this.gateInteractRoot) {
      this.gateInteractRoot.active = canEnter;
    }
    if (this.hintLabel) {
      this.hintLabel.string = canEnter ? '点击大门进入城镇' : '继续向前…';
    }
  }

  private emit(event: string, detail?: unknown): void {
    this.eventBus?.emit(event, detail);
    this.node.emit(event, detail);
  }
}
