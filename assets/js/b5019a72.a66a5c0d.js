"use strict";(self.webpackChunkrobo_control_web_socket=self.webpackChunkrobo_control_web_socket||[]).push([[204],{5114:(e,n,r)=>{r.r(n),r.d(n,{assets:()=>c,contentTitle:()=>s,default:()=>d,frontMatter:()=>o,metadata:()=>l,toc:()=>a});var i=r(4848),t=r(8453);const o={sidebar_position:2},s="filesystem.h",l={id:"c-files/filesystem_h",title:"filesystem.h",description:"",source:"@site/docs/01_c-files/filesystem_h.md",sourceDirName:"01_c-files",slug:"/c-files/filesystem_h",permalink:"/RoboControl_WebSocket/docs/c-files/filesystem_h",draft:!1,unlisted:!1,editUrl:"https://github.com/Praktikant-Klobuerste/RoboControl_WebSocket/tree/dev/docusaurus/RoboControl_WebSocket/docs/01_c-files/filesystem_h.md",tags:[],version:"current",sidebarPosition:2,frontMatter:{sidebar_position:2},sidebar:"tutorialSidebar",previous:{title:"RoboControl.ino",permalink:"/RoboControl_WebSocket/docs/c-files/RoboControl_ino"},next:{title:"secrets.h",permalink:"/RoboControl_WebSocket/docs/c-files/secrets_h"}},c={},a=[];function f(e){const n={code:"code",h1:"h1",pre:"pre",...(0,t.R)(),...e.components};return(0,i.jsxs)(i.Fragment,{children:[(0,i.jsx)(n.h1,{id:"filesystemh",children:"filesystem.h"}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",children:'#include <ArduinoJson.h>\r\n#include "LittleFS.h"\n'})}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",children:"StaticJsonDocument<512> config;\n"})}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",children:'void writeFile(fs::FS &fs, const char *path, const char *message, const char *mode) {\r\n  Serial.printf("\\nWriting file: %s\\r\\n", path);\r\n\r\n  File file = fs.open(path, mode);\r\n  if (!file) {\r\n    Serial.println("- failed to open file for writing");\r\n    return;\r\n  }\r\n  if (file.print(message)) {\r\n    Serial.println("- file written");\r\n  } else {\r\n    Serial.println("- write failed");\r\n  }\r\n  file.close();\r\n}\n'})}),"\n",(0,i.jsx)(n.pre,{children:(0,i.jsx)(n.code,{className:"language-c",children:'bool loadFile(fs::FS &fs, const char *path)\r\n// Load existing configuration file\r\n{\r\n  String input;\r\n\r\n  if (fs.exists(path)) {\r\n    // The file exists, reading and loading\r\n    Serial.printf("\\nreading File: %s\\n", path);\r\n    File file = fs.open(path, "r");\r\n    if (file) {\r\n      Serial.println("Opening file:");\r\n\r\n      while (file.available()) {\r\n        char intRead = file.read();\r\n        input += intRead;\r\n      }\r\n\r\n      DeserializationError error = deserializeJson(config, input);\r\n      file.close();\r\n\r\n      if (!error) {\r\n        serializeJsonPretty(config, Serial);\r\n\r\n        return true;\r\n      } else {\r\n        Serial.print(F("deserializeJson() failed: "));\r\n        Serial.println(error.f_str());\r\n      }\r\n    } else {\r\n      Serial.println("Failed to open file for reading");\r\n    }\r\n  }\r\n  return false;\r\n}\n'})})]})}function d(e={}){const{wrapper:n}={...(0,t.R)(),...e.components};return n?(0,i.jsx)(n,{...e,children:(0,i.jsx)(f,{...e})}):f(e)}},8453:(e,n,r)=>{r.d(n,{R:()=>s,x:()=>l});var i=r(6540);const t={},o=i.createContext(t);function s(e){const n=i.useContext(o);return i.useMemo((function(){return"function"==typeof e?e(n):{...n,...e}}),[n,e])}function l(e){let n;return n=e.disableParentContext?"function"==typeof e.components?e.components(t):e.components||t:s(e.components),i.createElement(o.Provider,{value:n},e.children)}}}]);