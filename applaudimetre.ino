const int soundSensorPin = A0;   // Broche analogique pour le capteur de son
const int ledPin = 6;           // Broche pour la première LED de la série
const int numLEDs = 26;         // Nombre de LED dans la série

int threshold = 500;            // Seuil pour détecter un applaudissement

void setup() {
  pinMode(ledPin, OUTPUT);
  for (int i = 1; i < numLEDs; i++) {
    pinMode(ledPin + i, OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int soundLevel = analogRead(soundSensorPin);  // Lecture du niveau de son
  Serial.println(soundLevel);                    // Affichage du niveau de son (facultatif)

  if (soundLevel > threshold) {
    applause(soundLevel);  // Appel de la fonction pour allumer les LED en fonction de l'intensité du son
    delay(1000); // Délai pour éviter de détecter plusieurs applaudissements rapides
  }
}

void applause(int soundLevel) {
  int numLEDsToLight = map(soundLevel, 0, 1023, 0, numLEDs);  // Conversion du niveau de son en nombre de LED à allumer

  for (int i = 0; i < numLEDsToLight; i++) {
    digitalWrite(ledPin + i, HIGH);  // Allume chaque LED dans la série jusqu'à numLEDsToLight
    delay(100);                      // Délai entre chaque allumage de LED pour un effet progressif
  }
  
  delay(500);  // Temps d'affichage des LED allumées
  
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPin + i, LOW);   // Éteint chaque LED dans la série
  }
}
