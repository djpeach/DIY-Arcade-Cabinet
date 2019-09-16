import config                           from './config'
import { coordsToIndex, indexToCoords } from './utils'

let hm_players = 0;

class Player {

  constructor(keymap, messager) {
    this.keymap = keymap
    this.messager = messager
    hm_players++
    this.playerNumber = hm_players
    this.currentTile = this.playerNumber === 1 ? 63 : 0
    this.heldPiece = null
    this.magnitude = this.playerNumber === 1 ? -1 : 1
    this.kingCode = config.pieces_codes.KING * this.magnitude
    this.inCheck = false
    this.inCheckMate = false
    this.infoText = 'Good Luck!'
    this.gameOver = false
  }

  update(cb, board, otherPlayer) {
    this.endTurn = cb
    this.board = board
    this.opponent = otherPlayer

    config.turnTag.innerText = `Player ${this.playerNumber}'s turn`
    config.infoTag.innerText = this.infoText
  }

  draw(ctx) {
    let currentTileCoords = indexToCoords(this.currentTile)
    ctx.fillStyle = 'cornflowerblue'
    ctx.fillRect(currentTileCoords.x, currentTileCoords.y, config.tileWidth, config.tileHeight)

    if (this.heldPiece) {
      ctx.fillStyle = 'rgba(80, 100, 230, 0.3)'
      this.heldPiece.showPossibleMoves(this, this.board, ctx)
    }

    if (this.inCheck) {
      ctx.fillStyle = 'rgba(193, 66, 66, 0.57)'
      let kingCoords = indexToCoords(this.kingIndex)
      ctx.fillRect(kingCoords.x, kingCoords.y, config.tileWidth, config.tileHeight)
    }
  }

  selectTile(selectedTileIndex) {
    if (this.heldPiece) {
      if (this.heldPiece.getPossibleMoves(this, this.board).indexOf(selectedTileIndex) >= 0) {
        let pieceOnSelectedTile = this.board[selectedTileIndex]
        let { prevCoords, movedPiece } = this.movePiece(selectedTileIndex)
        this.checkIfKingInCheck()
        if (this.inCheck) {
          let prevIndex = coordsToIndex(prevCoords.row, prevCoords.col)
          this.board[prevIndex] = movedPiece
          this.board[selectedTileIndex] = pieceOnSelectedTile
          movedPiece.move(prevCoords)
          this.infoText = `You cannot move there, you must protect your King`
        } else {
          this.endTurn()
        }
      } else if (this.board[selectedTileIndex] && this.ownsPiece(this.board[selectedTileIndex].code)) {
        this.heldPiece = this.board[selectedTileIndex]
      } else {
        this.infoText = `You cannot move there`
      }
    } else if (this.ownsPiece(this.board[selectedTileIndex].code)){
      this.heldPiece = this.board[selectedTileIndex]
    } else {
      this.infoText = `That is not yours`
    }
  }

  movePiece(selectedTileIndex) {
    let attackedPiece = this.board[selectedTileIndex]
    if (attackedPiece && Math.abs(attackedPiece.code) === config.pieces_codes.KING) {
      this.messager.post({type: config.messageTypes.gameOver})
    }
    this.board[coordsToIndex(this.heldPiece.row, this.heldPiece.col)] = null
    let prevCoords = { x: this.heldPiece.x, y: this.heldPiece.y, col: this.heldPiece.col, row: this.heldPiece.row }
    let coords = indexToCoords(selectedTileIndex)
    coords.row = coords.y / config.tileHeight
    coords.col = coords.x / config.tileWidth
    this.heldPiece.move(coords)
    this.board[selectedTileIndex] = this.heldPiece
    let movedPiece = this.heldPiece
    this.heldPiece = null
    return { prevCoords, movedPiece }
  }

  checkIfKingInCheck() {
    let inCheck = false
    this.infoText = ''
    for(let i=0;i<this.board.length;i++) {
      let piece = this.board[i]
      if (piece) {
        if (!this.ownsPiece(piece.code)) {
          piece.getPossibleMoves(this.opponent, this.board).map(index => {
            let pieceUnderAttack = this.board[index]
            if (pieceUnderAttack && pieceUnderAttack.code === this.kingCode) {
              inCheck = true
              this.kingIndex = index
              this.infoText = `Your King is under attack!`
            }
          })
        }
      }
    }
    this.inCheck = inCheck
  }

  ownsPiece(pieceCode) {
    if (this.playerNumber === 1) {
      return pieceCode < 0
    } else if (this.playerNumber === 2) {
      return pieceCode > 0
    }
  }

  handleMsg(msg) {
    switch(msg.type) {
      case config.messageTypes.keyDown:
        if (!this.gameOver) {
          switch (msg.keyCode) {
            case this.keymap.up:
              if(this.currentTile - 8 >= 0) {
                this.currentTile -= 8
              }
              break
            case this.keymap.down:
              if(this.currentTile + 8 <= 63) {
                this.currentTile += 8
              }
              break
            case this.keymap.left:
              if (this.currentTile % 8 === 0) {
                this.currentTile += 7
              } else {
                this.currentTile--
              }
              break
            case this.keymap.right:
              if((this.currentTile + 1) % 8 === 0) {
                this.currentTile -= 7
              } else {
                this.currentTile++
              }
              break
            case this.keymap.select:
              this.selectTile(this.currentTile)
              break
            default:
              // pass
          }
        }
        break
      case config.messageTypes.gameOver:
        this.gameOver = true
      default:
        // pass
    }
  }
}

export default Player