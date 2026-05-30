import { _decorator, Component, Node } from 'cc';
import { GameEvents } from '../core/GameEvents';
import { TunnelForwardController } from '../tunnel/TunnelForwardController';
import { TunnelTapArea } from '../tunnel/TunnelTapArea';

const { ccclass, property } = _decorator;

/** 战斗时禁止隧道前进 */
@ccclass('TunnelCombatGate')
export class TunnelCombatGate extends Component {
  @property(TunnelForwardController)
  tunnel: TunnelForwardController | null = null;

  @property(TunnelTapArea)
  tapArea: TunnelTapArea | null = null;

  @property(Node)
  eventBus: Node | null = null;

  onLoad(): void {
    const bus = this.eventBus ?? this.node;
    bus.on(GameEvents.EXPLORING_DISABLED, this.lock, this);
    bus.on(GameEvents.EXPLORING_ENABLED, this.unlock, this);
  }

  onDestroy(): void {
    const bus = this.eventBus ?? this.node;
    bus.off(GameEvents.EXPLORING_DISABLED, this.lock, this);
    bus.off(GameEvents.EXPLORING_ENABLED, this.unlock, this);
  }

  private lock(): void {
    if (this.tunnel) this.tunnel.blockInputWhileStepping = true;
    if (this.tapArea) this.tapArea.enabled = false;
  }

  private unlock(): void {
    if (this.tunnel) this.tunnel.blockInputWhileStepping = true;
    if (this.tapArea) this.tapArea.enabled = true;
  }
}
