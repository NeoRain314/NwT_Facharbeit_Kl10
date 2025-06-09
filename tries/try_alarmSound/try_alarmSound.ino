#define PIEZO_PIN 10

#define C 264
#define E 330
#define G 396
#define A 440
#define CZWEI 528 
#define PAUSE 0

#define HALBE 3000
#define VIERTEL 2000
#define ACHTEL 1000

#define arr_length(a) (sizeof(a) / sizeof(a[0]))

const int sound0_tones[] = {A, E, G};
const int sound0_length[] = {ACHTEL, ACHTEL, HALBE};

const int sound1_tones[] = {A, PAUSE, A, PAUSE};
const int sound1_length[] = {ACHTEL, ACHTEL, ACHTEL, ACHTEL};

const int sound2_tones[] = {C, E, G, CZWEI,  G, E, C};
const int sound2_length[] = {VIERTEL, VIERTEL, VIERTEL, VIERTEL, VIERTEL, VIERTEL, VIERTEL};

const int sound3_tones[] = {A, PAUSE, A};
const int sound3_length[] = {ACHTEL, ACHTEL, ACHTEL};

int curr_sound_tones[10] = {};
int curr_sound_length[10] = {};





int i = 0;
int c = 0;

void setup(){
  for(int j = 0; j < arr_length(sound1_tones); j++){
    curr_sound_tones[j] = sound1_tones[j];
    curr_sound_length[j] = sound1_length[j];
  }
}

void loop(){

  process();
  //tone (PIEZO_PIN, A);
}

void process() {
    tone(PIEZO_PIN, sound2_tones[i]);
    c++;
    if(c > sound2_length[i]){
      i++;
      c = 0;
    }

    if(i > arr_length(sound2_tones)) i = 0;
  }