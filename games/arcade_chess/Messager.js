class Messager {
  constructor() {
    this.subscribers = []
  }

  subscribe(subscriber) {
    if(this.subscribers.indexOf(subscriber) < 0) {
      this.subscribers.push(subscriber)
      console.log('subscribed')
    }
  }

  unsubscribe(subscriber) {
    let subIndex = this.subscribers.indexOf(subscriber)
    this.subscribers.splice(subIndex, 1)
  }

  post(msg) {
    this.subscribers.forEach(sub => {
      sub.handleMsg(msg)
    })
  }
}

export default Messager