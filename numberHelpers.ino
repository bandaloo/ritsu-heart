void setupDigit(int offset) {
    for (int i = 2 + offset; i < 10 + offset; i++) {
        pinMode(i, OUTPUT);
    }
}

void writeNumber(int num, int offset) {
    if (num == 0) {
        digitalWrite(5 + offset, LOW);  //0
        digitalWrite(6 + offset, LOW);
        digitalWrite(7 + offset, LOW);
        digitalWrite(2 + offset, LOW);
        digitalWrite(3 + offset, LOW);
        digitalWrite(4 + offset, LOW);
        digitalWrite(8 + offset, HIGH);
    } else if (num == 1) {
        digitalWrite(5 + offset, HIGH);  //1
        digitalWrite(6 + offset, LOW);
        digitalWrite(7 + offset, LOW);
        digitalWrite(2 + offset, HIGH);
        digitalWrite(3 + offset, HIGH);
        digitalWrite(4 + offset, HIGH);
        digitalWrite(8 + offset, HIGH);
    } else if (num == 2) {
        digitalWrite(5 + offset, LOW);  //2
        digitalWrite(6 + offset, LOW);
        digitalWrite(7 + offset, HIGH);
        digitalWrite(2 + offset, LOW);
        digitalWrite(3 + offset, LOW);
        digitalWrite(4 + offset, HIGH);
        digitalWrite(8 + offset, LOW);
    } else if (num == 3) {
        digitalWrite(5 + offset, LOW);  //3
        digitalWrite(6 + offset, LOW);
        digitalWrite(7 + offset, LOW);
        digitalWrite(2 + offset, LOW);
        digitalWrite(3 + offset, HIGH);
        digitalWrite(4 + offset, HIGH);
        digitalWrite(8 + offset, LOW);
    } else if (num == 4) {
        digitalWrite(5 + offset, HIGH);  //4
        digitalWrite(6 + offset, LOW);
        digitalWrite(7 + offset, LOW);
        digitalWrite(2 + offset, HIGH);
        digitalWrite(3 + offset, HIGH);
        digitalWrite(4 + offset, LOW);
        digitalWrite(8 + offset, LOW);
    } else if (num == 5) {
        digitalWrite(5 + offset, LOW);  //5
        digitalWrite(6 + offset, HIGH);
        digitalWrite(7 + offset, LOW);
        digitalWrite(2 + offset, LOW);
        digitalWrite(3 + offset, HIGH);
        digitalWrite(4 + offset, LOW);
        digitalWrite(8 + offset, LOW);
    } else if (num == 6) {
        digitalWrite(5 + offset, LOW);  //6
        digitalWrite(6 + offset, HIGH);
        digitalWrite(7 + offset, LOW);
        digitalWrite(2 + offset, LOW);
        digitalWrite(3 + offset, LOW);
        digitalWrite(4 + offset, LOW);
        digitalWrite(8 + offset, LOW);
    } else if (num == 7) {
        digitalWrite(5 + offset, LOW);  //7
        digitalWrite(6 + offset, LOW);
        digitalWrite(7 + offset, LOW);
        digitalWrite(2 + offset, HIGH);
        digitalWrite(3 + offset, HIGH);
        digitalWrite(4 + offset, HIGH);
        digitalWrite(8 + offset, HIGH);
    } else if (num == 8) {
        digitalWrite(5 + offset, LOW);  //8
        digitalWrite(6 + offset, LOW);
        digitalWrite(7 + offset, LOW);
        digitalWrite(2 + offset, LOW);
        digitalWrite(3 + offset, LOW);
        digitalWrite(4 + offset, LOW);
        digitalWrite(8 + offset, LOW);
    } else if (num == 9) {
        digitalWrite(5 + offset, LOW);  //9
        digitalWrite(6 + offset, LOW);
        digitalWrite(7 + offset, LOW);
        digitalWrite(2 + offset, LOW);
        digitalWrite(3 + offset, HIGH);
        digitalWrite(4 + offset, LOW);
        digitalWrite(8 + offset, LOW);
    }
}
