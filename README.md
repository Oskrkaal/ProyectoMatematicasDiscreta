# Analizador y Optimizador de Grafos Dirigidos 🧭

## Descripción
Este proyecto es una herramienta desarrollada en C++ que modela interconexiones, redes y mapas de transición utilizando la **Teoría de Grafos**. Permite ingresar dinámicamente vértices y conexiones direccionales ponderadas (con pesos positivos) para abstraer mapas virtuales, y utiliza algoritmos de exploración profunda para encontrar todas las rutas viables entre dos puntos.

## Puntos Claves del Desarrollo
* **Estructuras Dinámicas:** Implementado 100% con `std::vector`, asegurando eficiencia espacial en tiempo de ejecución y evitando el uso de datos en código duro (*hardcoding*).
* **Matriz de Adyacencia:** Garantiza consultas de conexión entre nodos en un tiempo óptimo de $O(1)$.
* **Búsqueda Exhaustiva (DFS + Backtracking):** Algoritmo recursivo a prueba de bucles cerrados que aísla de manera precisa todos los caminos simples viables en topologías de red complejas.
* **Sistema de Optimización Analítico:** Recolecta métricas de todas las ramas exploradas para discernir de forma autónoma cuál es el **Camino Más Corto** (Ideal para ahorro logístico) y el **Camino Más Largo** (Ideal para identificación de rutas críticas).
* **Interacción Guiada y Segura:** Incluye validaciones robustas frente a valores nulos o dimensiones incoherentes (pesos <= 0, grafos de un solo nodo, etc).

## ¿Para qué sirve este código?
1. **Logística y Transporte:** Calcular la ruta más eficiente (menor distancia, gasto o tiempo) para el envío de mercancías entre almacenes.
2. **Redes de Telecomunicaciones:** Encontrar los trayectos de enrutamiento con menor latencia para el envío de paquetes de datos entre servidores.
3. **Gestión de Proyectos (Ruta Crítica):** Al encontrar el camino más largo (máximo), permite a administradores prever el tiempo máximo que podría tomar una red de tareas secuenciales.
4. **Base Académica:** Excelente recurso para estudiantes de Ciencias de la Computación o Ingeniería en Sistemas que busquen comprender visualmente cómo operan la recursividad y el *Backtracking*.
