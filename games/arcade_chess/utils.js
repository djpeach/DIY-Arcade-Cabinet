import config from './config'

export function indexToCoords(index) {
  return {
    x: (index % 8) * config.tileWidth,
    y: Math.floor(index / 8) * config.tileHeight
  }
}

export function coordsToIndex(x, y) {
  return (x * 8) + y
}