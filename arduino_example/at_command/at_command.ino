#include <stdio.h>
#include <string.h>

#define UART_PC Serial
#define UART_AT Serial1

#define DEBUG true
#define PWR_KEY 27
#define RST_KEY 33
#define LOW_PWR_KEY 2

#define AT_RX 22
#define AT_TX 21

bool ModuleState = false;

void setup()
{
    UART_PC.begin(115200);
    UART_AT.begin(115200, SERIAL_8N1, AT_TX, AT_RX);

    pinMode(PWR_KEY, OUTPUT);
    pinMode(RST_KEY, OUTPUT);
    pinMode(LOW_PWR_KEY, OUTPUT);

    digitalWrite(RST_KEY, LOW);
    digitalWrite(LOW_PWR_KEY, HIGH);
    digitalWrite(PWR_KEY, HIGH);

    digitalWrite(PWR_KEY, LOW);
    delay(3000);
    digitalWrite(PWR_KEY, HIGH);
    delay(10000);

    ModuleState = moduleStateCheck();
    if (ModuleState == false) // if it's off, turn on it.
    {
        digitalWrite(PWR_KEY, LOW);
        delay(3000);
        digitalWrite(PWR_KEY, HIGH);
        delay(10000);
        UART_PC.println("Now turnning the A9/A9G on.");
    }

    UART_PC.println("Maduino A9/A9G Test Begin!");

    // sendData("AT+CCID", 3000, DEBUG);
    // sendData("AT+CREG?", 3000, DEBUG);
    // sendData("AT+CGATT=1", 1000, DEBUG);
    // sendData("AT+CGACT=1,1", 1000, DEBUG);
    // sendData("AT+CGDCONT=1,\"IP\",\"CMNET\"", 1000, DEBUG);

    // sendData("AT+CIPSTART=\"TCP\",\"www.mirocast.com\",80", 2000, DEBUG);
}

void loop()
{
    while (UART_AT.available() > 0)
    {
        UART_PC.write(UART_AT.read());
        yield();
    }
    while (UART_PC.available() > 0)
    {
        UART_AT.write(UART_PC.read());
        yield();
    }
}

bool moduleStateCheck()
{
    int i = 0;
    bool moduleState = false;
    for (i = 0; i < 5; i++)
    {
        String msg = String("");
        msg = sendData("AT", 1000, DEBUG);
        if (msg.indexOf("OK") >= 0)
        {
            UART_PC.println("A9/A9G Module had turned on.");
            moduleState = true;
            return moduleState;
        }
        delay(1000);
    }
    return moduleState;
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    UART_AT.println(command);
    long int time = millis();
    while ((time + timeout) > millis())
    {
        while (UART_AT.available())
        {
            char c = UART_AT.read();
            response += c;
        }
    }
    if (debug)
    {
        UART_PC.print(response);
    }
    return response;
}