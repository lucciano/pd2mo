% Conversión de modelos PowerDEVS al lenguaje Modelica
% Tesinista: Luciano Andrade; Director: Federico Bergero, Co-Director: Ernesto Kofman

# Resumen #

En este trabajo se descrive la implementación de una aplicación capaz de convertir modelos descriptos en la herramienta PowerDEVS a modelos en el Modelica, más especificamente en µModelica, con el fin de aprobechar la velocidad de simulación del '''QSS Solver''' y aprobechar su velocidad de simulación, permitiendo describir las simulaciones en el entorno PowerDEVS.

# Introducción #
Hola [@Fer12] .
## Motivación y Objetivos ##
## Trabajo relacionado ##
## Alcance ##

# Conceptos Previos #
## Modelado y Simulación ##
### Sistemas Continuos y Discretos ###
### Métodos de Integración numérica ###
## Formalismo DEVS ##
### Atómicos ###
### Acoplados ###
Equivalencia entre atómicos y acoplados.

## Métodos de integración de QSS ##
## PowerDEVS ##
### Modelos Vectoriales ###
## Modelica ##
## QSS Stand Alone Solver ##
### µ-Modelica ###

# Conversión de modelos DEVS #
## Modelos Atómicos ##
Cómo se traducen (es conocimiento del modelador, no automático)
## Modelos Vectoriales ##
?

## Modelos Acoplados Planos ##
Modelos acoplados solo con modelos atómicos adentro.

Mencionar el algoritmo (traducción de conexiones y ``aplanado'' de cada uno de los atómicos hijos``)	

## Equivalencia semántica de la conversión ##

# Modelos Acoplados Jerárquicos #
Explicar cuándo se utilzan y que resolvemos el problema aplanando los acoplados

## Algoritmo de aplanado ##
Describir el algoritmo para PDS

## Comparación de performance ##

# Detalles de Implementación #

# Ejemplos de Aplicación #
## Vector/airs ##
## Vector/lcline ##

# Conclusiones y Trabajo a futuro #

# Bibliografía #
