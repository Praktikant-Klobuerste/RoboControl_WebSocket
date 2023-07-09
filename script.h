const char* script_js = R"=====(
     
var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
var isOn = true;
window.addEventListener("load", onload);

setTimeout(() => { function_body }, time in milliseconds);

function onload(event) {
   initWebSocket();
}

function getValues() {
   websocket.send("getValues");
}

function isJson(str) {
   try {
      JSON.parse(str);
   } catch (e) {
      return false;
   }
   return true;
}

function initWebSocket() {
   console.log("Trying to open a WebSocket connection…");
   websocket = new WebSocket(gateway);
   websocket.onopen = onOpen;
   websocket.onclose = onClose;
   websocket.onmessage = onMessage;
}

function handleMessage(data) {
   var message = data.split("&");
   var topic = message[0];
   var payload = message[1];
   console.log(topic, payload);

   // Power Button
   if (topic == "armed") {
      if (payload == "true") {
         isOn = true;
         document
            .getElementById("btnPower")
            .classList.replace("btn-outline-light", "btn-warning");
      } else {
         isOn = false;
         document
            .getElementById("btnPower")
            .classList.replace("btn-warning", "btn-outline-light");
      }
   }
}

function onOpen(event) {
   console.log("Connection opened");
   getValues();
}

function onClose(event) {
   console.log("Connection closed");
   setTimeout(initWebSocket, 2000);
}

function updateSliderPWM(element) {
   var sliderNumber = element.id.charAt(element.id.length - 1);
   var sliderValue = document.getElementById(element.id).value;
   document.getElementById("sliderValue" + sliderNumber).innerHTML =
      sliderValue;
   console.log(sliderValue);
   websocket.send(sliderNumber + "s" + sliderValue.toString());
}


function onMessage(event) {
   console.log(event.data);

   if (isJson(event.data)) {
      var myObj = JSON.parse(event.data);
      var keys = Object.keys(myObj);

      for (var i = 0; i < keys.length; i++) {
         var key = keys[i];
         document.getElementById(key).innerHTML = myObj[key];
         document.getElementById("slider" + (i + 1).toString()).value =
            myObj[key];
      }
   }
   else {
      handleMessage(event.data)
   }
}


function startReset(element) {
   document.getElementById("modalResetBody").innerHTML = 'Board is restarting, refresh page. This will take some time!<br><div class="spinner-border" role="status">  <span class="visually-hidden">Loading...</span></div>'
   console.log(element.id);
   websocket.send("reset");
   setTimeout(() => {
      location.reload();
   }
      , 10000);

}

function togglePower(element) {
   console.log(element.id);
   console.log(isOn);
   if (isOn) {
      websocket.send("armed&false");
   } else {
      websocket.send("armed&true");
   }
}

function startAnimation(element) {
   console.log(element.id);
   websocket.send("animation");
}

function validateForm() {
   let Servos = [];
   for (var i = 1; i < 8; i++) {
      Servo = [];
      Servo[0] = parseFloat(document.getElementById("inputServo" + i + "K1").value);
      Servo[1] = parseFloat(document.getElementById("inputServo" + i + "K2").value);

      Servos.push(Servo);

      // console.log(Servos);
   }
   const convertedData = {};
   Servos.forEach((item, index) => {
      const servoName = "Servo" + (index + 1);
      convertedData[servoName] = {
         K1: item[0],
         K2: item[1]
      };
   });

   const jsonData = JSON.stringify(convertedData);

   console.log(jsonData);
   websocket.send(jsonData);
}
     )=====";