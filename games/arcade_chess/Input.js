import config from './config'

class Input {
  constructor(messager) {
    this.messager = messager
    this.setupEventListeners()
  }

  setupEventListeners() {
    document.onkeydown = (evt) => {
      this.messager.post({type: config.messageTypes.keyDown, keyCode: evt.keyCode})
    }
  }
}

export default Input