import "phaser";
import makeAnimations from "./animations.js";
import {
  COMBAT_MAP,
  IGNORE_MAP_COLLISION,
  SHOW_DEBUG,
  SLIME_SPEED,
  SLIME_START_COLOR,
  TINT_MAP
} from "./constants.js";

const config = {
  type: Phaser.AUTO,
  width: 534,
  height: 300,
  pixelArt: true,
  parent: "game",
  canvasStyle: "zoom: 100%;",
  scene: {
    preload: preload,
    create: create,
    update: update
  },
  physics: {
    default: "arcade",
    arcade: {
      gravity: { y: 0 } //Top down game, no gravity
    }
  }
};

let gameStarted = false;

function startGame(scene){
  scene.game.scene.start("default");
}

function endGame(scene) {
  document.getElementById("gameOverScreen").style.display = "block";
  scene.game.scene.pause("default");
}

const game = new Phaser.Game(config);
let cursors;

// Runs once, loads up assets like images and audio
function preload() {
  this.load.audio("background_music", ["assets/audio/slimemusic.mp3", "assets/audio/slimemusic.wav", "assets/audio/slimemusic.ogg"]);
  this.load.audio("door_open", "assets/audio/door-open.wav");
  this.load.audio("s_knight_red", "assets/audio/knight-red.wav");
  this.load.audio("s_slime_attack", "assets/audio/slime-attack.wav");
  this.load.audio("slime_pickup", "assets/audio/slime-pickup.wav");
  this.load.audio("slime_cycle", "assets/audio/slime-cycle.wav");
  this.load.audio("water_drop", "assets/audio/water-drop.wav");
  this.load.audio("s_wizard_green", "assets/audio/wizard-green.wav");
  this.load.audio("s_wizard_red", "assets/audio/wizard-red.wav");
  this.load.image("dungeon-tiles", "assets/tilesets/dungeon_tiles.png");
  this.load.tilemapTiledJSON("map", "assets/tilemaps/level1.json");
  this.load.spritesheet("slime", "assets/spritesheets/slime.png", {
    frameWidth: 16,
    frameHeight: 16,
    endFrame: 15
  });
  this.load.spritesheet("wizard-blue", "assets/spritesheets/wizard-blue.png", {
    frameWidth: 21,
    frameHeight: 24,
    endFrame: 3
  });
  this.load.spritesheet("wizard-red", "assets/spritesheets/wizard-red.png", {
    frameWidth: 27,
    frameHeight: 23,
    endFrame: 3
  });
  this.load.spritesheet(
    "wizard-green",
    "assets/spritesheets/wizard-green.png",
    {
      frameWidth: 21,
      frameHeight: 24,
      endFrame: 3
    }
  );
  this.load.spritesheet("knight-red", "assets/spritesheets/knight-red.png", {
    frameWidth: 26,
    frameHeight: 22,
    endFrame: 3
  });
  this.load.spritesheet(
    "knight-silver",
    "assets/spritesheets/knight-silver.png",
    {
      frameWidth: 16,
      frameHeight: 23,
      endFrame: 3
    }
  );
}

function addLayerCollision(scene, body) {
  scene.collisionLayers.forEach(layer => {
    scene.physics.add.collider(body, layer);
  });
  scene.physics.add.collider(body, scene.wizards, wizardColliderCallback);
  scene.physics.add.collider(body, scene.knights, knightColliderCallback);
}

function addSlime(scene, slimeColor = "yellow", x = -25, y = -25) {
  let slime = scene.physics.add.sprite(x, y, "slime");

  slime.setTint(TINT_MAP[slimeColor]);
  slime.color = slimeColor;
  slime.combat = Object.assign({}, COMBAT_MAP.slime[slimeColor]);
  scene.followingSlimes.add(slime);
}

function removeSlime(scene) {
  const followingSlimes = scene.followingSlimes.children.entries;

  const numSlimes = followingSlimes.length;
  if (numSlimes === 0) {
    endGame(scene);
    return;
  }

  scene.movingSlime.body.setVelocity(0);
  scene.movingSlime.depth -= 20;
  scene.movingSlime.play("slime_dead");

  followingSlimes[0].combat.lastAttack = scene.movingSlime.combat.lastAttack;
  scene.movingSlime = followingSlimes[0];

  // Remove old collisions
  scene.physics.world.colliders.destroy();

  // Add new collisions
  addLayerCollision(scene, scene.movingSlime);

  scene.cameras.main.startFollow(scene.movingSlime);

  for (let i = 0; i < numSlimes; i++) {
    if (i + 1 === numSlimes) {
      // Remove last slime
      followingSlimes.splice(-1, 1);
    } else {
      followingSlimes[i] = followingSlimes[i + 1];
    }
  }
}

function deRotateSlimes() {
  const scene = this;
  const followingSlimes = scene.followingSlimes.children.entries;
  const numSlimes = followingSlimes.length;
  if (numSlimes < 1) {
    console.error("Not enough slimes to rotate!");
    return;
  }

  s_slimeCycle.play();
  const tempSlime = scene.movingSlime;

  scene.movingSlime = followingSlimes.pop();
  scene.movingSlime.combat.lastAttack = tempSlime.combat.lastAttack;
  followingSlimes.unshift(tempSlime);

  // Remove old collisions
  scene.physics.world.colliders.destroy();

  // Add new collisions
  addLayerCollision(scene, scene.movingSlime);



  scene.cameras.main.startFollow(scene.movingSlime);
}

function rotateSlimes() {
  const scene = this;
  const followingSlimes = scene.followingSlimes.children.entries;
  const numSlimes = followingSlimes.length;
  if (numSlimes < 1) {
    console.error("Not enough slimes to rotate!");
    return;
  }

  s_slimeCycle.play();
  const tempSlime = scene.movingSlime;

  scene.movingSlime = followingSlimes.shift();
  scene.movingSlime.combat.lastAttack = tempSlime.combat.lastAttack;
  followingSlimes.push(tempSlime);

  // Remove old collisions
  scene.physics.world.colliders.destroy();

  // Add new collisions
  addLayerCollision(scene, scene.movingSlime);

  scene.cameras.main.startFollow(scene.movingSlime);
}

function staticSlimeCollision(movingSlime, staticSlime) {
  staticSlime.disableBody(true, true);
  addSlime(movingSlime.scene, staticSlime.color);
  var slimePickup = this.sound.add('slime_pickup');
  slimePickup.loop = false;
  slimePickup.play();
  return false;
}

function determineCombat(
  sceneRef,
  obj1,
  obj1DeathCallback,
  obj1AttackAnim,
  obj2,
  obj2DeathCallback,
  obj2AttackAnim,
) {
  var ret = [];
  const currentTime = Date.now();
  if (
    cursors.space.isDown &&
    (!obj1.combat.lastAttack ||
      obj1.combat.lastAttack + obj1.combat.attackPeriod < currentTime)
  ) {
    ret['obj1'] = true;
    if (obj1AttackAnim) {
      obj1.anims.play(obj1AttackAnim);
    }

    // Check for modified damage
		let damage = obj1.combat.attack;
		if (obj2.texture.key.split("-")[0] === "wizard" && obj1.color === "green") {
			// Green slimes deal 150% damage against wizards
			damage = damage * 1.5;
		} else if (obj2.texture.key.split("-")[0] === "knight" && obj1.color === "purple") {
			// Purple slimes deal 150% damage against knights
			damage = damage * 1.5;
		}

    if (SHOW_DEBUG) {
      console.log(
        obj1.texture.key +
          " attacks " +
          obj2.texture.key +
          " for " +
          damage +
          " damage!"
      );
      console.log("Old HP: " + obj2.combat.current);
      obj2.combat.current = Math.max(
        0,
        obj2.combat.current - damage
      );
      console.log("New HP: " + obj2.combat.current);
    } else {
      obj2.combat.current = Math.max(
        0,
        obj2.combat.current - damage
      );
    }

    obj1.combat.lastAttack = currentTime;
  }
  if (
    cursors.space.isDown &&
    (!obj2.combat.lastAttack ||
      obj2.combat.lastAttack + obj2.combat.attackPeriod < currentTime)
  ) {
    ret['obj2'] = true;
    if (obj2AttackAnim) {
      obj2.anims.stop();
      obj2.anims.play(obj2AttackAnim);
    }

		let damage = obj2.combat.attack;
    if (SHOW_DEBUG) {
      console.log(
        obj2.texture.key +
          " attacks " +
          obj1.texture.key +
          " for " +
          damage +
          " damage!"
      );
      console.log("Old HP: " + obj1.combat.current);
      let damage = obj2.combat.attack;
      obj1.combat.current = Math.max(
        0,
        obj1.combat.current - damage
      );
      console.log("New HP: " + obj1.combat.current);
    } else {
      obj1.combat.current = Math.max(
        0,
        obj1.combat.current - damage
      );
    }
    obj2.combat.lastAttack = currentTime;
  }

  if (obj1.combat.current < 1) {
    if (obj1DeathCallback) {
      obj1DeathCallback(sceneRef, obj1, obj2);
    } else {
      obj1.disableBody(true, true);
    }
  }

  if (obj2.combat.current < 1) {
    if (obj2.healthBar) {
      obj2.healthBar.setVisible(false);
    }
    if (obj2DeathCallback) {
      obj2DeathCallback(sceneRef, obj1, obj2);
    } else {
      obj2.disableBody(true, true);
    }
  }
  return ret;
}

function wizardColliderCallback(movingSlime, wizard) {
  let obj = determineCombat(
    movingSlime.scene,
    movingSlime,
    removeSlime,
    undefined,
    wizard,
    undefined,
    `wizard_${wizard.color}_attack`,
  );
  if(obj['obj1']) {
    s_slimeAttack.play();
  }
  if(obj['obj2']) {
    if(wizard.color === 'red') {
      setTimeout(function(){ 
        s_wizardRedAttack.play(); 
      }, 50);
      
    }
    if(wizard.color === 'green') {
      setTimeout(function(){ 
        s_wizardGreenAttack.play();
      }, 50);
      
    }
  }
}

function knightColliderCallback(movingSlime, knight) {
  let obj = determineCombat(
    movingSlime.scene,
    movingSlime,
    removeSlime,
    undefined,
    knight,
    undefined,
    `knight_${knight.color}_attack`,
  );
  if(obj['obj1']) {
    s_slimeAttack.play();
  }
  if(obj['obj2']) {
    setTimeout(function(){ 
      s_knightRedAttack.play();
    }, 50);
  }
}
//global sound variables
var s_slimeAttack, s_wizardRedAttack, s_wizardGreenAttack, s_knightRedAttack, s_slimeCycle;

// Runs once, after all assets in preload are loaded
function create() {
  s_slimeCycle = this.sound.add('slime_cycle');
  s_slimeCycle.loop = false;
  s_slimeAttack = this.sound.add('s_slime_attack');
  s_slimeAttack.loop = false;
  s_wizardRedAttack = this.sound.add('s_wizard_red');
  s_wizardRedAttack.loop = false;
  s_wizardGreenAttack = this.sound.add('s_wizard_green');
  s_wizardGreenAttack.loop = false;
  s_knightRedAttack = this.sound.add('s_knight_red');
  s_knightRedAttack.loop = false;

  makeAnimations(this);
  const map = this.make.tilemap({ key: "map" });
  const spawnPoint = map.findObject("points", obj => obj.name === "spawnpoint");

  const knightSpawns = map.filterObjects("points", obj =>
    obj.name.startsWith("knight-")
  );
  this.knights = this.physics.add.group();

  knightSpawns.forEach(knightSpawn => {
    // Split the name so we can get the color. name should look like: "knight-COLOR-ID" or "knight-COLOR" if unique
    const KEY_PARTS = knightSpawn.name.split("-");
    if (KEY_PARTS.length < 2) {
      console.log("Error creating knight from spawn: " + knightSpawn.name);
      console.log(knightSpawn);
    }

    const knightColor = KEY_PARTS[1];
    let tempKnight = this.physics.add.sprite(
      knightSpawn.x,
      knightSpawn.y,
      "knight-" + knightColor
    );

    tempKnight.body.immovable = true;
    tempKnight.body.moves = false;

    tempKnight.combat = Object.assign({}, COMBAT_MAP.knight[knightColor]);
    tempKnight.color = knightColor;

    tempKnight.healthBar = this.add.graphics(knightSpawn.x, knightSpawn.y);

    tempKnight.anims.play(`knight_${knightColor}_idle`, true);
    this.knights.add(tempKnight);
  });

  const wizardSpawns = map.filterObjects("points", obj =>
    obj.name.startsWith("wizard-")
  );
  this.wizards = this.physics.add.group();

  wizardSpawns.forEach(wizardSpawn => {
    // Split the name so we can get the color. name should look like: "wizard-COLOR-ID" or "wizard-COLOR" if unique
    const KEY_PARTS = wizardSpawn.name.split("-");
    if (KEY_PARTS.length < 2) {
      console.log("Error creating wizard from spawn: " + wizardSpawn.name);
      console.log(wizardSpawn);
    }

    const wizardColor = KEY_PARTS[1];
    let tempWiz = this.physics.add.sprite(
      wizardSpawn.x,
      wizardSpawn.y,
      "wizard-" + wizardColor
    );

    tempWiz.body.immovable = true;
    tempWiz.body.moves = false;

    tempWiz.color = wizardColor;
    tempWiz.combat = Object.assign({}, COMBAT_MAP.wizard[wizardColor]);
    tempWiz.anims.play(`wizard_${wizardColor}_idle`, true);

    tempWiz.healthBar = this.add.graphics(wizardSpawn.x, wizardSpawn.y);

    this.wizards.add(tempWiz);
  });

  this.slimeCollideWaterLayer1 = true;
  this.slimeCollideWaterLayer2 = true;
  this.slimeCollideDoorLayer = true;

  // We're going to assume anything starting with "slime-..." is a spawn for a slime. determine color later
  const staticSlimes = map.filterObjects("points", obj =>
    obj.name.startsWith("slime-")
  );
  this.staticSlimes = this.physics.add.group();

  staticSlimes.forEach(staticSlime => {
    // Split the name so we can get the color. name should look like: "slime-COLOR-ID" or "slime-COLOR" if unique
    const KEY_PARTS = staticSlime.name.split("-");
    if (KEY_PARTS.length < 2) {
      console.log("Error creating slime from spawn: " + staticSlime.name);
      console.log(staticSlime);
    }
    let tempSlime = this.physics.add.sprite(
      staticSlime.x,
      staticSlime.y,
      "slime"
    );
    //console.log(KEY_PARTS[1], TINT_MAP[KEY_PARTS[1]]);
    tempSlime.setTint(TINT_MAP[KEY_PARTS[1]]);
    tempSlime.color = KEY_PARTS[1];
    tempSlime.combat = Object.assign({}, COMBAT_MAP.slime[KEY_PARTS[1]]);
    tempSlime.anims.play("slime_walk_down", true);
    this.staticSlimes.add(tempSlime);
  });

  // Parameters are the name you gave the tileset in Tiled and then the key of the tileset image in
  // Phaser's cache (i.e. the name you used in preload)
  const tileset = map.addTilesetImage("dungeonv4", "dungeon-tiles");

  // Parameters: layer name (or index) from Tiled, tileset, x, y
  this.groundLayer = map.createStaticLayer("ground", tileset, 0, 0);
  this.wallLayer = map.createStaticLayer("wall", tileset, 0, 0);
  this.waterLayer1 = map.createDynamicLayer("water1", tileset, 0, 0);
  this.waterLayer2 = map.createStaticLayer("water2", tileset, 0, 0);
  this.doorLayer = map.createStaticLayer("door", tileset, 0, 0);
  this.objectsLayer = map.createStaticLayer("objects", tileset, 0, 0);

  this.collisionLayers = [
    this.wallLayer,
    this.waterLayer1,
    this.waterLayer2,
    this.doorLayer,
    this.objectsLayer
  ];

  this.followingSlimes = this.physics.add.group();
  this.movingSlime = this.physics.add.sprite(
    spawnPoint.x,
    spawnPoint.y,
    "slime"
  );

  // Enable collision for each tile layer
  this.wallLayer.setCollisionByProperty({
    collide: true && !IGNORE_MAP_COLLISION
  });
  this.waterLayer1.setCollisionByProperty(
    { collide: true },
    isColorMatch(this.movingSlime, "blue")
  );
  this.waterLayer2.setCollisionByProperty({
    collide: true && !IGNORE_MAP_COLLISION
  });
  this.doorLayer.setCollisionByProperty({
    collide: true && !IGNORE_MAP_COLLISION
  });
  this.objectsLayer.setCollisionByProperty({
    collide: true && !IGNORE_MAP_COLLISION
  });

  this.slimePosIndexOffset = 0;
  this.slimePos = [];
  for (var i = 0; i < 1000; i++) {
    this.slimePos[i] = -50;
  }
  this.movingSlime.color = SLIME_START_COLOR;
  this.movingSlime.setTint(TINT_MAP[SLIME_START_COLOR]);
  this.movingSlime.combat = Object.assign({}, COMBAT_MAP.slime.green);

  addLayerCollision(this, this.movingSlime);

  if (SHOW_DEBUG) {
    const debugGraphics = this.add.graphics().setAlpha(0.75);
    this.doorLayer.renderDebug(debugGraphics, {
      tileColor: null, // Color of non-colliding tiles
      collidingTileColor: new Phaser.Display.Color(255, 255, 255, 255), // Color of colliding tiles
      faceColor: new Phaser.Display.Color(40, 39, 37, 255) // Color of colliding face edges
    });
    this.wallLayer.renderDebug(debugGraphics, {
      tileColor: null, // Color of non-colliding tiles
      collidingTileColor: new Phaser.Display.Color(255, 0, 0, 255), // Color of colliding tiles
      faceColor: new Phaser.Display.Color(40, 39, 37, 255) // Color of colliding face edges
    });
    this.waterLayer1.renderDebug(debugGraphics, {
      tileColor: null, // Color of non-colliding tiles
      collidingTileColor: new Phaser.Display.Color(0, 255, 0, 255), // Color of colliding tiles
      faceColor: new Phaser.Display.Color(40, 39, 37, 255) // Color of colliding face edges
    });
    this.waterLayer2.renderDebug(debugGraphics, {
      tileColor: null, // Color of non-colliding tiles
      collidingTileColor: new Phaser.Display.Color(0, 255, 255, 255), // Color of colliding tiles
      faceColor: new Phaser.Display.Color(40, 39, 37, 255) // Color of colliding face edges
    });
    this.objectsLayer.renderDebug(debugGraphics, {
      tileColor: null, // Color of non-colliding tiles
      collidingTileColor: new Phaser.Display.Color(0, 0, 255, 255), // Color of colliding tiles
      faceColor: new Phaser.Display.Color(40, 39, 37, 255) // Color of colliding face edges
    });
  }

  // Phaser supports multiple cameras, but you can access the default camera like this:
  const camera = this.cameras.main;

  // Set up the arrows to control the camera
  cursors = this.input.keyboard.addKeys({
    up: Phaser.Input.Keyboard.KeyCodes.W,
    down: Phaser.Input.Keyboard.KeyCodes.S,
    left: Phaser.Input.Keyboard.KeyCodes.A,
    right: Phaser.Input.Keyboard.KeyCodes.D,
    space: Phaser.Input.Keyboard.KeyCodes.R
  });

  this.input.keyboard.on("keydown_Y", deRotateSlimes, this);
  this.input.keyboard.on("keydown_O", rotateSlimes, this);

  // Constrain the camera so that it isn't allowed to move outside the width/height of tilemap
  camera.startFollow(this.movingSlime);
  camera.setBounds(0, 0, map.widthInPixels, map.heightInPixels);

  this.waterLayer1.setTileIndexCallback(
    [
      4490,
      4491,
      4492,
      4493,
      4582,
      4583,
      4584,
      4585,
      4674,
      4675,
      4676,
      4677,
      4766,
      4767,
      4768,
      4769
    ],
    () => {
      if (isColorMatch(this.movingSlime, "blue")) {
        if (cursors.space.isDown) {
          if (this.slimeCollideWaterLayer1) {
            var waterDrop = this.sound.add('water_drop');
            waterDrop.loop = false;
            waterDrop.play();
            this.movingSlime.y = this.movingSlime.y + 15;
            removeSlime(this);
            this.slimeCollideWaterLayer1 = false;
          }
        }
      }
    },
    this
  );

  this.waterLayer2.setTileIndexCallback(
    [
      3754,
      3755,
      3756,
      3757,
      3846,
      3847,
      3848,
      3849,
      3938,
      3939,
      3940,
      3941,
      4030,
      4031,
      4032,
      4033,
      4122,
      4123,
      4124,
      4125,
      4214,
      4215,
      4216,
      4217,
      4306,
      4307,
      4308,
      4309
    ],
    () => {
      if (isColorMatch(this.movingSlime, "blue")) {
        if (cursors.space.isDown) {
          if (this.slimeCollideWaterLayer2) {
            var waterDrop = this.sound.add('water_drop');
            waterDrop.loop = false;
            waterDrop.play();
            this.movingSlime.x = this.movingSlime.x + 15;
            removeSlime(this);
            this.slimeCollideWaterLayer2 = false;
          }
        }
      }
    },
    this
  );

  this.doorLayer.setTileIndexCallback(
    [
      5191,
      5192,
      5193,
      5194,
      5099,
      5100,
      5101,
      5102,
      5007,
      5008,
      5009,
      5010,
      4915,
      4916,
      4917,
      4918
    ],
    () => {
      if (isColorMatch(this.movingSlime, "red")) {
        if (cursors.space.isDown) {
          if (this.slimeCollideDoorLayer) {
            var doorOpen = this.sound.add('door_open');
            doorOpen.loop = false;
            doorOpen.play();
            this.slimeCollideDoorLayer = false;
            document.getElementById("gameWinScreen").style.display = "block";
          }
        }
      }
    },
    this
  );

  //Game start screen behavior
  this.input.keyboard.on("keydown_U", function(event) {
      if (!gameStarted){
        document.getElementById("startScreen").style.display = "none";
        gameStarted = true;
        var backgroundMusic = this.sound.add('background_music', { volume: 0.3 });
        backgroundMusic.loop = true;
        backgroundMusic.play();
      }
  }.bind(this));

  //Restart on 'r' key
  this.input.keyboard.on("keydown_P", ()=>{
    location = window.location;
    gameStarted = false;
  })
}

function isColorMatch(movingSlime, color) {
  return movingSlime.color == color;
}

function updateStatuses(mainSlime, followingSlimes) {
  var html = "<div id='status-text'>Slime Status:</div><div id='statuses'>";
  if (mainSlime && mainSlime.color && mainSlime.combat.current) {
    let mainSlimeHealthPercent = parseInt(
      (mainSlime.combat.current / mainSlime.combat.max) * 100
    );
    let progressBarColor = "success";
    if (mainSlimeHealthPercent <= 66) {
      progressBarColor = "warning";
    } else if (mainSlimeHealthPercent <= 33) {
      progressBarColor = "danger";
    }
    html +=
      "<div class='sprite-info main'>" +
      "<img class='slime-img' src='assets/ui/slime-" +
      mainSlime.color +
      ".png' />" +
      "<div class='progress'><div class='progress-bar bg-" +
      progressBarColor +
      "' role='progressbar' style='width: " +
      mainSlimeHealthPercent +
      "%'></div></div><div class='progress-bar-health'>" +
      +mainSlime.combat.current +
      "/" +
      mainSlime.combat.max +
      "</div>" +
      "</div>";
  }
  followingSlimes.forEach(slime => {
    if (slime.color && slime.combat.current) {
      let slimeHealthPercent = parseInt(
        (slime.combat.current / slime.combat.max) * 100
      );
      let progressBarColor = "success";
      if (slimeHealthPercent <= 33) {
        progressBarColor = "danger";
      } else if (slimeHealthPercent <= 66) {
        progressBarColor = "warning";
      }
      html +=
        "<div class='sprite-info following'>" +
        "<img class='slime-img' src='assets/ui/slime-" +
        slime.color +
        ".png' />" +
        "<div class='progress'><div class='progress-bar bg-" +
        progressBarColor +
        "' role='progressbar' style='width: " +
        slimeHealthPercent +
        "%'></div></div><div class='progress-bar-health'>" +
        slime.combat.current +
        " / " +
        slime.combat.max +
        "</div>" +
        "</div>";
    }
  });
  html += "</div>";
  document.getElementById("status").innerHTML = html;
}

// Runs once per frame for the duration of the scene
function update(time, delta) {
  this.waterLayer1.setCollisionByProperty(
    { collide: true },
    this.slimeCollideWaterLayer1
  );
  this.waterLayer2.setCollisionByProperty(
    { collide: true },
    this.slimeCollideWaterLayer2
  );
  this.doorLayer.setCollisionByProperty(
    { collide: true },
    this.slimeCollideDoorLayer
  );

  window.gameObj = this;
  updateStatuses(this.movingSlime, this.followingSlimes.children.entries);
  // to add slimes
  this.physics.collide(
    this.movingSlime,
    this.staticSlimes,
    staticSlimeCollision,
    staticSlimeCollision,
    this
  );
  this.slimePos[this.slimePosIndexOffset] = this.movingSlime.x;
  this.slimePos[this.slimePosIndexOffset + 1] = this.movingSlime.y;
  this.slimePosIndexOffset = this.slimePosIndexOffset - 2;
  if (this.slimePosIndexOffset < 0)
    this.slimePosIndexOffset = this.slimePosIndexOffset + 1000;
  for (var i = 0; i < this.followingSlimes.children.size; i++) {
    var idx = this.slimePosIndexOffset + (i + 1) * 30;
    idx = idx % 1000;
    this.followingSlimes.children.entries[i].x = this.slimePos[idx];
    this.followingSlimes.children.entries[i].y = this.slimePos[idx + 1];
  }
  // Apply the controls to the camera each update tick of the game
  const speed = SLIME_SPEED;

  // Stop any previous movement from the last frame
  this.movingSlime.body.setVelocity(0);

  // Horizontal movement
  if (cursors.left.isDown && gameStarted) {
    this.movingSlime.body.setVelocityX(-speed);
  } else if (cursors.right.isDown) {
    this.movingSlime.body.setVelocityX(speed);
  }

  // Vertical movement
  if (cursors.up.isDown && gameStarted) {
    this.movingSlime.body.setVelocityY(-speed);
  } else if (cursors.down.isDown) {
    this.movingSlime.body.setVelocityY(speed);
  }

  // Normalize and scale the velocity so that this.movingSlime can't move faster along a diagonal
  this.movingSlime.body.velocity.normalize().scale(speed);

  // Update the animation last and give left/right animations precedence over up/down animations
  if (cursors.left.isDown) {
    this.movingSlime.anims.play("slime_walk_left", true);
  } else if (cursors.right.isDown) {
    this.movingSlime.anims.play("slime_walk_right", true);
  } else if (cursors.up.isDown) {
    this.movingSlime.anims.play("slime_walk_up", true);
  } else if (cursors.down.isDown) {
    this.movingSlime.anims.play("slime_walk_down", true);
  } else {
    this.movingSlime.anims.play("slime_walk_down", true);
  }

  //top-down layering
  this.movingSlime.depth = this.movingSlime.y;
  this.staticSlimes.children.entries.forEach(
    staticSlime => (staticSlime.depth = this.movingSlime.depth)
  );
  this.wizards.children.entries.forEach(wizard => {
    wizard.depth = this.movingSlime.depth;

    const graphics = wizard.healthBar;
    graphics.clear();
    const currentHealthRatio = wizard.combat.current / wizard.combat.max;
    if (currentHealthRatio > 0.5) {
      graphics.fillStyle(0x00ff00);
    } else if (currentHealthRatio > 0.25) {
      graphics.fillStyle(0xffff00);
    } else {
      graphics.fillStyle(0xff0000);
    }

    graphics.fillRect(wizard.x - 11, wizard.y - 17, 20 * currentHealthRatio, 3);
    graphics.setDepth(wizard.depth + 1);
  });

  this.knights.children.entries.forEach(knight => {
    knight.depth = this.movingSlime.depth;

    const graphics = knight.healthBar;
    graphics.clear();
    const currentHealthRatio = knight.combat.current / knight.combat.max;
    if (currentHealthRatio > 0.5) {
      graphics.fillStyle(0x00ff00);
    } else if (currentHealthRatio > 0.25) {
      graphics.fillStyle(0xffff00);
    } else {
      graphics.fillStyle(0xff0000);
    }

    graphics.fillRect(knight.x - 11, knight.y - 17, 20 * currentHealthRatio, 3);
    graphics.setDepth(knight.depth + 1);
  });

  // Layer the slimes so they are all over the proceding one
  this.followingSlimes.children.entries.forEach(function(slime, index) {
    slime.depth = this.movingSlime.depth - 0.1 * (index + 1);
  }, this);

  this.followingSlimes.children.entries.forEach(function(slime, index) {
    let animDir = "";
    if (this.movingSlime.body.velocity.y > 0) {
      animDir = "down";
    } else if (this.movingSlime.body.velocity.x < 0) {
      animDir = "left";
    } else if (this.movingSlime.body.velocity.x > 0) {
      animDir = "right";
    } else if (this.movingSlime.body.velocity.y < 0) {
      animDir = "up";
    } else {
      animDir = "down";
    }
    let anim = "slime_walk_" + animDir;
    if (!slime.anims.isPlaying || anim !== slime.anims.currentAnim.key) {
      slime.play(anim);
    }
  }, this);
}
