const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
   <title>Robo - Control</title>
   <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet"
      integrity="sha384-9ndCyUaIbzAi2FUVXJi0CjmCapSmO7SnpJef0486qhLnuZ2cdeRhO02iuK6FUUVM" crossorigin="anonymous" />
      <meta charset="UTF-8">
   <meta name="viewport" content="width=device-width, initial-scale=1" />
   <!-- <link rel="icon" type="image/png" href="favicon.png"> -->
   <link rel="stylesheet" href="styles.css">
</head>

<body>
   <nav class="navbar bg-dark border-bottom border-bottom-dark" data-bs-theme="dark">
      <h1 class="title mx-3 my-2">Robo - Control</h1>
      <ul class="navbar-nav mx-4 topnav">
         <!-- Settings Modal button -->
         <li class="nav-item">
            <a class="btn btn-outline-light"  id="btnSettings" href="settings" role="button">Settings</a>
         </li>
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


   <!-- Modal Reset Robot-->
   <section class="modal fade" id="modalReset" data-bs-backdrop="static" data-bs-keyboard="false" tabindex="-1"
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
               <p class="model-paragraph">Axis will go to initial position.</p>
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
   </section>


   <section class="content">
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
   </section>

   <script src="script.js"></script>
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