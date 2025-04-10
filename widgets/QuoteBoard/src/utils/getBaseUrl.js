const { app } = require("electron").remote;
const path = require("path");
import fs from 'fs';
export function getSystem() {
  //这是mac系统
  if (process.platform == "darwin") {
    return 1;
  }
  //这是windows系统
  if (process.platform == "win32") {
    return 2;
  }
  //这是linux系统
  if (process.platform == "linux") {
    return 3;
  }
}
/**
 *
 * @returns 获取安装路径
 */
export function getExePath() {
  return path.dirname(app.getPath("exe"));
}

/**
 *
 * @returns 获取配置文件路径
 */
export function getConfigPath() {
  if (getSystem() === 1) {
    return path.dirname(getExePath()) + "/config.json";
  } else {
    return getExePath() + "\\config.json";
  }
}
/**
 * 读取配置文件
 */
export function readConfig(callback) {
  if (app.isPackaged) {
    fs.readFile(getConfigPath(), "utf-8", (err, data) => {
      if (data) {
        //有值
        const config = JSON.parse(data);
        callback(config);
      }
    });
  } else {
    console.log("222")
    fs.readFile("config.json", "utf-8", (err, data) => {
      if (data) {
        //有值
        const config = JSON.parse(data);
        callback(config);
      }
    })

  }



}