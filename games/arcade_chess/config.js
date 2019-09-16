let config =  {
  fpsTag: document.getElementById('fps'),
  turnTag: document.getElementById('turn'),
  infoTag: document.getElementById('info'),
  winnerTag: document.getElementById('winner'),
  testing: false,
  blank_board: [
    2, 3, 4, 5, 6, 4, 3, 2,
    1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    -1, -1, -1,  6, -1, -1, -1, -1,
    -2, -3, -4, -5, -6, -4, -3, -2
  ],
  rows: 8,
  cols: 8,
  pieces_codes: {
    NO_PIECE: 0,
    PAWN: 1,
    ROOK: 2,
    KNIGHT: 3,
    BISHOP: 4,
    KING: 5,
    QUEEN: 6
  },
  playerOneKeyMap: {
    up: 87,
    down: 83,
    left: 65,
    right: 68,
    select: 70
  },
  playerTwoKeyMap: {
    up: 73,
    down: 75,
    left: 74,
    right: 76,
    select: 72
  },
  messageTypes: {
    keyDown: 'KEY_DOWN',
    keyUp: 'KEY_UP',
    gameOver: 'GAME_OVER'
  }
}

export const init = (ops) => {
  config.tileHeight = ops.tileHeight
  config.tileWidth = ops.tileWidth
}

export default config