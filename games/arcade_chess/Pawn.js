import images                                     from "./ImageLoader"
import config                                     from './config'
import { coordsToIndex, indexToCoords } from './utils'

class Pawn {
  constructor(coords, pieceCode) {
    this.x = coords.x
    this.y = coords.y
    this.row = coords.row
    this.col = coords.col
    this.img = pieceCode > 0 ? images.b_pawn : images.w_pawn
    this.code = pieceCode
    this.magnitude = this.code / Math.abs(this.code)
  }

  getPossibleMoves(player, board) {
    let currentIndex = coordsToIndex(this.row, this.col)
    let singleForwardIndex = currentIndex + (config.cols * this.magnitude)
    let doubleForwardIndex = currentIndex + ((config.cols * 2) * this.magnitude)
    let possibleMoves = []
    if(this.inBounds(currentIndex, singleForwardIndex) && !board[singleForwardIndex]) {
      possibleMoves.push(singleForwardIndex) // move up
    }
    if (this.inBounds(currentIndex, doubleForwardIndex) && this.row === config.rows - 2 || this.row === 1) { // first turn with pawn
      possibleMoves.push(doubleForwardIndex) // move up twice
    }
    if (this.inBounds(singleForwardIndex, singleForwardIndex + 1) && board[singleForwardIndex + 1] && !player.ownsPiece(board[singleForwardIndex + 1].code)) { // diagonal right piece to attack
      possibleMoves.push(singleForwardIndex + 1)
    }
    if (this.inBounds(singleForwardIndex, singleForwardIndex - 1) && board[singleForwardIndex - 1] && !player.ownsPiece(board[singleForwardIndex - 1].code)) {
      possibleMoves.push(singleForwardIndex - 1)
    }

    return possibleMoves
  }

  showPossibleMoves(player, board, ctx) {
    this.getPossibleMoves(player, board).forEach(proposedIndex => {
      let proposedCoords = indexToCoords(proposedIndex)
      ctx.fillRect(proposedCoords.x, proposedCoords.y, config.tileWidth, config.tileHeight)
    })
  }

  inBounds(prevIndex, nextIndex) {
    if (nextIndex < 0) {
      return false
    }
    if (nextIndex > config.cols * config.rows - 1) {
      return false
    }
    if (prevIndex - nextIndex === 1 && prevIndex % 8 === 0) {
      return false
    }
    if (nextIndex - prevIndex === 1 && nextIndex % 8 === 0) {
      return false
    }
    return true
  }

  move(coords) {
    this.x = coords.x
    this.y = coords.y
    this.row = coords.row
    this.col = coords.col
  }
}

export default Pawn