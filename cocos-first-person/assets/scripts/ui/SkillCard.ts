import {
  _decorator,
  Component,
  Node,
  Label,
  Sprite,
  SpriteFrame,
  Graphics,
  Color,
  UITransform,
  resources,
  CCString,
  Enum,
  EventTouch,
} from 'cc';
import { SkillAction } from './SkillTypes';

const { ccclass, property } = _decorator;

/**
 * 圆角方框技能卡：无图时显示文字；编辑器拖 SpriteFrame 或 resources 路径自动出图。
 */
@ccclass('SkillCard')
export class SkillCard extends Component {
  @property({ type: CCString })
  skillId = '';

  @property({ type: CCString })
  displayLabel = '';

  @property({ type: Enum(SkillAction) })
  action = SkillAction.NormalAttack;

  /** 编辑器直接拖图（优先） */
  @property(SpriteFrame)
  iconFrame: SpriteFrame | null = null;

  /** 如 skills/block/spriteFrame，对应 assets/resources/ */
  @property({ type: CCString })
  iconResourcePath = '';

  @property(Sprite)
  iconSprite: Sprite | null = null;

  @property(Label)
  label: Label | null = null;

  @property(Graphics)
  background: Graphics | null = null;

  @property({ type: CCString })
  clickEventName = 'skill-card-click';

  private ready = false;

  onLoad(): void {
    this.drawBackground();
    this.refreshVisual();
    if (this.action !== SkillAction.WeaponDisplay) {
      this.node.on(Node.EventType.TOUCH_END, this.onTap, this);
    }
  }

  configure(entry: {
    skillId: string;
    label: string;
    action: SkillAction;
    iconResourcePath?: string;
  }): void {
    this.skillId = entry.skillId;
    this.displayLabel = entry.label;
    this.action = entry.action;
    this.iconResourcePath = entry.iconResourcePath ?? '';
    this.refreshVisual();
  }

  refreshVisual(): void {
    if (this.label) {
      this.label.string = this.displayLabel;
    }
    if (this.iconFrame) {
      this.showIcon(this.iconFrame);
      return;
    }
    if (this.iconResourcePath) {
      resources.load(this.iconResourcePath, SpriteFrame, (err, sf) => {
        if (!err && sf) this.showIcon(sf);
        else this.showLabelOnly();
      });
      return;
    }
    this.showLabelOnly();
  }

  private showIcon(sf: SpriteFrame): void {
    if (this.iconSprite) {
      this.iconSprite.spriteFrame = sf;
      this.iconSprite.node.active = true;
    }
    if (this.label) this.label.node.active = false;
    this.ready = true;
  }

  private showLabelOnly(): void {
    if (this.iconSprite) this.iconSprite.node.active = false;
    if (this.label) {
      this.label.node.active = true;
      this.label.string = this.displayLabel;
    }
    this.ready = true;
  }

  private drawBackground(): void {
    const g = this.background;
    if (!g) return;
    const ui = this.getComponent(UITransform);
    const w = ui?.width ?? 72;
    const h = ui?.height ?? 72;
    const r = 10;
    g.clear();
    g.fillColor = new Color(38, 38, 48, 230);
    g.roundRect(-w / 2, -h / 2, w, h, r);
    g.fill();
    g.lineWidth = 2;
    g.strokeColor = new Color(90, 88, 110, 255);
    g.roundRect(-w / 2, -h / 2, w, h, r);
    g.stroke();
  }

  private onTap(_e: EventTouch): void {
    if (!this.ready || this.action === SkillAction.WeaponDisplay) return;
    this.node.emit(this.clickEventName, {
      skillId: this.skillId,
      action: this.action,
    });
  }
}
