import {
  _decorator,
  Component,
  SpriteFrame,
  CCString,
  CCBoolean,
  resources,
} from 'cc';
import { MonsterConfigData } from './CombatTypes';
import { MonsterConfigById, Model01PartyCat } from '../data/DefaultMonsters';

const { ccclass, property } = _decorator;

export interface MonsterSpawnPick {
  modelId: string;
  config: MonsterConfigData;
  spriteFrame: SpriteFrame | null;
}

@ccclass('MonsterModelEntry')
export class MonsterModelEntry {
  @property({ type: CCString })
  modelId = 'model_01';

  @property({ type: CCString })
  displayName = '派对猫';

  @property(SpriteFrame)
  spriteFrame: SpriteFrame | null = null;

  @property({ type: CCString, tooltip: 'resources 路径，如 monsters/model_01/spriteFrame' })
  resourcePath = 'monsters/model_01/spriteFrame';

  @property({ type: CCString, tooltip: '对应 DefaultMonsters 中的 id' })
  configId = 'model_01';

  @property({ type: CCBoolean })
  enabledInRandomPool = true;
}

/**
 * 随机怪物模型表：策划在编辑器追加条目并拖 SpriteFrame。
 */
@ccclass('MonsterModelRegistry')
export class MonsterModelRegistry extends Component {
  @property({ type: [MonsterModelEntry] })
  models: MonsterModelEntry[] = [];

  private cache = new Map<string, SpriteFrame>();

  onLoad(): void {
    if (!this.models.length) {
      this.models = [this.createDefaultModel01Entry()];
    }
    this.preloadResources();
  }

  pickRandom(): MonsterSpawnPick {
    const pool = this.models.filter((m) => m.enabledInRandomPool);
    const list = pool.length ? pool : this.models;
    const entry = list[Math.floor(Math.random() * list.length)];
    return this.resolve(entry);
  }

  pickById(modelId: string): MonsterSpawnPick | null {
    const entry = this.models.find((m) => m.modelId === modelId);
    return entry ? this.resolve(entry) : null;
  }

  private resolve(entry: MonsterModelEntry): MonsterSpawnPick {
    const config =
      MonsterConfigById[entry.configId] ??
      MonsterConfigById[entry.modelId] ??
      Model01PartyCat;
    const sf =
      entry.spriteFrame ??
      this.cache.get(entry.resourcePath) ??
      this.cache.get(entry.modelId) ??
      null;
    return {
      modelId: entry.modelId,
      config: { ...config, displayName: entry.displayName || config.displayName },
      spriteFrame: sf,
    };
  }

  private preloadResources(): void {
    for (const m of this.models) {
      if (m.spriteFrame || !m.resourcePath) continue;
      resources.load(m.resourcePath, SpriteFrame, (err, sf) => {
        if (!err && sf) {
          this.cache.set(m.resourcePath, sf);
          this.cache.set(m.modelId, sf);
        }
      });
    }
  }

  private createDefaultModel01Entry(): MonsterModelEntry {
    const e = new MonsterModelEntry();
    e.modelId = 'model_01';
    e.displayName = '派对猫';
    e.configId = 'model_01';
    e.resourcePath = 'monsters/model_01/spriteFrame';
    e.enabledInRandomPool = true;
    return e;
  }
}
