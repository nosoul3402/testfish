import Phaser from 'phaser';
import { GameScene } from './scenes/GameScene';

const GAME_WIDTH = 390;
const GAME_HEIGHT = 844;

new Phaser.Game({
  type: Phaser.AUTO,
  parent: 'game',
  width: GAME_WIDTH,
  height: GAME_HEIGHT,
  backgroundColor: '#121218',
  scale: {
    mode: Phaser.Scale.FIT,
    autoCenter: Phaser.Scale.CENTER_BOTH,
  },
  scene: [GameScene],
});
