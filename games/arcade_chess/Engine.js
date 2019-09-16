import {loadImages} from "./ImageLoader";
import Input from './Input'
import config from './config'
import Messager            from './Messager'

class Engine {
  constructor(onStartUp, ctx) {
    this.ctx = ctx
    this.onStartUp = onStartUp
    this.fps = 0
    this.messager = new Messager()
    new Input(this.messager)
    loadImages(this.startUp)
  }

  startUp = () => {
    this.onStartUp()
    this.lastUpdateTime = new Date().getTime()
    this.frameCounter = 0
    this.frameTime = 0
    window.requestAnimationFrame(this.loop)
  }

  loop = () => {
    const currentTime = new Date().getTime()
    const deltaTime = (currentTime - this.lastUpdateTime) / 1000
    this.lastUpdateTime = currentTime

    this.frameCounter++
    this.frameTime += deltaTime

    if(this.frameTime >= .5) {
      this.frameTime = .5 - this.frameTime
      this.fps = this.frameCounter * 2
      this.frameCounter = 0
      config.fpsTag.innerText = `FPS: ${this.fps}`
    }

    if(this.update) {
      this.update()
    }

    if(this.draw) {
      this.draw()
    }
    window.requestAnimationFrame(this.loop)
  }
}

export default Engine