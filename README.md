# snake-arduino

Game description:

Snake is one of the most renowned games due to its simplicity. The user is able to control a snake towards different points on a map. Once the snake eats some prizes its total size increases. The purpose of the game is to get the snake as big as possible. The game is lost whenever the head of the snake hits the rest of its body.

Hardware: 
  
  The game runs on a LED 8x8 matrix which is connected to an Arduino Uno board with a MAX7129 driver. Besides the matrix, the user has access to a joystick to control the movement of the snake and to start a new game. The led interface handles the notification system throughout the game

Software:
  
  The software is written in C and is decoupled into separate actions as much as possible. The movement of the snake is simulated by erasing the current state of the map and creating a new one at every 0.5 seconds. This delay is decreased progressively as the snake gets bigger to increase difficulty. Please note that this game does not implements walls as the original Snake game. Also, highscore is maintained between the games. Have fun!
