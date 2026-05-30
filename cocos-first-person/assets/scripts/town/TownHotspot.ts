import { _decorator, Component, Node, Enum, EventTouch } from 'cc';
import { ShopId } from './ShopTypes';
import { ShopCatalog } from './ShopCatalog';
import { ShopPanel } from './ShopPanel';
import { NpcCatalog } from './NpcCatalog';
import { DialoguePanel } from './DialoguePanel';

const { ccclass, property } = _decorator;

export enum HotspotKind {
  Shop = 0,
  Npc = 1,
}

Enum(HotspotKind);

/**
 * 城镇两侧可点击区域：铁匠铺/炼金铺 → 商店 UI；NPC → 对话/任务选项。
 */
@ccclass('TownHotspot')
export class TownHotspot extends Component {
  @property({ type: Enum(HotspotKind) })
  kind = HotspotKind.Shop;

  @property({ type: Enum(ShopId) })
  shopId = ShopId.Blacksmith;

  @property
  npcId = 'smith_npc';

  @property(ShopCatalog)
  shopCatalog: ShopCatalog | null = null;

  @property(NpcCatalog)
  npcCatalog: NpcCatalog | null = null;

  @property(ShopPanel)
  shopPanel: ShopPanel | null = null;

  @property(DialoguePanel)
  dialoguePanel: DialoguePanel | null = null;

  onLoad(): void {
    this.node.on(Node.EventType.TOUCH_END, this.onTap, this);
  }

  private onTap(_e: EventTouch): void {
    if (this.kind === HotspotKind.Shop) {
      const cat = this.shopCatalog ?? this.findShopCatalog();
      if (cat && this.shopPanel) this.shopPanel.open(cat);
      return;
    }

    const npc = this.npcCatalog?.find(this.npcId);
    if (npc && this.dialoguePanel) this.dialoguePanel.open(npc);
  }

  private findShopCatalog(): ShopCatalog | null {
    const catalogs = this.node.scene.getComponentsInChildren(ShopCatalog);
    return catalogs.find((c) => c.shopId === this.shopId) ?? null;
  }
}
