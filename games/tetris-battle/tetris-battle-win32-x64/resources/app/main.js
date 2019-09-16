const electron = require('electron');
const { app, BrowserWindow } = electron;
const remote = require("electron").remote;

app.on('ready', () => {
  let window = new BrowserWindow({ width: 1000, height: 800, frame: false});
  window.loadURL(`file://${__dirname}/index.html`);
  window.show();

  const ret = electron.globalShortcut.register('Escape', function(){
    window.close();
  });
})

/*
*Example of adding a function to the main electron controller
exports.openWindow = () => {
  let window = new BrowserWindow({ width: 800, height: 600});
  window.loadURL("https://www.google.com");
}
*/