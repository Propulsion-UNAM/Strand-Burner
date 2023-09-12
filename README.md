# Strand Burner

Código para de el Strand Burner para Windows.

Esta Documentación está **muy** simplificada, para pasos más detallados dirígete a esta [otra documentación](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf), específicamente las páginas 39-41. 

-------------------------------

## El SDK de la Raspberry Pi Pico

Se encuentra en este [repositorio](https://github.com/raspberrypi/pico-sdk) y nos proporciona herramientas para poder programar la Raspberry Pi Pico en C.

Aunque el archivo que necesitamos ([pico_sdk_import.cmake](pico_sdk_import.cmake)) ya se encuentra en este repositorio, no está de más clonar el sdk.

## Instalación del Toolchain

Dirigirse a este [repositorio](https://github.com/raspberrypi/pico-setup-windows) y descargar la [versión más nueva](https://github.com/raspberrypi/pico-setup-windows/releases/latest/download/pico-setup-windows-x64-standalone.exe). Ejecuta el instalador y sigue los pasos para que se instale todo el software.

## Configuración y Compilación del proyecto

Abrir **Pico - Visual Studio Code** desde el explorador de Windows y dentro de VSCode abrir la carpeta del proyecto.

Debido a los archivos incluidos en [.vscode](.vscode), la configuración del proyecto debería hacerse de forma automática.

Para poder compilar el proyecto, abrir la extensión de CMake en la barra lateral izquierda de VSCode, seleccionar el proyecto *sb* y hacer click en *Build*.

## Archivo uf2

El archivo que subiremos a la Raspberry es el generado dentro de *build/sb/sb.uf2*, para subirlo tienes que conectar la Raspberry manteniendo presionado el botón de BOOTSEL, al abrirse el explorador de archivos puedes copiar el uf2 dentro de la Raspberry, el explorador debería cerrarse y el programa debería ejecutarse.