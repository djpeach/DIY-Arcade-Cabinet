export const SHOW_DEBUG = false;

export const IGNORE_MAP_COLLISION = false;

export const SLIME_START_COLOR = "green";

export const SLIME_SPEED = 60;

export const TINT_MAP = {
  red: 0xff0000,
  green: 0x00ff00,
  blue: 0x0000ff,
  purple: 0xaa00ff,
  yellow: 0xffff00
};

export const COMBAT_MAP = {
  slime: {
    red: {
      current: 500,
      max: 500,
      attack: 50,
      attackPeriod: 1000,
      lastAttack: null
    },
    green: {
      current: 500,
      max: 500,
      attack: 50,
      attackPeriod: 1000,
      lastAttack: null
    },
    blue: {
      current: 500,
      max: 500,
      attack: 50,
      attackPeriod: 1000,
      lastAttack: null
    },
    purple: {
      current: 500,
      max: 500,
      attack: 50,
      attackPeriod: 1000,
      lastAttack: null
    },
    yellow: {
      current: 500,
      max: 500,
      attack: 50,
      attackPeriod: 1000,
      lastAttack: null
    }
  },
  wizard: {
    blue: {
      current: 250,
      max: 250,
      attack: 50,
      attackPeriod: 1000,
      lastAttack: null
    },
    green: {
      current: 550,
      max: 550,
      attack: 60,
      attackPeriod: 1000,
      lastAttack: null
    },
    red: {
      current: 300,
      max: 300,
      attack: 70,
      attackPeriod: 1000,
      lastAttack: null
    }
  },
  knight: {
    red: {
      current: 550,
      max: 550,
      attack: 40,
      attackPeriod: 1000,
      lastAttack: null
    },
    silver: {
      current: 700,
      max: 700,
      attack: 60,
      attackPeriod: 1000,
      lastAttack: null
    }
  }
};
