import { _decorator, Component, director, CCString } from 'cc';
import { GameEvents } from '../core/GameEvents';

const { ccclass, property } = _decorator;

/** 城镇场景入口：返回森林等 */
@ccclass('TownDirector')
export class TownDirector extends Component {
  @property({ type: CCString })
  returnSceneName = 'Game';

  onLoad(): void {
    this.node.emit(GameEvents.ENTER_TOWN);
  }

  returnToTunnel(): void {
    director.loadScene(this.returnSceneName);
  }
}
