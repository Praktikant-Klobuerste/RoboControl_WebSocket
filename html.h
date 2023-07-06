const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
   <title>Robo - Control</title>
   <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet"
      integrity="sha384-9ndCyUaIbzAi2FUVXJi0CjmCapSmO7SnpJef0486qhLnuZ2cdeRhO02iuK6FUUVM" crossorigin="anonymous" />
   <meta name="viewport" content="width=device-width, initial-scale=1" />
   <!-- <link rel="icon" type="image/png" href="favicon.png"> -->
   <style>
      html {
         font-family: Arial, Helvetica, sans-serif;
         display: inline-block;
         text-align: center;
      }

      p {
         font-size: 1.4rem;
      }

      body {
         margin: 0;
      }

      .content {
         padding: 30px;
      }

      .title {
         font-size: 1.8rem;
         color: white;
      }

      .card-grid {
         max-width: 700px;
         margin: 0 auto;
         display: grid;
         grid-gap: 2rem;
         grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
      }

      .card-element {
         background-color: white;
         box-shadow: 2px 2px 12px 1px rgba(140, 140, 140, 0.5);
      }

      .card-title {
         font-size: 1.2rem;
         font-weight: bold;
         color: #034078;
         padding: 20px 5px 5px;
      }

      .state {
         font-size: 1.2rem;
         color: #1282a2;
      }

      .slider {
         -webkit-appearance: none;
         margin: 0 auto;
         width: 100%;
         height: 10px;
         background: #ffd65c;
         outline: none;
         -webkit-transition: 0.2s;
         transition: opacity 0.2s;
      }

      .slider::-webkit-slider-thumb {
         -webkit-appearance: none;
         appearance: none;
         width: 25px;
         height: 25px;
         border-radius: 10%;
         background: #003249;
         cursor: pointer;
      }

      .slider::-moz-range-thumb {
         width: 25px;
         height: 25px;
         background: #003249;
         cursor: pointer;
      }

      .switch {
         padding-left: 5%;
         padding-right: 5%;
      }

      .navbar-nav {
         display: inline;
      }

      .nav-item {
         display: inline;
      }

      .btn-delete {
         --bs-btn-font-weight: 600;
         --bs-btn-color: rgb(248, 183, 245);
         --bs-btn-bg: purple;
         --bs-btn-border-color: rgb(88, 0, 88);
         --bs-btn-border-radius: 0.5rem;
         --bs-btn-hover-color: white;
         --bs-btn-hover-bg: rgb(226, 4, 4);
         /* --bs-btn-hover-bg: rgb(70, 1, 70); */
      }

      .model-paragraph {
         font-size: 1rem;
      }
   </style>
</head>

<body>
   <nav class="navbar bg-dark border-bottom border-bottom-dark" data-bs-theme="dark">
      <h1 class="title mx-3 my-2">Robo - Control</h1>
      <ul class="navbar-nav mx-4 topnav">
         <li class="nav-item">
            <button id="btnPower" class="btn btn-warning" onclick="togglePower(this)">
               Power
            </button>
         </li>
         <li class="nav-item">
            <button class="btn btn-outline-light" type="button" data-bs-toggle="offcanvas"
               data-bs-target="#offcanvasWithBothOptions" aria-controls="offcanvasWithBothOptions">
               🎈
            </button>
         </li>
         <!-- Modal button -->
         <li class="nav-item">
            <button id="btnReset" class="btn btn-outline-danger" data-bs-toggle="modal" data-bs-target="#modalReset">
               Restart
            </button>
         </li>
      </ul>
   </nav>

   <!-- offcanvas -->
   <div class="offcanvas offcanvas-start text-bg-dark" data-bs-scroll="true" tabindex="-1" id="offcanvasWithBothOptions"
      aria-labelledby="offcanvasWithBothOptionsLabel">
      <div class="offcanvas-header">
         <h3 class="offcanvas-title" id="offcanvasWithBothOptionsLabel">
            Animationen
         </h3>
         <button type="button" class="btn-close btn-close-white" data-bs-dismiss="offcanvas"
            aria-label="Close"></button>
      </div>
      <div class="offcanvas-body">
         <button id="btnAnimation" class="btn btn-secondary btn-lg" onclick="startAnimation(this)"
            data-bs-toggle="tooltip" data-bs-placement="right" data-bs-title="Start Animation">
            Eye
         </button>
      </div>
   </div>


   <!-- Modal Bestellungen löschen-->
   <div class="modal fade" id="modalReset" data-bs-backdrop="static" data-bs-keyboard="false" tabindex="-1"
      aria-labelledby="modalResetLabel" aria-hidden="true">
      <div class="modal-dialog">
         <div class="modal-content">
            <div class="modal-header">
               <h1 class="modal-title fs-5" id="modalResetLabel">
                  Restart Robo
               </h1>
               <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
            </div>
            <div class="modal-body" id="modalResetBody">
               <p class="model-paragraph">You are about to restart the Robo!</p>
               <p class="model-paragraph">Axis will go to initial posistion.</p>
            </div>
            <div class="modal-footer">
               <button class="btn btn-delete" type="button" data-bs-toggle="tooltip" data-bs-placement="bottom"
                  onclick="startReset(this)" data-bs-title="Are you sure?">
                  Restart
               </button>
               <button type="button" class="btn btn-outline-dark" data-bs-dismiss="modal">
                  Cancel
               </button>
            </div>
         </div>
      </div>
   </div>

   <div class="content">
      <div class="card-grid">
         <div class="card-element">
            <p class="card-title">Servo 1</p>
            <p class="switch">
               <input type="range" onchange="updateSliderPWM(this)" id="slider1" min="60" max="150" step="1" value="0"
                  class="slider" />
            </p>
            <p class="state">Angle: <span id="sliderValue1"></span></p>
         </div>
         <div class="card-element">
            <p class="card-title">Servo 2</p>
            <p class="switch">
               <input type="range" onchange="updateSliderPWM(this)" id="slider2" min="60" max="105" step="1" value="0"
                  class="slider" />
            </p>
            <p class="state">Angle: <span id="sliderValue2"></span></p>
         </div>
         <div class="card-element">
            <p class="card-title">Servo 3</p>
            <p class="switch">
               <input type="range" onchange="updateSliderPWM(this)" id="slider3" min="50" max="140" step="1" value="0"
                  class="slider" />
            </p>
            <p class="state">Angle: <span id="sliderValue3"></span></p>
         </div>
         <div class="card-element">
            <p class="card-title">Servo 4</p>
            <p class="switch">
               <input type="range" onchange="updateSliderPWM(this)" id="slider4" min="120" max="170" step="1" value="0"
                  class="slider" />
            </p>
            <p class="state">Angle: <span id="sliderValue4"></span></p>
         </div>
         <div class="card-element">
            <p class="card-title">Servo 5</p>
            <p class="switch">
               <input type="range" onchange="updateSliderPWM(this)" id="slider5" min="0" max="180" step="1" value="0"
                  class="slider" />
            </p>
            <p class="state">Angle: <span id="sliderValue5"></span></p>
         </div>
         <div class="card-element">
            <p class="card-title">Servo 6</p>
            <p class="switch">
               <input type="range" onchange="updateSliderPWM(this)" id="slider6" min="0" max="180" step="1" value="0"
                  class="slider" />
            </p>
            <p class="state">Angle: <span id="sliderValue6"></span></p>
         </div>
         <div class="card-element">
            <p class="card-title">Servo 7</p>
            <p class="switch">
               <input type="range" onchange="updateSliderPWM(this)" id="slider7" min="10" max="180" step="1" value="0"
                  class="slider" />
            </p>
            <p class="state">Angle: <span id="sliderValue7"></span></p>
         </div>
      </div>
   </div>

   <script>
      var gateway = `ws://${window.location.hostname}/ws`;
      var websocket;
      var isOn = true;
      window.addEventListener("load", onload);

      setTimeout(()=>{function_body}, time in milliseconds);

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
         else 
         {
            handleMessage(event.data)
         }
      }


      function startReset(element) {
         document.getElementById("modalResetBody").textContent = "Board is restarting, refresh page. This will take some time!";
         console.log(element.id);
         websocket.send("reset");
         setTimeout(()=> {
            location.reload();
      }
      ,10000);
         
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
   </script>
   <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js"
      integrity="sha384-geWF76RCwLtnZ8qwWowPQNguL3RmwHVBC9FhGdlKrxdiJJigb/j/68SIy3Te4Bkz"
      crossorigin="anonymous"></script>
   <script>
      const tooltipTriggerList = document.querySelectorAll(
         '[data-bs-toggle="tooltip"]'
      );
      const tooltipList = [...tooltipTriggerList].map(
         (tooltipTriggerEl) => new bootstrap.Tooltip(tooltipTriggerEl)
      );
   </script>
</body>

</html>

  )rawliteral";