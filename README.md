# Sistema de Control de Posición con Sensor Ultrasónico y Motor DC

## Descripción

Este proyecto implementa un sistema de control de posición utilizando un **sensor ultrasónico** (HC-SR04), un módulo puente H, dos **motores DC**, y un controlador basado en espacio de estados. El código está diseñado para plataformas **Arduino** y emplea temporización mediante la librería **TimerOne**.

---

## **Características del Sistema**

- **Sensor ultrasónico**: Mide la distancia respecto a un objetivo.
- **Controlador basado en estado**: Regula la posición del motor en función del error de distancia.
- **Temporización**: Se utiliza un temporizador de 10 ms (Timer1) para ejecutar el control de manera periódica.
- **Comunicaciones seriales**: Permite visualizar las variables de control y cambiar la distancia deseada.

---

## **Componentes y Conexiones**

| Componente             | Pin en Arduino | Descripción                  |
| ---------------------- | -------------- | ---------------------------- |
| **Sensor Ultrasónico** | TrigPin: 7     | Pin de activación del sensor |
|                        | EchoPin: 6     | Pin de recepción del pulso   |
| **Motor DC**           | IN3: 2         | Sentido de giro Motor B      |
|                        | IN4: 4         | Sentido de giro Motor B      |
|                        | ENB: 3         | Control de velocidad PWM     |

---

## **Dependencias**

- **Librería TimerOne**: Manejo del temporizador.
  - [Descargar TimerOne](https://github.com/PaulStoffregen/TimerOne)

---

## **Instalación y Uso**

1. **Clona el repositorio**:

   ```bash
   git clone https://github.com/tu-usuario/tu-repositorio.git
   ```

2. **Carga el código en la tarjeta Arduino**:

   - Abre el archivo en el IDE de Arduino.
   - Selecciona la placa correcta y el puerto serial.
   - Carga el programa.

3. **Uso mediante comunicación serial**:
   - Envía la letra **'A'** para ver las variables del sistema:
     - Distancia medida
     - Distancia deseada
     - Estados internos del controlador.
   - Envía la letra **'D'** seguido de un valor (0-255) para cambiar la distancia deseada.

---

## **Funcionamiento del Sistema**

1. El **sensor ultrasónico** mide la distancia actual (_distance1_).
2. Se calcula el error en los estados (_xa_ y _xb_) y se aplica un controlador de espacio de estados con ganancias `k_1` y `k_2`.
3. El control generado ajusta:
   - **Dirección del motor**: Adelante o atrás según el signo del error.
   - **Velocidad**: Proporcional al voltaje de control `u`, limitado entre 50 y 255 (PWM).
4. El sistema se ejecuta cada **10 ms** usando una interrupción de temporizador.

---

## **Variables Importantes**

| Variable            | Descripción                                  |
| ------------------- | -------------------------------------------- |
| `distance_setpoint` | Distancia objetivo (en cm)                   |
| `distance1`         | Distancia medida por el sensor ultrasónico   |
| `u`                 | Señal de control generada                    |
| `xa`, `xb`          | Estados del sistema (posiciones controladas) |
| `voltajebits`       | Valor de PWM aplicado al motor               |

---

## **Ejemplo de Salida Serial**

```plaintext
30.25 30.00 0.12 0.35
29.90 30.00 0.08 0.29
30.10 30.00 0.10 0.32
```

- **Primera columna**: Distancia actual medida.
- **Segunda columna**: Distancia deseada.
- **Tercera y cuarta columna**: Estados del sistema (xa y xb).

---

## **Pruebas y Resultados**

- **Configuración de prueba**: Distancia objetivo de 30 cm.
- **Resultados esperados**: El motor ajusta su velocidad y dirección para mantener la distancia medida cercana a la deseada.
- **Para una mejor visualización de los resultados, el proyecto puede integrarse con LabVIEW. El proceso es sencillo: se abre el archivo correspondiente, se selecciona el puerto serial al que está conectado el microcontrolador Arduino UNO, se establece un _SetPoint_ y se presiona _Start_. Una vez iniciado, el sistema comienza a funcionar y permite interactuar dinámicamente con la interfaz, observando en tiempo real la curva de respuesta y con la posibilidad de ajustar el _SetPoint_ en cualquier momento.**

---

## Créditos

Proyecto desarrollado como sexto laboratio de la asignatura Sistemas de Control Automático II del programa de Ingeniería Electrónica de la Universidad del Quindío.

Desarrollado por los estudiantes Daniel Alejandro Cangrejo López, Alvaro Sebástian Hernandez Ramirez y Andrea Carolina Soler.

##

Cualquier duda o mejora, ¡no dudes en contribuir! 🚀
