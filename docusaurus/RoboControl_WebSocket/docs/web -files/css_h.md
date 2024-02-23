---
sidebar_position: 3
---

# css.h

```c
const char* styles_css = R"=====(
    //css file
)=====";
```

```css
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

.servo-input-container {
  max-width: 400px;
  margin: 4rem auto;
}

.form-label {
  margin: 0;
}
```
