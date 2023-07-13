const char settings_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Settings</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet"
        integrity="sha384-9ndCyUaIbzAi2FUVXJi0CjmCapSmO7SnpJef0486qhLnuZ2cdeRhO02iuK6FUUVM" crossorigin="anonymous" />
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <!-- <link rel="icon" type="image/png" href="favicon.png"> -->
    <link rel="stylesheet" href="styles.css" />
</head>

<body style="background-color:#212529">
    <a class="btn btn-delete" href="/" role="button">❌</a>
    <!-- Form -->
    <form name="servoParameter" class="mx-5">
        <div class="servo-input-container">
            <label for="inputServo1K1" class="form-label">Servo 1</label>

            <input type="number" class="form-control" id="inputServo1K1" value="0.10" min="0.00" max="1.00"
                step="0.05" />
            <input type="number" class="form-control" id="inputServo1K2" value="0.90" min="0.00" max="1.00"
                step="0.05" />
        </div>
        <div class="servo-input-container">
            <label for="inputServo2K1" class="form-label">Servo 2</label>

            <input type="number" class="form-control" id="inputServo2K1" value="0.10" min="0.00" max="1.00"
                step="0.05" />
            <input type="number" class="form-control" id="inputServo2K2" value="0.90" min="0.00" max="1.00"
                step="0.05" />
        </div>
        <div class="servo-input-container">
            <label for="inputServo3K1" class="form-label">Servo 3</label>

            <input type="number" class="form-control" id="inputServo3K1" value="0.10" min="0.00" max="1.00"
                step="0.05" />
            <input type="number" class="form-control" id="inputServo3K2" value="0.90" min="0.00" max="1.00"
                step="0.05" />
        </div>
        <div class="servo-input-container">
            <label for="inputServo4K1" class="form-label">Servo 4</label>

            <input type="number" class="form-control" id="inputServo4K1" value="0.10" min="0.00" max="1.00"
                step="0.05" />
            <input type="number" class="form-control" id="inputServo4K2" value="0.90" min="0.00" max="1.00"
                step="0.05" />
        </div>
        <div class="servo-input-container">
            <label for="inputServo5K1" class="form-label">Servo 5</label>

            <input type="number" class="form-control" id="inputServo5K1" value="0.10" min="0.00" max="1.00"
                step="0.05" />
            <input type="number" class="form-control" id="inputServo5K2" value="0.90" min="0.00" max="1.00"
                step="0.05" />
        </div>
        <div class="servo-input-container">
            <label for="inputServo6K1" class="form-label">Servo 6</label>

            <input type="number" class="form-control" id="inputServo6K1" value="0.10" min="0.00" max="1.00"
                step="0.05" />
            <input type="number" class="form-control" id="inputServo6K2" value="0.90" min="0.00" max="1.00"
                step="0.05" />
        </div>
        <div class="servo-input-container">
            <label for="inputServo7K1" class="form-label">Servo 7</label>

            <input type="number" class="form-control" id="inputServo7K1" value="0.10" min="0.00" max="1.00"
                step="0.05" />
            <input type="number" class="form-control" id="inputServo7K2" value="0.90" min="0.00" max="1.00"
                step="0.05" />
        </div>

    </form>
        <button type="submit" class="btn btn-primary" onclick="validateForm()">
            Submit
        </button>

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