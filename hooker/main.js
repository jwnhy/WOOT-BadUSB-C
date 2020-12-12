const {
  app,
  BrowserWindow,
  Notification,
  Menu,
  Tray,
  shell,
  dialog,
  ipcMain,
} = require("electron");
const ioHook = require("iohook");

const blacklist = ["sudo"];

const buffer = [];

let count = 0;

let flag1 = false,
  flag2 = false;

setInterval(() => {
  count = 0;
  flag1 = false;
  flag2 = false;
}, 1000);

ioHook.on("keydown", (evt) => {
  buffer.push(evt.rawcode);
  count += 1;

  if (count > 10) {
    if (!flag1) {
      notify("warning", "too frequent");
    }
    flag1 = true;
  }

  blacklist.forEach((str) => {
    if (str.length > buffer.length) return;
    const len = str.length;
    for (let i = 0; i < len; i++) {
      const chr = String.fromCharCode(buffer[buffer.length - len + i]);
      //   console.log(chr.toLowerCase(), str[i].toLowerCase());
      if (chr.toLowerCase() != str[i].toLowerCase()) {
        return;
      }
    }
    if (!flag2) {
      notify("warning", "dangerous command typed");
    }
    flag2 = true;
  });
});

let mainWindow;

var notify = function (title, body) {
  const notification = {
    title,
    body,
  };
  new Notification(notification).show();
};
function createWindow() {
  mainWindow = new BrowserWindow({ width: 800, height: 600 });

  mainWindow.loadFile("index.html");
  mainWindow.on("closed", function () {
    mainWindow = null;
  });
  const iohook = require("iohook");
  iohook.start();
}

app.on("ready", createWindow);

app.on("window-all-closed", function () {
  if (process.platform !== "darwin") {
    app.quit();
  }
});

app.on("activate", function () {
  if (mainWindow === null) {
    createWindow();
  }
});
