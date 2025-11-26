# my_arduino_project

Proyecto basado en **ESP-IDF + Arduino como componente**, organizado en módulos y compilado con la estructura oficial de Espressif.

## 🧰 Tecnologías utilizadas
- ESP-IDF v5.x
- Arduino como componente (managed components)
- CMake
- VS Code (Extensión ESP-IDF)

## 📂 Estructura del proyecto
my_arduino_project/
├── CMakeLists.txt
├── main/
│ ├── main.cpp
│ └── CMakeLists.txt
├── components/
│ └── wifi_module/
│ ├── wifi_module.cpp
│ └── CMakeLists.txt
└── managed_components/

## 🚀 Cómo compilar
idf.py build
idf.py flash monitor

## 📡 Características del proyecto

Integración completa de Arduino dentro de ESP-IDF

Código modular en archivos .h y .cpp

Preparado para WiFi, sensores, Firebase, etc.

## 📜 Licencia

MIT
