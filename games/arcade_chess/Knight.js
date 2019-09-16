import images                           from "./ImageLoader"
import config                           from './config'
import { coordsToIndex, indexToCoords } from "./utils";

class Knight {
  constructor(coords, pieceCode) {
    this.x = coords.x
    this.y = coords.y
    this.row = coords.row
    this.col = coords.col
    this.img = pieceCode > 0 ? images.b_knight : images.w_knight
    this.code = pieceCode
    this.magnitude = this.code / Math.abs(this.code)
  }

  getPossibleMoves(player, board) {
    let currentIndex = coordsToIndex(this.row, this.col)
    let possibleMoves = []
    let proposedIndex

    let doubleForwardIndex = currentIndex + ((config.cols * 2) * this.magnitude)
    let singleRightIndex = doubleForwardIndex + 1
    if (this.inBounds(doubleForwardIndex, singleRightIndex)) {
      proposedIndex = singleRightIndex
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    let singleLeftIndex = doubleForwardIndex - 1
    if (this.inBounds(doubleForwardIndex, singleLeftIndex)) {
      proposedIndex = singleLeftIndex
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    let doubleBackwardIndex = currentIndex - ((config.cols * 2) * this.magnitude)
    singleRightIndex = doubleBackwardIndex + 1
    if (this.inBounds(doubleBackwardIndex, singleRightIndex)) {
      proposedIndex = singleRightIndex
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    singleLeftIndex = doubleBackwardIndex - 1
    if (this.inBounds(doubleBackwardIndex, singleLeftIndex)) {
      proposedIndex = singleLeftIndex
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    let singleForwardIndex = currentIndex + (config.cols * this.magnitude)
    let doubleRightIndex = singleForwardIndex + 2
    if (this.inBounds(singleForwardIndex, doubleRightIndex)) {
      proposedIndex = doubleRightIndex
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    let doubleLeftIndex = singleForwardIndex - 2
    if (this.inBounds(singleForwardIndex, doubleLeftIndex)) {
      proposedIndex = doubleLeftIndex
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    let singleBackwardIndex = currentIndex - (config.cols * this.magnitude)
    doubleRightIndex = singleBackwardIndex + 2
    if (this.inBounds(singleBackwardIndex, doubleRightIndex)) {
      proposedIndex = doubleRightIndex
      let pieceOnTile = board[proposedIndex]
      if (!pieceOnTile || !player.ownsPiece(pieceOnTile.code)) {
        possibleMoves.push(proposedIndex)
      }
    }

    doubleLeftIndex = singleBackwardIndex - 2
    if (this.inBounds(singleBackwardIndex, doubleLeftIndex)) {
      proposedIndex = doubleLeftIndex
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
    if (prevIndex - nextIndex === 2 && (prevIndex % 8 === 0 || (prevIndex - 1) % 8 === 0)) {
      return false
    }
    if (nextIndex - prevIndex === 1 && nextIndex % 8 === 0) {
      return false
    }
    if (nextIndex - prevIndex === 2 && ((prevIndex + 1) % 8 === 0 || (prevIndex + 2) % 8 === 0)) {
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

export default Knight