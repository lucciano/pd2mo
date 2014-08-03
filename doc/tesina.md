% Conversión de modelos PowerDEVS al lenguaje Modelica
% Tesinista: Luciano Andrade; Director: Federico Bergero, Co-Director: Ernesto Kofman

# Resumen #

# Introducción #
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
