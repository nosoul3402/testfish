import { _decorator, Component, Node, Label, Button, Prefab, instantiate } from 'cc';
import { ShopCatalog } from './ShopCatalog';
import { ShopItemRow } from './ShopTypes';

const { ccclass, property } = _decorator;

/** 商店 UI：购买逻辑占位，接金币系统后扩展 */
@ccclass('ShopPanel')
export class ShopPanel extends Component {
  @property(Node)
  panelRoot: Node | null = null;

  @property(Label)
  titleLabel: Label | null = null;

  @property(Node)
  itemListRoot: Node | null = null;

  @property(Prefab)
  itemRowPrefab: Prefab | null = null;

  @property(Label)
  goldLabel: Label | null = null;

  private catalog: ShopCatalog | null = null;
  private gold = 300;

  onLoad(): void {
    this.hide();
  }

  open(catalog: ShopCatalog): void {
    this.catalog = catalog;
    const root = this.panelRoot ?? this.node;
    root.active = true;
    if (this.titleLabel) this.titleLabel.string = catalog.shopTitle;
    this.refreshGold();
    this.buildList();
  }

  hide(): void {
    const root = this.panelRoot ?? this.node;
    root.active = false;
  }

  private refreshGold(): void {
    if (this.goldLabel) this.goldLabel.string = `金币 ${this.gold}`;
  }

  private buildList(): void {
    const list = this.itemListRoot;
    if (!list || !this.catalog) return;
    list.removeAllChildren();

    for (const row of this.catalog.items) {
      if (this.itemRowPrefab) {
        const n = instantiate(this.itemRowPrefab);
        list.addChild(n);
        const label = n.getComponentInChildren(Label);
        if (label) label.string = `${row.displayName}  ${row.price}G`;
        const btn = n.getComponent(Button);
        btn?.node.on(Button.EventType.CLICK, () => this.buy(row), this);
      } else {
        const n = new Node(row.itemId);
        list.addChild(n);
      }
    }
  }

  private buy(row: ShopItemRow): void {
    if (this.gold < row.price) return;
    this.gold -= row.price;
    this.refreshGold();
    this.node.emit('shop-item-bought', { itemId: row.itemId, price: row.price });
  }
}
