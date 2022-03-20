void setup() {
  // put your setup code here, to run once:

}

int flip = 0;
//int keys[] = {KEY_O, KEY_S, KEY_U};
int keys_len = 3;
void loop() {
  // put your main code here, to run repeatedly:
  if (flip == 0) {
    Keyboard.set_key1(KEY_A);
  } else if (flip == 1) {
    Keyboard.set_key1(KEY_B);
  } else if (flip == 2) {
    Keyboard.set_key1(KEY_C);
  } else if (flip == 3) {
    Keyboard.set_key1(0);
  } else {
    delay(1000);

  }
  Keyboard.send_now();
  flip = (flip + 1) % 5;
}
