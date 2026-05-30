import { _decorator, CCString, CCInteger, Enum } from 'cc';

const { ccclass, property } = _decorator;

export enum ShopId {
  Blacksmith = 0,
  Alchemy = 1,
}

Enum(ShopId);

/** 策划可挂在 ShopCatalog 组件上逐条填 */
@ccclass('ShopItemRow')
export class ShopItemRow {
  @property({ type: CCString })
  itemId = '';

  @property({ type: CCString })
  displayName = '';

  @property({ type: CCInteger })
  price = 10;

  @property({ type: CCInteger })
  stock = -1;
}
