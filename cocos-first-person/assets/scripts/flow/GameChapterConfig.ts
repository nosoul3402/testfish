import { _decorator, Component, SpriteFrame, CCString, CCInteger, CCBoolean } from 'cc';

const { ccclass, property } = _decorator;

/**
 * 策划在 Creator 编辑器里直接改的本关配置（常规数据驱动入口）。
 * 可复制组件 Preset 做 chapter02、chapter03…
 */
@ccclass('GameChapterConfig')
export class GameChapterConfig extends Component {
  @property({ type: CCString, tooltip: '关卡 ID，日志/存档用' })
  chapterId = 'forest_01';

  // —— 隧道 ——
  @property({ type: [SpriteFrame], tooltip: '森林隧道循环帧；尽头前循环播放' })
  tunnelLoopFrames: SpriteFrame[] = [];

  @property({ type: SpriteFrame, tooltip: '达标后替换「最深处」的画面：城镇大门' })
  gateFrame: SpriteFrame | null = null;

  @property({ type: CCInteger, tooltip: '累计前进步数 ≥ 此值 → 显示大门' })
  stepsToRevealGate = 12;

  @property({ type: CCInteger, tooltip: '累计击败怪物 ≥ 此值 → 显示大门（与步数满足任一即可）' })
  killsToRevealGate = 5;

  @property({ type: CCBoolean, tooltip: 'true=步数 AND 击杀都要满足；false=满足任一' })
  requireBothForGate = false;

  @property({ type: CCInteger, tooltip: '显示大门后，再前进几次可点门（0=立刻可点）' })
  stepsAfterGateToEnter = 1;

  @property({ type: CCString, tooltip: '进入城镇的场景名（Build Settings）' })
  townSceneName = 'Town';

  // —— 遭遇 ——
  @property({ type: CCInteger })
  stepsPerEncounter = 3;

  @property({ type: CCBoolean, tooltip: '大门出现后是否停止刷怪' })
  stopEncountersAfterGate = true;
}
