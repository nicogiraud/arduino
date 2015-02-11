#arduino_Display

3 classes dédiées à l'exploitation des matrices de diode "i2c Led Backpack" fabriquées et commercialisées par Adafruit. Si Adafruit fournit d'excellentes [ressources pédagogiques](https://learn.adafruit.com/), des librairies et du code de qualité, l'idée est de proposer une alternative légère et rapide dédiée à l'exploitation de ses composants en production. Ainsi, un effort particulier est apporté à l'optimisation des performances et de l'emprunte mémoire des librairies.

####Support
Les librairies ont été testées sur les cartes suivantes :
- Adafruit Arduino Trinket Pro 5V
- Arduino Uno
- Arduino nano pro (chinois)

##Bitmap
Stockage et manipulation de données bitmap à 1 bit par pixel (monochrome)

##Matrix16x8
Communication i2c avec les matrices AdaFruit LED Backpack 16x8 pixels (http://www.adafruit.com/products/2044)

##Matrix8x8
Communication i2c avec les matrices AdaFruit LED Backpack 8x8 pixels (http://www.adafruit.com/products/1857)

##Font
Gestionnaire de fontes bitmap à chasse fixe (tous les caractères ont la même taille).

##Font3x8
Une typo 3x8 dédiée uniquement à l'affichage des chiffres de 0 à 9
