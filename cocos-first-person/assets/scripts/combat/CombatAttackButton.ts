import { _decorator, Component, Node } from 'cc';
import { PlayerCombat } from './PlayerCombat';

const { ccclass, property } = _decorator;

/** 挂到 UI「普攻」按钮 */
@ccclass('CombatAttackButton')
export class CombatAttackButton extends Component {
  @property(PlayerCombat)
  player: PlayerCombat | null = null;

  onLoad(): void {
    this.node.on(Node.EventType.TOUCH_END, () => this.player?.normalAttack(), this);
  }
}
