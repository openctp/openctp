const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  pluginOptions: {
    electronBuilder: {
      nodeIntegration: true,
      builderOptions: {
        // extraFiles: ["config.json"],
        extraResources: [{ from: "./config.json", to: "../" }],
      },
      nsis: {
        allowToChangeInstallationDirectory: true,
        oneClick: false
      },
      win: {
        icon: './public/favicon.ico'
      },
      mac: {
        icon: './public/favicon.ico'
      },
      productName: 'QuoteBoard'
    }
  }
})
