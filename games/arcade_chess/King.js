import images                           from "./ImageLoader"
import config                           from './config'
import { coordsToIndex, indexToCoords } from "./utils";

class King {
  constructor(coords, pieceCode) {
    this.x = coords.x
    this.y = coords.y
    this.row = coords.row
    this.col = coords.col
    this.img = pieceCode > 0 ? images.b_king : images.w_king
    this.code = pieceCode
    this.magnitude = this.code / Math.abs(this.code)
  }

  getPossibleMoves(player, board) {
    let currentIndex = coordsToIndex(this.row, this.col)
    let possibleMoves = []

    let proposedIndex = currentIndex + (config.cols * this.magnitude) // move forward
    if (this.inBounds(currentIndex, proposedIndex)) {
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    proposedIndex = currentIndex - (config.cols * this.magnitude) // move backward
    if (this.inBounds(currentIndex, proposedIndex)) {
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    proposedIndex = currentIndex + 1 // move right
    if (this.inBounds(currentIndex, proposedIndex)) {
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    proposedIndex = currentIndex - 1 // move left
    if (this.inBounds(currentIndex, proposedIndex)) {
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    proposedIndex = currentIndex + (config.cols * this.magnitude) + 1 // move forward right
    if (this.inBounds(currentIndex, proposedIndex)) {
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    proposedIndex = currentIndex + (config.cols * this.magnitude) - 1 // move forward left
    if (this.inBounds(currentIndex, proposedIndex)) {
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    proposedIndex = currentIndex - (config.cols * this.magnitude) + 1 // move backwards right
    if (this.inBounds(currentIndex, proposedIndex)) {
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    proposedIndex = currentIndex - (config.cols * this.magnitude) - 1 // move backwards left
    if (this.inBounds(currentIndex, proposedIndex)) {
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
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
    if (nextIndex > config.cols * config.rows) {
      return false
    }
    if (prevIndex - nextIndex === 1 && prevIndex % 8 === 0) {
      return false
    }
    if (nextIndex - prevIndex === 1 && nextIndex % 8 === 0) {
      return false
    }
    if (nextIndex - prevIndex === 9 && nextIndex % 8 === 0) {
      return false
    }
    if (nextIndex - prevIndex === 7 && prevIndex % 8 ===0) {
      return false
    }
    if (nextIndex - prevIndex === -9 && prevIndex % 8 === 0) {
      return false
    }
    if (nextIndex - prevIndex === -7 && nextIndex % 8 === 0) {
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

export default King