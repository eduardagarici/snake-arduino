# snake-arduino

Descrierea jocului
Snake,unul dintre cele mai cunoscute jocuri ( cred ca  telefonele vechi aveau o versiune de snake), este un joc aparent simplu care presupune directionarea unui sarpe catre anumite puncte(controlul sarpelui fiind al user-ului). Desi pare simplu, acest joc are o dificultate progresiva , iar de la dimensiuni mari ale sarpelui devine aproape imposibil de a mai ajunge la urmatorul punct. Nota: versiunea de Snake implementata de mine permite mersul prin pereti, adica la lovirea unui perete de catre sarpe, acesta va fi transportat in partea opusa a peretelui.

Hardware 
Jocul va rula pe o matrice LED 8X8, care este connectata la o placa Arduino Uno printr-un driver MAX7219. Pe langa matrice, voi folosi un joystick cu care user-ul poate controla sarpele, un buton fizic pentru pornirea/repornirea jocului, un led-display pentru afisarea mesajelor aditionale si bineinteles breadboard-urile si cablajele necesare.


Software
Referitor la partea de programare a jocului, acesta a fost impartit in cat mai multe functii poate a putea fi urmarita usor logica programului si bineinteles pentru un debugging cat mai rapid. In program folosesc urmatoarele functii:
-citire input user;
-generare si afisare hrana ( punctul pe care trebuie sa ajunga sarpele)
-deplsare si afisare snake
-afisare mesaje
-newGame, gameOver(unde setez/resetez variabilele precum scor )
-functie care verifica daca am lovit hrana (utila pentru incrementarea dimensiunii sarpelui)
-functie care verifica daca sarpele s-a lovit de corpul sau
Sarpele este memorat cu 2 vectori (unul care pastreaza coordonatele pe X , celalalt pe Y), iar functiile care verifica daca sarpele a lovit hrana sau pe el insusi sunt raportate la capul sarlepui. In program nu folosesc functia predefinita “delay” ci o simulez prin intermediul functiei millis(), astfel la fiecare interval de 500 ms folosesc functia de clearDisplay, urmata de cea pentru Afisarea Sarpelui pentru a crea senzatia de miscare. La finalul jocului pe ecranul aditional va aparea scorul,urmat de highscore, si in final un mesaj care sa informeze user-ul ca pentru un nou joc trebuie sa apese butonul.

