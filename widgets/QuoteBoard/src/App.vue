<template>
  <!-- <HelloWorld msg="Welcome to Your Vue.js App" /> -->
  <md-protocol />
</template>

<script>
// import HelloWorld from './components/HelloWorld.vue'
import mdProtocol from "./components/mdProtocol.vue"
export default {
  name: 'App',
  components: {
    // HelloWorld,
    mdProtocol
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  background-color: black;
  color: white;
  height: 100vh;
}
</style>
