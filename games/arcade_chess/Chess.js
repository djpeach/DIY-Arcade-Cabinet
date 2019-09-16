import config            from './config'
import { coordsToIndex } from "./utils"
import Bishop            from './Bishop'
import King              from './King'
import Knight            from './Knight'
import Pawn              from './Pawn'
import Queen             from './Queen'
import Rook              from './Rook'
import Engine            from './Engine'
import Player            from './Player'

class Chess {
  constructor(ctx) {
    this.blank_board = config.blank_board
    this.board = []
    this.rows = config.rows
    this.cols = config.cols
    this.engine = new Engine(this.initializeBoard, ctx)
    this.engine.update = this.update
    this.engine.draw = this.draw
    this.messager = this.engine.messager
    this.player1 = new Player(config.playerOneKeyMap, this.messager)
    this.player2 = new Player(config.playerTwoKeyMap, this.messager)
    this.currentPlayer = this.player1
    this.otherPlayer = this.player2
    this.messager.subscribe(this.currentPlayer)
  }

  initializeBoard = () => {
    const w = config.tileWidth
    const h = config.tileHeight
    for (let row = 0; row < this.rows; row++) {
      for (let col = 0; col < this.cols; col++) {
        let piece
        let tileIndex = coordsToIndex(row, col)
        let coords = { x: col * w, y: row * h, row: row, col: col }
        switch (Math.abs(this.blank_board[ tileIndex ])) {
          case config.pieces_codes.PAWN:
            piece = new Pawn(coords, this.blank_board[ tileIndex ])
            break
          case config.pieces_codes.ROOK:
            piece = new Rook(coords, this.blank_board[ tileIndex ])
            break
          case config.pieces_codes.KNIGHT:
            piece = new Knight(coords, this.blank_board[ tileIndex ])
            break
          case config.pieces_codes.BISHOP:
            piece = new Bishop(coords, this.blank_board[ tileIndex ])
            break
          case config.pieces_codes.KING:
            piece = new King(coords, this.blank_board[ tileIndex ])
            break
          case config.pieces_codes.QUEEN:
            piece = new Queen(coords, this.blank_board[ tileIndex ])
            break
          default:
            // pass
        }
        if (piece) {
          this.board[ tileIndex ] = piece
        }
      }
    }
  }

  drawBoard() {
    let color = ''
    const w = config.tileWidth
    const h = config.tileHeight
    for(let row = 0;row<this.rows;row++) {
      color = Math.floor(row % 2) === 0 ? 'grey' : 'black'
      for(let col = 0;col<this.cols;col++) {
        this.engine.ctx.fillStyle = color
        this.engine.ctx.fillRect(col * w, row * h, w, h)
        color = color === 'grey' ? 'black' : 'grey'
        if (config.testing) {
          let index = coordsToIndex(row, col)
          this.engine.ctx.fillStyle = 'yellow'
          this.engine.ctx.font = "30px Arial"
          this.engine.ctx.fillText(index, col * w + 10, row * h + 30)
        }
      }
    }
  }

  drawPieces() {
    for(let pieceIndex = 0; pieceIndex<this.board.length; pieceIndex++) {
      let piece = this.board[pieceIndex]
      if(piece) {
        this.engine.ctx.drawImage(piece.img, piece.x, piece.y, config.tileWidth, config.tileHeight)
      }
    }
  }

  update = () =>  {
    if (this.gameOver) {
      config.winnerTag.innerText = `Game Over! Player ${this.otherPlayer.playerNumber} wins!`
    }
    this.currentPlayer.update(this.switchPlayer, this.board, this.otherPlayer)
  }

  switchPlayer = () => {
    this.messager.unsubscribe(this.currentPlayer)
    let tempPlayer = this.currentPlayer
    this.currentPlayer = this.otherPlayer
    this.otherPlayer = tempPlayer
    this.messager.subscribe(this.currentPlayer)
    if (this.currentPlayer.board) {
      this.currentPlayer.checkIfKingInCheck()
    }
  }

  draw = () => {
    this.drawBoard()
    if(!this.gameOver) {
      this.currentPlayer.draw(this.engine.ctx)
    }
    this.drawPieces()
  }
}

export default Chess