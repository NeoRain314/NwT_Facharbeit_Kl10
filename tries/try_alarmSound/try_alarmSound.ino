const int sound1_tones[] = {};
const int sound1_length[] = {};

#define A 440

#define HALBE
#define VIERTEL
#define ACHTEL

void setup(){

}

void loop(){
  process();
}

void process() {
    tone(PIEZO_PIN, sound1_tones[i]);
    c++;
    if(c > sound1_length[i]){
      i++;
      c = 0;
    }

    if(i >arr_length(sound1_tones)) i = 0;
  }