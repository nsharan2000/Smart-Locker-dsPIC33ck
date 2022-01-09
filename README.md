# Smart-Locker-dsPIC33ck: 

### Video explanation: https://youtu.be/NDEcD_nKl9s

#### Background Information
Locks are of great importance and are used everywhere like jail doors, house
doors, lockers etc. This project is a better version of a locker system that is
being used everywhere. The cost of electrical items are cheaper than ever before.
We are able to add more and more features to a particular product with almost
no increase in the cost of manufacturing because of electronics.
Password Based Door Lock System is a simple product where a secure
password will act as a door unlocking system. Traditional lock systems using
mechanical lock and key mechanism are being replaced by new advanced
techniques. One of the prominent features of these innovative systems
is their simplicity and high efficiency. This project is proposed to be a better
version of a traditional locker. The control of the locking system shall be easy to
use and it should be easy to interface so that customers from any background
face very minimal difficulty while setting it up across their doors.
This kind of locks are better than traditional locks due to multiple reasons, a few
are mentioned down:
* The keypad cover protects the lock system from atmosphere, impacts and accidental damages when the keypad is not in use.
* The alarm system (in case of attempted breakage) helps in additional security which is a huge advantage over traditional lock
* No need to carry keys, as the keypad is digital.

#### Detailed Block Design
The system consists of 5 block components, namely:
1. dsPIC33CK256MP506
2. LCD display
3. Keypad
4. Alarm system
5. Lock system

##### Dev board - dsPIC33CK256MP506

The UNB Dev board will act as the central hub and will connect all other
systems. It contains dsPIC33CK256MP506 microcontroller which is the heart
of the Dev board. This will be the main controller which we will be using for
our controller system.

##### LCD display

The keypad system is the user interface for visual representation. LCD display
will be used to interact with the user. The LCD will first display “Enter the
password” and if the user enters the incorrect password it will display “You
have entered the wrong password. Please try again” and then it will go back to
displaying “Enter the password”. And if the user enters the right password it
will send the signal to the Lock system. If the user enters the wrong password
more than 5 times then a signal will be sent to the alarm system.
The LCD display is operated in a 4 bit mode.

##### Keypad

It is a 4* 4 Hex keypad which contains 16 buttons a user can press, it is a means
by which the user can enter his password. The keypad works on the basis of
allotting 4 rows as a write pin and the 4 columns as the read pin. In this way, we
will know which button is being pressed at a particular time. In order to avoid
the “bounce back” nature of the buttons a delay() is function is used to take in
the values of the user.

##### Alarm system

The alarm system consists of an active buzzer which is triggered whenever the
number of incorrect attempts reaches 5. It also contains a reset button in it, the
button is to reset the entire system so that the user can continue to use this
digital lock as it is before the intruder alarm is activated. This button is present
in the alarm system as it must be away from the intruder and must be hidden in
a secure location.

##### Lock system

If the correct password is entered in the keypad, the UNB board will verify the
password and the lock will be opened. This contains a 5V step motor DC which
will rotate 180 degrees and signifies the lock is opened. And if left idle for a
long time, it will rotate 180 degrees anticlockwise and go back to the original
position which will indicate that the lock remains closed.

##### Light System

Photoresistors, also known as light dependent resistors (LDR), are light
sensitive devices most often used to indicate the presence or absence of light, or
to measure the light intensity. In the dark, their resistance is very high,
sometimes up to 1MΩ, but when the LDR sensor is exposed to light, the
resistance drops dramatically, even down to a few ohms, depending on the light
intensity. LDRs have a sensitivity that varies with the wavelength of the light
applied and are nonlinear devices. The Photoresitors will detect the intensity of the light and will send an Analog
Signal to the microcontroller. The Microcontroller will convert the analog
signal into the digital signal using the built-in ADC module and this will give a
signal to the sequence of the LEDs. If the light intensity detected is low or the
resistance value of LDR is very high then the LEDs will glow which is kept
near the Keypad. This will make the keypad visible even in dark.

Checkout the final report in pdf format for more details.
