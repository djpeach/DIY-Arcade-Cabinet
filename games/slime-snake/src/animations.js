export default function makeAnimations(scene) {
  scene.anims.create({
    key: "slime_walk_down",
    frames: scene.anims.generateFrameNumbers("slime", {
      start: 0,
      end: 2,
      first: 0
    }),
    frameRate: 10,
    repeat: -1
  });

  scene.anims.create({
    key: "slime_walk_left",
    frames: scene.anims.generateFrameNumbers("slime", {
      start: 3,
      end: 5,
      first: 3
    }),
    frameRate: 10,
    repeat: -1
  });

  scene.anims.create({
    key: "slime_walk_right",
    frames: scene.anims.generateFrameNumbers("slime", {
      start: 6,
      end: 8,
      first: 6
    }),
    frameRate: 10,
    repeat: -1
  });

  scene.anims.create({
    key: "slime_walk_up",
    frames: scene.anims.generateFrameNumbers("slime", {
      start: 9,
      end: 11,
      first: 9
    }),
    frameRate: 10,
    repeat: -1
  });

  scene.anims.create({
    key: "slime_dead",
    frames: scene.anims.generateFrameNumbers("slime", {
      start: 12,
      end: 12,
      first: 12
    }),
    frameRate: 10,
    repeat: -1
  });

  scene.anims.create({
    key: "wizard_blue_idle",
    frames: scene.anims.generateFrameNumbers("wizard-blue", {
      start: 0,
      end: 0,
      first: 0
    }),
    frameRate: 10,
    repeat: -1
  });

  scene.anims.create({
    key: "wizard_blue_attack",
    frames: scene.anims.generateFrameNumbers("wizard-blue", {
      start: 0,
      end: 3,
      first: 0
    }),
    frameRate: 10,
    repeat: 1
  });

  scene.anims.create({
    key: "wizard_red_idle",
    frames: scene.anims.generateFrameNumbers("wizard-red", {
      start: 0,
      end: 0,
      first: 0
    }),
    frameRate: 10,
    repeat: -1
  });

  scene.anims.create({
    key: "wizard_red_attack",
    frames: scene.anims.generateFrameNumbers("wizard-red", {
      start: 0,
      end: 3,
      first: 0
    }),
    frameRate: 10,
    repeat: 1
  });

  scene.anims.create({
    key: "wizard_green_idle",
    frames: scene.anims.generateFrameNumbers("wizard-green", {
      start: 0,
      end: 0,
      first: 0
    }),
    frameRate: 10,
    repeat: -1
  });

  scene.anims.create({
    key: "wizard_green_attack",
    frames: scene.anims.generateFrameNumbers("wizard-green", {
      start: 0,
      end: 3,
      first: 0
    }),
    frameRate: 10,
    repeat: 1
  });

  scene.anims.create({
    key: "knight_red_idle",
    frames: scene.anims.generateFrameNumbers("knight-red", {
      start: 0,
      end: 0,
      first: 0
    }),
    frameRate: 10,
    repeat: -1
  });

  scene.anims.create({
    key: "knight_red_attack",
    frames: scene.anims.generateFrameNumbers("knight-red", {
      start: 0,
      end: 3,
      first: 0
    }),
    frameRate: 10,
    repeat: 1
  });

  scene.anims.create({
    key: "knight_silver_idle",
    frames: scene.anims.generateFrameNumbers("knight-silver", {
      start: 0,
      end: 0,
      first: 0
    }),
    frameRate: 10,
    repeat: -1
  });

  scene.anims.create({
    key: "knight_silver_attack",
    frames: scene.anims.generateFrameNumbers("knight-silver", {
      start: 0,
      end: 3,
      first: 0
    }),
    frameRate: 10,
    repeat: 1
  });
}
