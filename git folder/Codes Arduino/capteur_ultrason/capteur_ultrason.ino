/* Constantes pour les broches */
const byte TRIGGER_PIN = 3; // Broche TRIGGER
const byte ECHO_PIN = 4;    // Broche ECHO
 
/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;
float trigger_distance = 160;
float delay_time = 50;
int egg_count = 0;
boolean objectInFrontOfCapteur = false;
const int buttonPin = 2;


void setup() {
  
  /* Initialise le port série */
  Serial.begin(115200);
  
  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
  Serial.print("ready");
}

void loop() {
  
  /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  
  /* 3. Calcul la distance à partir du temps mesuré */
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  
  /* Affiche les résultats en mm, cm et m */
  //Serial.println(distance_mm);
  if (distance_mm< trigger_distance){
    if (objectInFrontOfCapteur == false){
      objectInFrontOfCapteur = true;
      Serial.println("object detected");
      egg_count +=1;
    }
   }
   if (objectInFrontOfCapteur == true && distance_mm > trigger_distance){
      objectInFrontOfCapteur = false;
      Serial.println(egg_count);
    }
    if (digitalRead(2)==HIGH){
      Serial.println("button appuye");
      egg_count = 0;
    }

  /* Délai d'attente pour éviter d'afficher trop de résultats à la seconde */
  delay(delay_time);
}

