import { _decorator, CCString } from 'cc';

const { ccclass, property } = _decorator;

/** 对话选项（任务/闲聊） */
@ccclass('DialogueOptionRow')
export class DialogueOptionRow {
  @property({ type: CCString })
  optionId = '';

  @property({ type: CCString })
  label = '你好';

  @property({ type: CCString, tooltip: 'quest_accept / chat / close' })
  actionType = 'chat';
}

export class NpcDialogueSet {
  @property({ type: CCString })
  npcId = '';

  @property({ type: CCString })
  displayName = 'NPC';

  @property({ type: CCString })
  greeting = '旅人，需要什么？';

  @property({ type: [DialogueOptionRow] })
  options: DialogueOptionRow[] = [];
}
