void setupDigit()
{
    for (int i = 2; i < 10; i++)
    {
        pinMode(i, OUTPUT);
    }
}

void writeNumber(int num)
{
    if (num == 0)
    {
        digitalWrite(2, LOW); //0
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
    }
    else if (num == 1)
    {
        digitalWrite(2, HIGH); //1
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
    }
    else if (num == 2)
    {
        digitalWrite(2, LOW); //2
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        digitalWrite(8, LOW);
    }
    else if (num == 3)
    {
        digitalWrite(2, LOW); //3
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, LOW);
    }
    else if (num == 4)
    {
        digitalWrite(2, HIGH); //4
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
    }
    else if (num == 5)
    {
        digitalWrite(2, LOW); //5
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
    }
    else if (num == 6)
    {
        digitalWrite(2, LOW); //6
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
    }
    else if (num == 7)
    {
        digitalWrite(2, LOW); //7
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
    }
    else if (num == 8)
    {
        digitalWrite(2, LOW); //8
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
    }
    else if (num == 9)
    {
        digitalWrite(2, LOW); //9
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
    }
}