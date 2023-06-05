// index.js

var { remote } = require('electron');
// import { remote } from 'electron'


// 错误提示框
const errMessage = (message) => {
  console.log("errMessage", message)
  remote.dialog.showErrorBox('温馨提示', message)
};

// // 消息提示框(异步)
// mesageBoxDom.onclick = () => {
//   remote.dialog.showMessageBox({
//     type: "info",
//     buttons: ["确认", "取消"],
//     title: "关于我们",
//     message: `
//         这是一个神有奇的软件，
//         当你打开的时候，
//         你会发现你离不开它了，
//         因为你关不掉了，
//         哈哈哈...
//         `
//   }).then((result) => {
//     if (result.response == 0) {
//       console.log("确定")
//     } else if (result.response == 1) {
//       console.log("取消")
//     }
//   }).catch((error) => {
//     console.log(error);
//   });
//   console.log("异步方法执行开始");
// };
// // 消息提示框(同步)
// mesageBoxDomSync.onclick = () => {
//   var result = remote.dialog.showMessageBoxSync({
//     type: "info",
//     buttons: ["确认", "取消"],
//     title: "关于我们",
//     message: `
//         这是一个神有奇的软件，
//         当你打开的时候，
//         你会发现你离不开它了，
//         因为你关不掉了，
//         哈哈哈...
//         `
//   });
//   console.log(result);
//   console.log("同步方法执行完成");
// };


// // 打开对话框(异步)
// openDialogDom.onclick = () => {
//   remote.dialog.showOpenDialog({

//     title: "选择目标",
//     // 打开单个文件
//     // properties:["openFile"],

//     // 打开多个文件
//     // properties:["openFile","multiSelections"],

//     // 打开目录
//     properties: ["openDirectory"]

//   }).then((result) => {

//     // 是否取消
//     console.log(result.canceled);
//     // 文件路径
//     console.log(result.filePaths);

//   }).catch((error) => {
//     console.log(error);
//   });

//   console.log("异步方法执行开始");
// };
// // 打开对话框(同步)
// openDialogDomSync.onclick = () => {

//   var result = remote.dialog.showOpenDialogSync({
//     title: "选择目标",
//     // 打开单个文件
//     // properties:["openFile"],

//     // 打开多个文件
//     // properties:["openFile","multiSelections"],

//     // 打开目录
//     properties: ["openDirectory"]

//   });

//   console.log(result);
//   console.log("同步方法执行完成");
// };


// // 保存对话框(异步)
// saveDialogDom.onclick = () => {
//   remote.dialog.showSaveDialog({
//     title: "保存文件",
//     // 默认文件名
//     defaultPath: "file.text",
//     // 保存类型选择过滤
//     filters: [
//       { name: 'Images', extensions: ['jpg', 'png', 'gif'] },
//       { name: 'Movies', extensions: ['mkv', 'avi', 'mp4'] },
//       { name: 'Custom File Type', extensions: ['as'] },
//       { name: 'All Files', extensions: ['*'] }
//     ]
//   }).then((result) => {
//     // 是否取消
//     console.log(result.canceled);
//     // 保存后的文件路径
//     console.log(result.filePath);
//   }).catch((error) => {
//     console.log(error);
//   });
//   console.log("异步方法执行开始");


// };
// // 保存对话框(同步)
// saveDialogDomSync.onclick = () => {

//   var result = remote.dialog.showSaveDialogSync({
//     title: "保存文件",
//     // 默认文件名
//     defaultPath: "file.text",
//     // 保存类型选择过滤
//     filters: [
//       { name: 'Images', extensions: ['jpg', 'png', 'gif'] },
//       { name: 'Movies', extensions: ['mkv', 'avi', 'mp4'] },
//       { name: 'Custom File Type', extensions: ['as'] },
//       { name: 'All Files', extensions: ['*'] }
//     ]
//   });
//   console.log(result);
//   console.log("同步方法执行完成");

// };

export { errMessage }