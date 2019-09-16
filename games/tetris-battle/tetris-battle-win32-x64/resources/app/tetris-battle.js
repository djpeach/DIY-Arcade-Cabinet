const Phaser = require('phaser');

var map1;
var map2;
var restarted = false;
var first = true;
var success;
var place;

var p1 = {
  id: 1,
  frameDelay: 0,
  map: map1,
  tetrominoValues: [0,0,1,1,2,2,3,3,4,4,5,5,6,6],
  currentTetromino: 0,
  activeTetromino: [],
  activeTetrominoX: 0,
  activeTetrominoY: 0,
  gameOver: false,
  gameSpeed: 60,
  speedLock: false,
  rotations: 0,
  tempTetromino: [],
  hold: [],
  holdText: "None",
  holdTetrominoVal: 0,
  currentTetrominoText: "",
  swapLock: false
}

var p2 = {
  id: 2,
  frameDelay: 0,
  map: map1,
  tetrominoValues: [0,0,1,1,2,2,3,3,4,4,5,5,6,6],
  currentTetromino: 0,
  activeTetromino: [],
  activeTetrominoX: 0,
  activeTetrominoY: 0,
  gameOver: false,
  gameSpeed: 60,
  speedLock: false,
  rotations: 0,
  tempTetromino: [],
  hold: [],
  holdText: "None",
  holdTetrominoVal: 0,
  currentTetrominoText: "",
  swapLock: false
}

var Tetris = new Phaser.Class({
  Extends: Phaser.Scene,

  initialize:

  function Tetris(){
    Phaser.Scene.call(this, { key: 'Tetris', active: true });
  },

  preload: function() {
    this.load.tilemapTiledJSON('map', 'assets/tilemaps/tetris-grid.json');
    this.load.image('tetris-tileset', 'assets/tilemaps/tetris-tilemapimage.png');

    //I did not create this sound. Success sound obtained from https://freesound.org/people/grunz/sounds/109663/. 
    //Original author is the user Grunz. Sound is available under the Creative Commons Attribution License.
    this.load.audio('clear-line', 'assets/109663__grunz__success-low.wav');
    //I did not create this sound. Pop sound obtained from https://freesound.org/people/kwahmah_02/sounds/260614/. 
    //Original author is the user kwahmah_02. Sound is available under the Creative Commons Attribution License.
    this.load.audio('place-block', 'assets/260614__kwahmah-02__pop.wav');
  },

  create: function(){
    map1 = this.add.tilemap('map');
    p1.map = map1;
    var tileset1 = map1.addTilesetImage('tetris-tileset');
    layer1 = map1.createDynamicLayer('Tile Layer 1', tileset1, 70, 25);

    this.p1hold = this.add.text(180, 700, "Hold: None", {fontSize: 24});

    map2 = this.add.tilemap('map');
    p2.map = map2;
    var tileset2 = map2.addTilesetImage('tetris-tileset');
    var layer2 = map2.createDynamicLayer('Tile Layer 1', tileset2, 530, 25);

    this.p2hold = this.add.text(650, 700, "Hold: None", {fontSize: 24});

    success = this.sound.add('clear-line');
    place = this.sound.add('place-block');

    //P1 Controls

    this.input.keyboard.on('keydown_A', function (event) {
      moveTetrominoLeft(p1);
    });
    this.input.keyboard.on('keydown_D', function (event) {
      moveTetrominoRight(p1);
    });
    this.input.keyboard.on('keydown_W', function (event) {
      rotateTetromino(p1);
    });
    this.input.keyboard.on('keydown_SPACE', function (event) {
      dropTetromino(p1);
    });
    this.input.keyboard.on('keydown_SHIFT', function(event){
      holdTetromino(p1);
    });

    this.input.keyboard.on('keydown_S', function (event) {
      if(!p1.speedLock){
        p1.gameSpeed = p1.gameSpeed / 5;
        p1.speedLock = true;
      }
    });
    this.input.keyboard.on('keyup_S', function (event) {
      p1.gameSpeed = p1.gameSpeed * 5;
      p1.speedLock = false;
    });

    //P2 Controls

    this.input.keyboard.on('keydown_LEFT', function (event) {
      moveTetrominoLeft(p2);
    });
    this.input.keyboard.on('keydown_RIGHT', function (event) {
      moveTetrominoRight(p2);
    });
    this.input.keyboard.on('keydown_UP', function (event) {
      rotateTetromino(p2);
    });
    this.input.keyboard.on('keydown_ENTER', function (event) {
      dropTetromino(p2);
    });
    this.input.keyboard.on('keydown_CTRL', function(event){
      holdTetromino(p2);
    });

    this.input.keyboard.on('keydown_DOWN', function (event) {
      if(!p2.speedLock){
        p2.gameSpeed = p2.gameSpeed / 5;
        p2.speedLock = true;
      }
    });
    this.input.keyboard.on('keyup_DOWN', function (event) {
      p2.gameSpeed = p2.gameSpeed * 5;
      p2.speedLock = false;
    });

    generateNewTetromino(p1);
    generateNewTetromino(p2);
  },

  update: function(){
    if(p1.gameOver){
      this.input.keyboard.removeAllListeners();
      this.input.keyboard.on('keydown_R', function(event){
        resetValues();
        restarted = true;
      });
      if(first){
        first = false;
        this.add.text(180, 290, "Loser", { fontFamily: 'Arial', fontSize: 48, color: '#ff0000' });
        this.add.text(660, 290, "Winner", { fontFamily: 'Arial', fontSize: 48, color: '#00ff00' });
        this.add.text(415, 700, "Press 'R' to play again", { fontFamily: 'Arial', fontSize: 16 });
      }
    }
    else if(p2.gameOver){
      this.input.keyboard.removeAllListeners();
      this.input.keyboard.on('keydown_R', function(event){
        resetValues();
        restarted = true;
      });
      if(first){
        first = false;
        this.add.text(180, 290, "Winner", { fontFamily: 'Arial', fontSize: 48, color: '#00ff00' });
        this.add.text(660, 290, "Loser", { fontFamily: 'Arial', fontSize: 48, color: '#ff0000' });
        this.add.text(415, 700, "Press 'R' to play again", { fontFamily: 'Arial', fontSize: 16 });
      }
    }
    else if(restarted){
      this.scene.restart();
      restarted = false;
    }
    else{
      p1.frameDelay++;
      if(p1.frameDelay >= p1.gameSpeed){
        updateActiveTetromino(p1);
        p1.frameDelay = 0;
      }
      this.p1hold.text = "Hold: " + p1.holdText;

      
      p2.frameDelay++;
      if(p2.frameDelay >= p2.gameSpeed){
        updateActiveTetromino(p2);
        p2.frameDelay = 0;
      }
      this.p2hold.text = "Hold: " + p2.holdText;
    }
  }
});

function resetValues(){
  p1 = {
    id: 1,
    frameDelay: 0,
    map: map1,
    tetrominoValues: [0,0,1,1,2,2,3,3,4,4,5,5,6,6],
    currentTetromino: 0,
    activeTetromino: [],
    activeTetrominoX: 0,
    activeTetrominoY: 0,
    gameOver: false,
    gameSpeed: 60,
    speedLock: false,
    rotations: 0,
    tempTetromino: [],
    hold: [],
    holdText: "None",
    holdTetrominoVal: 0,
    currentTetrominoText: "",
    swapLock: false
  }
  
  p2 = {
    id: 2,
    frameDelay: 0,
    map: map1,
    tetrominoValues: [0,0,1,1,2,2,3,3,4,4,5,5,6,6],
    currentTetromino: 0,
    activeTetromino: [],
    activeTetrominoX: 0,
    activeTetrominoY: 0,
    gameOver: false,
    gameSpeed: 60,
    speedLock: false,
    rotations: 0,
    tempTetromino: [],
    hold: [],
    holdText: "None",
    holdTetrominoVal: 0,
    currentTetrominoText: "",
    swapLock: false
  }

  first = true;
  restarted = false;
}

function holdTetromino(player){
  if(!player.swapLock){
    player.swapLock = true;
    if(player.hold.length === 0){
      player.hold = player.activeTetromino;
      player.holdText = player.currentTetrominoText;
      player.holdTetrominoVal = player.currentTetromino;
      clearActiveTetromino(player);
      generateNewTetromino(player);
    }
    else{
      clearActiveTetromino(player);

      //swap tetrominoes
      var temp = player.activeTetromino;
      player.activeTetromino = player.hold;
      player.hold = temp;

      //swap text values
      temp = player.holdText;
      player.holdText = player.currentTetrominoText;
      player.currentTetrominoText = temp;

      //swap current tetromino value
      temp = player.currentTetromino;
      player.currentTetromino = player.holdTetrominoVal;
      player.holdTetrominoVal = temp;

      player.activeTetrominoX = 4;
      player.activeTetrominoY = 0;
      renderTetromino(player);
    }
  }
}

function dropTetromino(player){
  clearActiveTetromino(player);
  while(nextTileIsValid(player)){
    player.activeTetrominoY++;
  }
  renderTetromino(player);
  place.play();
  clearLines(player);
  generateNewTetromino(player);
}

function getRandomTetromino(player){
  var rng = Math.floor(Math.random() * player.tetrominoValues.length)
  var newTetromino = player.tetrominoValues[rng];
  player.tetrominoValues.splice(rng, 1);
  if(player.tetrominoValues.length == 0){
    player.tetrominoValues = [0,0,1,1,2,2,3,3,4,4,5,5,6,6];
  }
  return newTetromino;
}

function generateNewTetromino(player){
  player.currentTetromino = getRandomTetromino(player);
  player.activeTetrominoX = 4;
  player.activeTetrominoY = 0;
  player.swapLock = false;

  switch(player.currentTetromino){
    case 0:
      // L
      player.activeTetromino = [
        [3, 1],
        [3, 1],
        [3, 3]
      ];
      player.currentTetrominoText = "L";
      break;
    case 1:
      // J
      player.activeTetromino = [
        [1, 7],
        [1, 7],
        [7, 7]
      ];
      player.currentTetrominoText = "J";
      break;
    case 2:
      // I
      player.activeTetromino = [
        [6],
        [6],
        [6],
        [6]
      ];
      player.currentTetrominoText = "I";
      break;
    case 3:
      // T
      player.activeTetromino = [
        [1, 8, 1],
        [8, 8, 8]
      ];
      player.currentTetrominoText = "T";
      break;
    case 4:
      // S
      player.activeTetromino = [
        [1, 5, 5],
        [5, 5, 1]
      ];
      player.currentTetrominoText = "S";
      break;
    case 5:
      // Z
      player.activeTetromino = [
        [2, 2, 1],
        [1, 2, 2]
      ];
      player.currentTetrominoText = "Z";
      break;
    case 6:
      // O
      player.activeTetromino = [
        [4, 4],
        [4, 4]
      ];
      player.currentTetrominoText = "O";
      break;
    default:
      break;
  }

  if(canSpawnNewBlock(player)){
    player.rotations = 0;
    renderTetromino(player);
  }
  else {
    player.gameOver = true;
  }
}

function renderTetromino(player){
  for(var i = 0; i < player.activeTetromino.length; i++){
    for(var j = 0; j < player.activeTetromino[i].length; j++){
      if(player.activeTetromino[i][j] != 1){
        player.map.putTileAt(player.activeTetromino[i][j], player.activeTetrominoX + j, player.activeTetrominoY + i);
      }
    }
  }
}

function moveTetrominoLeft(player){
  //check if block exists to the left of tetromino
  for(var i = 0; i < player.activeTetromino.length; i++){
    if(player.activeTetromino[i][0] != 1){
      if(player.map.getTileAt(player.activeTetrominoX - 1, player.activeTetrominoY + i, true) == null || player.map.getTileAt(player.activeTetrominoX - 1, player.activeTetrominoY + i).index != 1){
        return false;
      }
    }
  }

  //check if another block is extending into tetromino
  for(var i = 0; i < player.activeTetromino.length; i++){
    for(var j = 1; j < player.activeTetromino[i].length; j++){
      if(player.activeTetromino[i][j] != 1 && player.activeTetromino[i][j - 1] == 1){
        if(player.map.getTileAt(player.activeTetrominoX + j - 1, player.activeTetrominoY + i).index != 1){
          return false;
        }
      }
    }
  }

  clearActiveTetromino(player);
  player.activeTetrominoX--;
  renderTetromino(player);
}

function moveTetrominoRight(player){
  //check if block exists to the right of tetromino
  for(var i = 0; i < player.activeTetromino.length; i++){
    if(player.activeTetromino[i][player.activeTetromino[i].length - 1] != 1){
      if(player.map.getTileAt(player.activeTetrominoX + player.activeTetromino[i].length, player.activeTetrominoY + i, true) == null || player.map.getTileAt(player.activeTetrominoX + player.activeTetromino[i].length, player.activeTetrominoY + i).index != 1){
        return false;
      }
    }
  }

  //check if another block is extending into tetromino
  for(var i = 0; i < player.activeTetromino.length; i++){
    for(var j = 0; j < player.activeTetromino[i].length - 1; j++){
      if(player.activeTetromino[i][j] != 1 && player.activeTetromino[i][j + 1] == 1){
        if(player.map.getTileAt(player.activeTetrominoX + j + 1, player.activeTetrominoY + i).index != 1){
          return false;
        }
      }
    }
  }

  clearActiveTetromino(player);
  player.activeTetrominoX++;
  renderTetromino(player);
}

function clearActiveTetromino(player){
   for(var i = 0; i < player.activeTetromino.length; i++){
    for(var j = 0; j < player.activeTetromino[i].length; j++){
      if(player.activeTetromino[i][j] != 1){
        player.map.putTileAt(1, player.activeTetrominoX + j, player.activeTetrominoY + i);
      }
    }
  }
}

function canSpawnNewBlock(player){
  for(var i = 0; i < player.activeTetromino.length; i++){
    for(var j = 0; j < player.activeTetromino[i].length; j++){
      if(player.activeTetromino[i][j] != 1){
        if(player.map.getTileAt(player.activeTetrominoX + j, player.activeTetrominoY + i).index != 1){
          return false;
        }
      }
    }
  }
  return true;
}

function nextTileIsValid(player){
  if(player.activeTetrominoY + player.activeTetromino.length >= player.map.height)
    return false;

  //check if block exists below tetromino
  for(var i = 0; i < player.activeTetromino[player.activeTetromino.length - 1].length; i++){
    if(player.activeTetromino[player.activeTetromino.length - 1][i] != 1){
      if(player.map.getTileAt(player.activeTetrominoX + i, player.activeTetrominoY + player.activeTetromino.length).index != 1){
        return false;
      }
    }
  }

  //check if another block is extending into tetromino
  for(var i = 0; i < player.activeTetromino.length - 1; i++){
    for(var j = 0; j < player.activeTetromino[i].length; j++){
      if(player.activeTetromino[i][j] != 1 && player.activeTetromino[i + 1][j] == 1){
        if(player.map.getTileAt(player.activeTetrominoX + j, player.activeTetrominoY + i + 1).index != 1){
          return false;
        }
      }
    }
  }

  return true;
}

function updateActiveTetromino(player){
  if(nextTileIsValid(player)){
    clearActiveTetromino(player);
    player.activeTetrominoY++;
    renderTetromino(player);
  }
  else{
    place.play();
    clearLines(player);
    generateNewTetromino(player);
  }
}

function clearLines(player){
  var canClear = true;
  var dontAdd = false;
  for(var i = 0; i < player.activeTetromino.length; i++){
    for(var j = 0; j < player.map.width; j++){
      if(player.map.getTileAt(j, player.activeTetrominoY + i).index == 1){
        canClear = false;
      }
      if(player.map.getTileAt(j, player.activeTetrominoY + i).index == 9){
        dontAdd = true;
      }
    }
    if(canClear){
      success.play();
      for(var j = 0; j < player.map.width; j++){
        player.map.putTileAt(1, j, player.activeTetrominoY + i)
      }
      moveBlocksDown(i, player);
      if(!dontAdd){
        addNewLine(i, player);
      }
    }
    canClear = true;
    dontAdd = false;
  }
}

function addNewLine(index, player){
  var randomSpot = Math.floor(Math.random() * (map1.width - 1));
  if(player.id == 1){
    for(var i = 0; i < map2.height - 1; i++){
      for(var j = 0; j < map2.width; j++){
        map2.putTileAt(map2.getTileAt(j, i + 1), j, i);
      }
    }
    if(p2.activeTetrominoY > 0){
      p2.activeTetrominoY--;
    }
    for(var i = 0; i < map2.width; i++){
      if(i != randomSpot){
        map2.putTileAt(9, i, map2.height - 1);
      }
      else{
        map2.putTileAt(1, i, map2.height - 1);
      }
    }
  }
  else{
    for(var i = 0; i < map1.height - 1; i++){
      for(var j = 0; j < map1.width; j++){
        map1.putTileAt(map1.getTileAt(j, i + 1), j, i);
      }
    }
    if(p1.activeTetrominoY > 0){
      p1.activeTetrominoY--;
    }
    for(var i = 0; i < map1.width; i++){
      if(i != randomSpot){
        map1.putTileAt(9, i, map1.height - 1);
      }
      else{
        map1.putTileAt(1, i, map1.height - 1);
      }
    }
  }
}

function moveBlocksDown(index, player){
  for(var i = 0; i < player.activeTetrominoY + index; i++){
    for(var j = 0; j < player.map.width; j++){
      player.map.putTileAt(player.map.getTileAt(j, player.activeTetrominoY + index - 1 - i), j, player.activeTetrominoY + index - i)
    }
  }
}

var config = {
  type: Phaser.AUTO,
  width: 1000,
  height: 800,
  scene: [ Tetris ]
};

var game = new Phaser.Game(config);

function rotateTetromino(player){
  player.rotations++;
  player.rotations = player.rotations % 4;

  player.tempTetromino = [[]];

  switch(player.currentTetromino){
    case 0:
      // L
      if(player.rotations == 0){
        player.tempTetromino = [
          [3, 1],
          [3, 1],
          [3, 3]
        ];
      }
      else if(player.rotations == 1){
        player.tempTetromino = [
          [3, 3, 3],
          [3, 1, 1]
        ];
      }
      else if(player.rotations == 2){
        player.tempTetromino = [
          [3, 3],
          [1, 3],
          [1, 3]
        ];
      }
      else if(player.rotations == 3){
        player.tempTetromino = [
          [1, 1, 3],
          [3, 3, 3]
        ];
      }
      break;
    case 1:
      // J
      if(player.rotations == 0){
        player.tempTetromino = [
          [1, 7],
          [1, 7],
          [7, 7]
        ];
      }
      else if(player.rotations == 1){
        player.tempTetromino = [
          [7, 1, 1],
          [7, 7, 7]
        ];
      }
      else if(player.rotations == 2){
        player.tempTetromino = [
          [7, 7],
          [7, 1],
          [7, 1]
        ];
      }
      else if(player.rotations == 3){
        player.tempTetromino = [
          [7, 7, 7],
          [1, 1, 7]
        ];
      }
      break;
    case 2:
      // I
      if(player.rotations == 0 || player.rotations == 2){
        player.tempTetromino = [
          [6],
          [6],
          [6],
          [6]
        ];
      }
      else {
        player.tempTetromino = [
          [6, 6, 6, 6]
        ];
      }
      break;
    case 3:
      // T
      if(player.rotations == 0){
        player.tempTetromino = [
          [1, 8, 1],
          [8, 8, 8]
        ];
      }
      else if(player.rotations == 1){
        player.tempTetromino = [
          [8, 1],
          [8, 8],
          [8, 1]
        ];
      }
      else if(player.rotations == 2){
        player.tempTetromino = [
          [8, 8, 8],
          [1, 8, 1]
        ];
      }
      else if(player.rotations == 3){
        player.tempTetromino = [
          [1, 8],
          [8, 8],
          [1, 8]
        ];
      }
      break;
    case 4:
      // S
      if(player.rotations == 0 || player.rotations == 2){
        player.tempTetromino = [
          [1, 5, 5],
          [5, 5, 1]
        ];
      }
      else if(player.rotations == 1 || player.rotations == 3){
        player.tempTetromino = [
          [5, 1],
          [5, 5],
          [1, 5]
        ];
      }
      break;
    case 5:
      // Z
      if(player.rotations == 0 || player.rotations == 2){
        player.tempTetromino = [
          [2, 2, 1],
          [1, 2, 2]
        ];
      }
      else if(player.rotations == 1 || player.rotations == 3){
        player.tempTetromino = [
          [1, 2],
          [2, 2],
          [2, 1]
        ];
      }
      break;
    case 6:
      // O
      player.tempTetromino = [
        [4, 4],
        [4, 4]
      ]
      break;
    default:
      break;
  }
  clearActiveTetromino(player);
  if(checkTempTetromino(player)){
    player.activeTetromino = player.tempTetromino;
  }else
  {
    player.rotations--;
  }
  renderTetromino(player);
}

function checkTempTetromino(player){
  for(var i = 0; i < player.tempTetromino.length; i++){
    for(var j = 0; j < player.tempTetromino[i].length; j++){
      if(player.tempTetromino[i][j] != 1){
        if(player.map.getTileAt(player.activeTetrominoX + j, player.activeTetrominoY + i, true) == null || player.map.getTileAt(player.activeTetrominoX + j, player.activeTetrominoY + i).index != 1){
          return false;
        }
      }
    }
  }
  return true;
}