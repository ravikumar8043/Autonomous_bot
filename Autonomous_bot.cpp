// C++ code
//
int echoPin[4] = {7, 8, 12, 13};
int trigPin[4] = {6, 9, 10, 11};
int output[4] = {A0,4,3,2};

int distance[4] = {0, 0, 0, 0};
bool canMoveD[4] = {false, false, false, false};

int speed = 150;
int dthreshold = 100;

int CheckDistance(int trigPin, int echoPin);
void ShowDistance(int d);
void WriteToUNO(bool *arr);

void setup()
{
    pinMode(5, OUTPUT);
    for (int i = 0; i < 4; i++)
    {
        pinMode(output[i], OUTPUT);
        pinMode(trigPin[i], OUTPUT); // Sets the trigPin as an OUTPUT
        pinMode(echoPin[i], INPUT);  // Sets the echoPin as an INPUT
    }
    Serial.begin(9600);
}

void loop()
{
    analogWrite(5, speed);
    //Serial.println(speed);
    for (int i = 0; i < 4; i++)
    {
        distance[i] = CheckDistance(trigPin[i], echoPin[i]);
        // ShowDistance(distance[i]);
        if (distance[i] > dthreshold)
        {
            canMoveD[i] = true;
        }
        else
        {
            canMoveD[i] = false;
        }
    }

    WriteToUNO(canMoveD);
  delay(100);
}

int CheckDistance(int trigPin, int echoPin)
{
    long duration;
    int d;
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    d = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    return d;
}

void ShowDistance(int d)
{
    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(d);
    Serial.println(" cm");
}

void WriteToUNO(bool *arr)
{
    for (int i = 0; i < 4; i++)
    {
        if (arr[i])
        {
            digitalWrite(output[i], HIGH);
        }
        else
        {
            digitalWrite(output[i], LOW);
        }
    }
}
