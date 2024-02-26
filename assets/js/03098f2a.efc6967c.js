"use strict";(self.webpackChunkrobo_control_web_socket=self.webpackChunkrobo_control_web_socket||[]).push([[912],{9938:(n,r,e)=>{e.r(r),e.d(r,{assets:()=>a,contentTitle:()=>i,default:()=>m,frontMatter:()=>s,metadata:()=>l,toc:()=>c});var t=e(4848),o=e(8453);const s={sidebar_position:2},i="settings_html.h",l={id:"web -files/settings_html_h",title:"settings_html.h",description:"",source:"@site/docs/02_web -files/settings_html_h.md",sourceDirName:"02_web -files",slug:"/web -files/settings_html_h",permalink:"/RoboControl_WebSocket/docs/web -files/settings_html_h",draft:!1,unlisted:!1,editUrl:"https://github.com/Praktikant-Klobuerste/RoboControl_WebSocket/tree/dev/docusaurus/RoboControl_WebSocket/docs/02_web -files/settings_html_h.md",tags:[],version:"current",sidebarPosition:2,frontMatter:{sidebar_position:2},sidebar:"tutorialSidebar",previous:{title:"html.h",permalink:"/RoboControl_WebSocket/docs/web -files/html_h"},next:{title:"css.h",permalink:"/RoboControl_WebSocket/docs/web -files/css_h"}},a={},c=[];function p(n){const r={code:"code",h1:"h1",pre:"pre",...(0,o.R)(),...n.components};return(0,t.jsxs)(t.Fragment,{children:[(0,t.jsx)(r.h1,{id:"settings_htmlh",children:"settings_html.h"}),"\n",(0,t.jsx)(r.pre,{children:(0,t.jsx)(r.code,{className:"language-c",children:'const char settings_html[] PROGMEM = R"rawliteral(\r\n    // html - file\r\n)rawliteral";\n'})}),"\n",(0,t.jsx)(r.pre,{children:(0,t.jsx)(r.code,{className:"language-html",children:'<!DOCTYPE html>\r\n<html lang="en">\r\n  <head>\r\n    <meta charset="UTF-8" />\r\n    <meta name="viewport" content="width=device-width, initial-scale=1.0" />\r\n    <title>Settings</title>\r\n    <link\r\n      href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css"\r\n      rel="stylesheet"\r\n      integrity="sha384-9ndCyUaIbzAi2FUVXJi0CjmCapSmO7SnpJef0486qhLnuZ2cdeRhO02iuK6FUUVM"\r\n      crossorigin="anonymous"\r\n    />\r\n    <meta charset="UTF-8" />\r\n    <meta name="viewport" content="width=device-width, initial-scale=1" />\r\n    \x3c!-- <link rel="icon" type="image/png" href="favicon.png"> --\x3e\r\n    <link rel="stylesheet" href="styles.css" />\r\n  </head>\r\n\r\n  <body style="background-color:#212529">\r\n    <a class="btn btn-delete" href="/" role="button">\u274c</a>\r\n    \x3c!-- Form --\x3e\r\n    <form name="servoParameter" class="mx-5">\r\n      <div class="servo-input-container">\r\n        <label for="inputServo1K1" class="form-label">Servo 1</label>\r\n\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo1K1"\r\n          value="0.10"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo1K2"\r\n          value="0.90"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n      </div>\r\n      <div class="servo-input-container">\r\n        <label for="inputServo2K1" class="form-label">Servo 2</label>\r\n\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo2K1"\r\n          value="0.10"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo2K2"\r\n          value="0.90"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n      </div>\r\n      <div class="servo-input-container">\r\n        <label for="inputServo3K1" class="form-label">Servo 3</label>\r\n\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo3K1"\r\n          value="0.10"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo3K2"\r\n          value="0.90"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n      </div>\r\n      <div class="servo-input-container">\r\n        <label for="inputServo4K1" class="form-label">Servo 4</label>\r\n\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo4K1"\r\n          value="0.10"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo4K2"\r\n          value="0.90"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n      </div>\r\n      <div class="servo-input-container">\r\n        <label for="inputServo5K1" class="form-label">Servo 5</label>\r\n\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo5K1"\r\n          value="0.10"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo5K2"\r\n          value="0.90"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n      </div>\r\n      <div class="servo-input-container">\r\n        <label for="inputServo6K1" class="form-label">Servo 6</label>\r\n\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo6K1"\r\n          value="0.10"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo6K2"\r\n          value="0.90"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n      </div>\r\n      <div class="servo-input-container">\r\n        <label for="inputServo7K1" class="form-label">Servo 7</label>\r\n\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo7K1"\r\n          value="0.10"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n        <input\r\n          type="number"\r\n          class="form-control"\r\n          id="inputServo7K2"\r\n          value="0.90"\r\n          min="0.00"\r\n          max="1.00"\r\n          step="0.05"\r\n        />\r\n      </div>\r\n    </form>\r\n    <button type="submit" class="btn btn-primary" onclick="validateForm()">\r\n      Submit\r\n    </button>\r\n\r\n    <script src="script.js"><\/script>\r\n    <script\r\n      src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js"\r\n      integrity="sha384-geWF76RCwLtnZ8qwWowPQNguL3RmwHVBC9FhGdlKrxdiJJigb/j/68SIy3Te4Bkz"\r\n      crossorigin="anonymous"\r\n    ><\/script>\r\n    <script>\r\n      const tooltipTriggerList = document.querySelectorAll(\r\n        \'[data-bs-toggle="tooltip"]\'\r\n      );\r\n      const tooltipList = [...tooltipTriggerList].map(\r\n        (tooltipTriggerEl) => new bootstrap.Tooltip(tooltipTriggerEl)\r\n      );\r\n    <\/script>\r\n  </body>\r\n</html>\n'})})]})}function m(n={}){const{wrapper:r}={...(0,o.R)(),...n.components};return r?(0,t.jsx)(r,{...n,children:(0,t.jsx)(p,{...n})}):p(n)}},8453:(n,r,e)=>{e.d(r,{R:()=>i,x:()=>l});var t=e(6540);const o={},s=t.createContext(o);function i(n){const r=t.useContext(s);return t.useMemo((function(){return"function"==typeof n?n(r):{...r,...n}}),[r,n])}function l(n){let r;return r=n.disableParentContext?"function"==typeof n.components?n.components(o):n.components||o:i(n.components),t.createElement(s.Provider,{value:r},n.children)}}}]);