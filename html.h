const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
   <head>
      <title>Robo - Control</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <!-- <link rel="icon" type="image/png" href="favicon.png"> -->
      <style>
         html {
         font-family: Arial, Helvetica, sans-serif;
         display: inline-block;
         text-align: center;
         }
         h1 {
         font-size: 1.8rem;
         color: white;
         }
         p {
         font-size: 1.4rem;
         }
         .topnav {
         overflow: hidden;
         background-color: #0A1128;
         }
         body {
         margin: 0;
         }
         .content {
         padding: 30px;
         }
         .card-grid {
         max-width: 700px;
         margin: 0 auto;
         display: grid;
         grid-gap: 2rem;
         grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
         }
         .card {
         background-color: white;
         box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
         }
         .card-title {
         font-size: 1.2rem;
         font-weight: bold;
         color: #034078
         }
         .state {
         font-size: 1.2rem;
         color:#1282A2;
         }
         .slider { 
         -webkit-appearance: none;
         margin: 0 auto;
         width: 100%;
         height: 10px;
         background: #FFD65C;
         outline: none;
         -webkit-transition: .2s;
         transition: opacity .2s;}

         .slider::-webkit-slider-thumb {
         -webkit-appearance: none;
         appearance: none; width: 25px;
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
      </style>
   </head>

   <body>
      <div class="topnav">
         <h1>Robo - Control</h1>
      </div>
      <div class="content">
         <div class="card-grid">
            <div class="card">
               <p class="card-title">Servo 1</p>
               <p class="switch">
                  <input type="range" onchange="updateSliderPWM(this)" id="slider1" min="30" max="130" step="1" value ="0" class="slider">
               </p>
               <p class="state">Angle: <span id="sliderValue1"></span></p>
            </div>
            <div class="card">
               <p class="card-title"> Servo 2</p>
               <p class="switch">
                  <input type="range" onchange="updateSliderPWM(this)" id="slider2" min="80" max="140" step="1" value ="0" class="slider">
               </p>
               <p class="state">Angle: <span id="sliderValue2"></span></p>
            </div>
            <div class="card">
               <p class="card-title"> Servo 3</p>
               <p class="switch">
                  <input type="range" onchange="updateSliderPWM(this)" id="slider3" min="70" max="170" step="1" value ="0" class="slider">
               </p>
               <p class="state">Angle: <span id="sliderValue3"></span></p>
            </div>
            <div class="card">
               <p class="card-title"> Servo 4</p>
               <p class="switch">
                  <input type="range" onchange="updateSliderPWM(this)" id="slider4" min="25" max="75" step="1" value ="0" class="slider">
               </p>
               <p class="state">Angle: <span id="sliderValue4"></span></p>
            </div>
            <div class="card">
               <p class="card-title"> Servo 5</p>
               <p class="switch">
                  <input type="range" onchange="updateSliderPWM(this)" id="slider5" min="0" max="180" step="1" value ="0" class="slider">
               </p>
               <p class="state">Angle: <span id="sliderValue5"></span></p>
            </div>
            <div class="card">
               <p class="card-title"> Servo 6</p>
               <p class="switch">
                  <input type="range" onchange="updateSliderPWM(this)" id="slider6" min="0" max="180" step="1" value ="0" class="slider">
               </p>
               <p class="state">Angle: <span id="sliderValue6"></span></p>
            </div>
            <div class="card">
               <p class="card-title"> Servo 7</p>
               <p class="switch">
                  <input type="range" onchange="updateSliderPWM(this)" id="slider7" min="10" max="180" step="1" value ="0" class="slider">
               </p>
               <p class="state">Angle: <span id="sliderValue7"></span></p>
            </div>
         </div>
      </div>


      <script>
         var gateway = `ws://${window.location.hostname}/ws`;
         var websocket;
         window.addEventListener('load', onload);
         
         function onload(event) {
         initWebSocket();
         }
         
         function getValues(){
         websocket.send("getValues");
         }
         
         function initWebSocket() {
         console.log('Trying to open a WebSocket connection…');
         websocket = new WebSocket(gateway);
         websocket.onopen = onOpen;
         websocket.onclose = onClose;
         websocket.onmessage = onMessage;
         }
         
         function onOpen(event) {
         console.log('Connection opened');
         getValues();
         }
         
         function onClose(event) {
         console.log('Connection closed');
         setTimeout(initWebSocket, 2000);
         }
         
         function updateSliderPWM(element) {
         var sliderNumber = element.id.charAt(element.id.length-1);
         var sliderValue = document.getElementById(element.id).value;
         document.getElementById("sliderValue"+sliderNumber).innerHTML = sliderValue;
         console.log(sliderValue);
         websocket.send(sliderNumber+"s"+sliderValue.toString());
         }
         
         function onMessage(event) {
         console.log(event.data);
         var myObj = JSON.parse(event.data);
         var keys = Object.keys(myObj);
         
         for (var i = 0; i < keys.length; i++){
         var key = keys[i];
         document.getElementById(key).innerHTML = myObj[key];
         document.getElementById("slider"+ (i+1).toString()).value = myObj[key];
         }
         }
      </script>
   </body>
</html>

  )rawliteral";