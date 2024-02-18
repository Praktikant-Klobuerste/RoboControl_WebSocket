"use strict";(self.webpackChunkrobo_control_web_socket=self.webpackChunkrobo_control_web_socket||[]).push([[6069],{2044:(e,n,r)=>{r.r(n),r.d(n,{assets:()=>l,contentTitle:()=>a,default:()=>u,frontMatter:()=>s,metadata:()=>i,toc:()=>c});var t=r(4848),o=r(8453);const s={sidebar_position:1},a="script_h",i={id:"c-files/script_h",title:"script_h",description:"",source:"@site/docs/c-files/script_h.md",sourceDirName:"c-files",slug:"/c-files/script_h",permalink:"/RoboControl-WebSocket/docs/c-files/script_h",draft:!1,unlisted:!1,editUrl:"https://github.com/facebook/docusaurus/tree/main/packages/create-docusaurus/templates/shared/docs/c-files/script_h.md",tags:[],version:"current",sidebarPosition:1,frontMatter:{sidebar_position:1},sidebar:"tutorialSidebar",previous:{title:"C Files",permalink:"/RoboControl-WebSocket/docs/category/c-files"}},l={},c=[];function d(e){const n={code:"code",h1:"h1",pre:"pre",...(0,o.R)(),...e.components};return(0,t.jsxs)(t.Fragment,{children:[(0,t.jsx)(n.h1,{id:"script_h",children:"script_h"}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-c",children:'const char* script_js = R"=====(\r\nvar gateway = `ws://${window.location.hostname}/ws`;\r\nvar websocket;\r\nvar isOn = true;\r\nwindow.addEventListener("load", onload);\r\n\r\nsetTimeout(() => {\r\n  function_body;\r\n}, time in milliseconds);\r\n\r\n// // Elemente aus dem DOM abrufen\r\n// const inputK1 = document.getElementById("inputServo1K1");\r\n// const inputK2 = document.getElementById("inputServo1K2");\r\n\r\n// // Event Listener hinzuf\xfcgen\r\n// inputK1.addEventListener("change", updateKValues);\r\n// inputK2.addEventListener("change", updateKValues);\r\n\r\n// // Funktion zur Aktualisierung der K-Werte\r\n// function updateKValues() {\r\n//    console.log("Updating")\r\n//   const valueK1 = parseFloat(inputK1.value);\r\n//   const valueK2 = parseFloat(inputK2.value);\r\n\r\n//   // Pr\xfcfen, ob die Summe von K1 und K2 1.00 ergibt\r\n//   if (valueK1 + valueK2 !== 1.00) {\r\n//     // Anpassung der Werte\r\n//     inputK1.value = (1.00 - valueK2).toFixed(2);\r\n//   }\r\n// }\r\n\r\nfunction onload(event) {\r\n  initWebSocket();\r\n}\r\n\r\nfunction getValues() {\r\n  websocket.send("getValues");\r\n}\r\n\r\nfunction isJson(str) {\r\n  try {\r\n    JSON.parse(str);\r\n  } catch (e) {\r\n    return false;\r\n  }\r\n  return true;\r\n}\r\n\r\nfunction initWebSocket() {\r\n  console.log("Trying to open a WebSocket connection\u2026");\r\n  websocket = new WebSocket(gateway);\r\n  websocket.onopen = onOpen;\r\n  websocket.onclose = onClose;\r\n  websocket.onmessage = onMessage;\r\n}\r\n\r\nfunction handleMessage(data) {\r\n  var message = data.split("&");\r\n  var topic = message[0];\r\n  var payload = message[1];\r\n  console.log(topic, payload);\r\n\r\n  // Power Button\r\n  if (topic == "armed") {\r\n    if (payload == "true") {\r\n      isOn = true;\r\n      document\r\n        .getElementById("btnPower")\r\n        .classList.replace("btn-outline-light", "btn-warning");\r\n    } else {\r\n      isOn = false;\r\n      document\r\n        .getElementById("btnPower")\r\n        .classList.replace("btn-warning", "btn-outline-light");\r\n    }\r\n  }\r\n}\r\n\r\nfunction onOpen(event) {\r\n  console.log("Connection opened");\r\n  getValues();\r\n}\r\n\r\nfunction onClose(event) {\r\n  console.log("Connection closed");\r\n  setTimeout(initWebSocket, 2000);\r\n}\r\n\r\nfunction updateSliderPWM(element) {\r\n  var sliderNumber = element.id.charAt(element.id.length - 1);\r\n  var sliderValue = document.getElementById(element.id).value;\r\n  document.getElementById("sliderValue" + sliderNumber).innerHTML = sliderValue;\r\n  console.log(sliderValue);\r\n  websocket.send(sliderNumber + "s" + sliderValue.toString());\r\n}\r\n\r\nfunction onMessage(event) {\r\n  console.log(event.data);\r\n\r\n  if (isJson(event.data)) {\r\n    var myObj = JSON.parse(event.data);\r\n    if (myObj.sliderValues) {\r\n      var sliderValues = myObj.sliderValues;\r\n      var keys = Object.keys(sliderValues);\r\n\r\n      for (var i = 0; i < keys.length; i++) {\r\n        var key = keys[i];\r\n        document.getElementById(key).innerHTML = sliderValues[key];\r\n        document.getElementById("slider" + (i + 1).toString()).value =\r\n          sliderValues[key];\r\n      }\r\n    }\r\n\r\n    if (myObj.servoParameter) {\r\n      var servoParameter = myObj.servoParameter;\r\n      var keys = Object.keys(servoParameter);\r\n      for (var i = 0; i < keys.length; i++) {\r\n         var key = keys[i];\r\n        k1 = servoParameter[key]["K1"];\r\n        k2 = servoParameter[key]["K2"];\r\n\r\n        document.getElementById("input" + key+"K1").value = k1\r\n        document.getElementById("input" + key+"K2").value = k2\r\n\r\n        console.log(key, k1,k2);\r\n      }\r\n\r\n    }\r\n  } else {\r\n    handleMessage(event.data);\r\n  }\r\n}\r\n\r\nfunction startReset(element) {\r\n  document.getElementById("modalResetBody").innerHTML =\r\n    \'Board is restarting, refresh page. This will take some time!<br><div class="spinner-border" role="status">  <span class="visually-hidden">Loading...</span></div>\';\r\n  console.log(element.id);\r\n  websocket.send("reset");\r\n  setTimeout(() => {\r\n    location.reload();\r\n  }, 10000);\r\n}\r\n\r\nfunction togglePower(element) {\r\n  console.log(element.id);\r\n  console.log(isOn);\r\n  if (isOn) {\r\n    websocket.send("armed&false");\r\n  } else {\r\n    websocket.send("armed&true");\r\n  }\r\n}\r\n\r\nfunction startAnimation(element) {\r\n  var btnAnimationNr = element.id.charAt(element.id.length - 1);\r\n  console.log("animation&"+ btnAnimationNr);\r\n  websocket.send("animation&"+ btnAnimationNr);\r\n}\r\n\r\nfunction validateForm() {\r\n  let Servos = [];\r\n  for (var i = 1; i < 8; i++) {\r\n    Servo = [];\r\n    Servo[0] = parseFloat(\r\n      document.getElementById("inputServo" + i + "K1").value\r\n    );\r\n    Servo[1] = parseFloat(\r\n      document.getElementById("inputServo" + i + "K2").value\r\n    );\r\n\r\n    Servos.push(Servo);\r\n\r\n    // console.log(Servos);\r\n  }\r\n\r\n  const servoParameter = {};\r\n\r\n  for (let i = 0; i < Servos.length; i++) {\r\n    const servoIndex = i + 1;\r\n    const servoKey = `Servo${servoIndex}`;\r\n    const [k1, k2] = Servos[i];\r\n\r\n    servoParameter[servoKey] = {\r\n      K1: k1,\r\n      K2: k2,\r\n    };\r\n  }\r\n\r\n  const result = {\r\n    servoParameter,\r\n  };\r\n\r\n  var jsonData = JSON.stringify(result);\r\n\r\n  websocket.send("settings&" + jsonData);\r\n  var xhr = new XMLHttpRequest();\r\n  xhr.open("GET", "/json?value=" + jsonData, true);\r\n  xhr.send();\r\n   window.location.href = \'/\';\r\n}\r\n\r\nfunction updateSliderPWM_6(element) {\r\n  var sliderValue = document.getElementById("pwmSliderServo_6").value;\r\n  document.getElementById("textSliderValueServo_6").innerHTML = sliderValue;\r\n  console.log(sliderValue);\r\n  var xhr = new XMLHttpRequest();\r\n  xhr.open("GET", "/servo6?value=" + sliderValue, true);\r\n  xhr.send();\r\n}\r\n\r\n     )=====";\n'})})]})}function u(e={}){const{wrapper:n}={...(0,o.R)(),...e.components};return n?(0,t.jsx)(n,{...e,children:(0,t.jsx)(d,{...e})}):d(e)}},8453:(e,n,r)=>{r.d(n,{R:()=>a,x:()=>i});var t=r(6540);const o={},s=t.createContext(o);function a(e){const n=t.useContext(s);return t.useMemo((function(){return"function"==typeof e?e(n):{...n,...e}}),[n,e])}function i(e){let n;return n=e.disableParentContext?"function"==typeof e.components?e.components(o):e.components||o:a(e.components),t.createElement(s.Provider,{value:n},e.children)}}}]);