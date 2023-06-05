const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  pluginOptions: {
    electronBuilder: {
      nodeIntegration: true
    }
  }
  
  // configureWebpack: {
  //   resolve: {
  //     fallback: {
  //       path: require.resolve("path-browserify"),
  //       fs: false
  //     },
  //   },
  // },


  // electronBuilder: {
  //   appId: "com.zcy.test",
  //   productName: "DAS",
  //   icon: "./app.ico",
  //   files: ["**/*", "static/*"],
  //   asar: true,
  //   win: {
  //     icon: "./app.ico",
  //     target: ["nsis"],
  //     extraResources: {
  //       from: "./core/",
  //       to: "./core/",
  //       filter: ["**/*"]
  //     }
  //   },
  //   mac: {
  //     icon: "./app.ico",
  //     target: ["nsis"],
  //     extraResources: {
  //       from: "./core/",
  //       to: "./core/",
  //       filter: ["**/*"]
  //     }
  //   }
  // }
})
