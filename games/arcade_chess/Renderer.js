import config, {init} from './config'
import Chess from './Chess'

class Renderer {
  constructor() {
    this.canvas = document.getElementById('canvas')
    this.ctx = this.canvas.getContext('2d')
    this.sideLength = document.getElementById('canvasBox').clientHeight
    this.canvas.height = this.sideLength
    this.canvas.width = this.sideLength
    this.canvas.imageSmoothingEnabled = false
    init({
      tileHeight: this.canvas.height / config.rows,
      tileWidth: this.canvas.width / config.cols
    })
    new Chess(this.ctx)
  }
}

new Renderer()