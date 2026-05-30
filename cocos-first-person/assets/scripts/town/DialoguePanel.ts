import { _decorator, Component, Node, Label, Button, Prefab, instantiate } from 'cc';
import { NpcDialogueSet, DialogueOptionRow } from './DialogueTypes';

const { ccclass, property } = _decorator;

@ccclass('DialoguePanel')
export class DialoguePanel extends Component {
  @property(Node)
  panelRoot: Node | null = null;

  @property(Label)
  nameLabel: Label | null = null;

  @property(Label)
  bodyLabel: Label | null = null;

  @property(Node)
  optionsRoot: Node | null = null;

  @property(Prefab)
  optionButtonPrefab: Prefab | null = null;

  private current: NpcDialogueSet | null = null;

  onLoad(): void {
    this.hide();
  }

  open(npc: NpcDialogueSet): void {
    this.current = npc;
    const root = this.panelRoot ?? this.node;
    root.active = true;
    if (this.nameLabel) this.nameLabel.string = npc.displayName;
    if (this.bodyLabel) this.bodyLabel.string = npc.greeting;
    this.buildOptions(npc.options);
  }

  hide(): void {
    const root = this.panelRoot ?? this.node;
    root.active = false;
    this.current = null;
  }

  private buildOptions(options: DialogueOptionRow[]): void {
    const root = this.optionsRoot;
    if (!root) return;
    root.removeAllChildren();

    for (const opt of options) {
      if (this.optionButtonPrefab) {
        const n = instantiate(this.optionButtonPrefab);
        root.addChild(n);
        const lab = n.getComponentInChildren(Label);
        if (lab) lab.string = opt.label;
        n.on(Button.EventType.CLICK, () => this.pick(opt), this);
      }
    }
  }

  private pick(opt: DialogueOptionRow): void {
    this.node.emit('dialogue-option', {
      npcId: this.current?.npcId,
      optionId: opt.optionId,
      actionType: opt.actionType,
    });
    if (opt.actionType === 'close') this.hide();
    else if (this.bodyLabel) {
      this.bodyLabel.string = `（${opt.actionType}）${opt.label}`;
    }
  }
}
