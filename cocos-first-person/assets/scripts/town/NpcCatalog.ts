import { _decorator, Component } from 'cc';
import { NpcDialogueSet } from './DialogueTypes';

const { ccclass, property } = _decorator;

@ccclass('NpcCatalog')
export class NpcCatalog extends Component {
  @property({ type: [NpcDialogueSet] })
  npcs: NpcDialogueSet[] = [];

  find(npcId: string): NpcDialogueSet | undefined {
    return this.npcs.find((n) => n.npcId === npcId);
  }
}
