const char* script_js = R"=====(
var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
var isOn = true;
window.addEventListener("load", onload);

setTimeout(() => {
  function_body;
}, time in milliseconds);

// // Elemente aus dem DOM abrufen
// const inputK1 = document.getElementById("inputServo1K1");
// const inputK2 = document.getElementById("inputServo1K2");

// // Event Listener hinzufügen
// inputK1.addEventListener("change", updateKValues);
// inputK2.addEventListener("change", updateKValues);

// // Funktion zur Aktualisierung der K-Werte
// function updateKValues() {
//    console.log("Updating")
//   const valueK1 = parseFloat(inputK1.value);
//   const valueK2 = parseFloat(inputK2.value);

//   // Prüfen, ob die Summe von K1 und K2 1.00 ergibt
//   if (valueK1 + valueK2 !== 1.00) {
//     // Anpassung der Werte
//     inputK1.value = (1.00 - valueK2).toFixed(2);
//   }
// }

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
  document.getElementById("sliderValue" + sliderNumber).innerHTML = sliderValue;
  console.log(sliderValue);
  websocket.send(sliderNumber + "s" + sliderValue.toString());
}

function onMessage(event) {
  console.log(event.data);

  if (isJson(event.data)) {
    var myObj = JSON.parse(event.data);
    if (myObj.sliderValues) {
      var sliderValues = myObj.sliderValues;
      var keys = Object.keys(sliderValues);

      for (var i = 0; i < keys.length; i++) {
        var key = keys[i];
        document.getElementById(key).innerHTML = sliderValues[key];
        document.getElementById("slider" + (i + 1).toString()).value =
          sliderValues[key];
      }
    }

    if (myObj.servoParameter) {
      var servoParameter = myObj.servoParameter;
      var keys = Object.keys(servoParameter);
      for (var i = 0; i < keys.length; i++) {
         var key = keys[i];
        k1 = servoParameter[key]["K1"];
        k2 = servoParameter[key]["K2"];

        document.getElementById("input" + key+"K1").value = k1
        document.getElementById("input" + key+"K2").value = k2
      
        console.log(key, k1,k2);
      }
      
    }
  } else {
    handleMessage(event.data);
  }
}

function startReset(element) {
  document.getElementById("modalResetBody").innerHTML =
    'Board is restarting, refresh page. This will take some time!<br><div class="spinner-border" role="status">  <span class="visually-hidden">Loading...</span></div>';
  console.log(element.id);
  websocket.send("reset");
  setTimeout(() => {
    location.reload();
  }, 10000);
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
  var btnAnimationNr = element.id.charAt(element.id.length - 1);
  console.log("animation&"+ btnAnimationNr);
  websocket.send("animation&"+ btnAnimationNr);
}

function validateForm() {
  let Servos = [];
  for (var i = 1; i < 8; i++) {
    Servo = [];
    Servo[0] = parseFloat(
      document.getElementById("inputServo" + i + "K1").value
    );
    Servo[1] = parseFloat(
      document.getElementById("inputServo" + i + "K2").value
    );

    Servos.push(Servo);

    // console.log(Servos);
  }

  const servoParameter = {};

  for (let i = 0; i < Servos.length; i++) {
    const servoIndex = i + 1;
    const servoKey = `Servo${servoIndex}`;
    const [k1, k2] = Servos[i];

    servoParameter[servoKey] = {
      K1: k1,
      K2: k2,
    };
  }

  const result = {
    servoParameter,
  };

  var jsonData = JSON.stringify(result);

  websocket.send("settings&" + jsonData);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/json?value=" + jsonData, true);
  xhr.send();
   window.location.href = '/';
}

function updateSliderPWM_6(element) {
  var sliderValue = document.getElementById("pwmSliderServo_6").value;
  document.getElementById("textSliderValueServo_6").innerHTML = sliderValue;
  console.log(sliderValue);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/servo6?value=" + sliderValue, true);
  xhr.send();
}

     )=====";