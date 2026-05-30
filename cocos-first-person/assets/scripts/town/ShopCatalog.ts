import { _decorator, Component, CCString, Enum } from 'cc';
import { ShopId, ShopItemRow } from './ShopTypes';

const { ccclass, property } = _decorator;

/** 铁匠铺 / 炼金铺 商品表（编辑器里编辑） */
@ccclass('ShopCatalog')
export class ShopCatalog extends Component {
  @property({ type: Enum(ShopId) })
  shopId = ShopId.Blacksmith;

  @property({ type: CCString })
  shopTitle = '铁匠铺';

  @property({ type: [ShopItemRow] })
  items: ShopItemRow[] = [];
}
