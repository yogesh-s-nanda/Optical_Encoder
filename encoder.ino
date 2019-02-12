/***********************************************************************
 *  ====================================================================
 *    --------------------------------
 *    Optical Encoder for Motor.
 *    --------------------------------
 *    
 *    Author    : Jogesh S Nanda
 *    Date      : 12.02.2019
 *    
 *    Revision  : 12.02.2019
 *    
 *    
 *  @2019 Copyright reserved to Toboids Automata Pvt. (Ltd)
 *  ====================================================================
 */

 #define encoder_A 2      //  Connect the Left Wheel Encoder to Pin 2
 #define encoder_B 3      //  Connect the Right Wheel Encoder to Pin 3
 
 /************************************************************************
 *  Function for Motor Encoder. 
 *  
 *    Working : calling this function as Interrupt Variable will increment
 *        the encoder value by 1 which acts as a counter for rising edge.
 *    
 *    Specification : 
 *      Unit  --- in cm.
 *      Raduis of the wheel   --  3.5 cm
 *      No. of theeth in Encoder  --  20 nos
 *    
 *    Calculations :
 *      distancce for 1 wheel rotation = 2 x pi x radius of wheel ---> in in this case is 22 cm
 *      distance trvelled by wheel = distance travelled by 1 wheel rotation x total number of rotation
 *      total number of rotation = encoder_pos / number of teeth (here 20)
 *      distance_of_motor = (encoder_pos / number of teeth ) x 2.pi x radius of wheel
 *                        = encoder_pos * 1.1
 */
 
 // Variable to store the Pulse count of Encoder.
  volatile long encoder_pos_A = 0;
  volatile long encoder_pos_B = 0;

 //  Variable to store the Distance moved by the Wheels.
  double distance_left_wheel = 0;
  double distance_right_wheel = 0;
  
 /************************************************************************
 *    Left_Encoder    --->  Increment the counter by 1 when called
 */
 void Left_Encoder (){
  // Incrementing the Counter for a pulse.
  encoder_pos_A = encoder_pos_A + 1;

  // distance moved by left Wheel.
  distance_left_wheel = encoder_pos_A * 1.1;
 }

 /************************************************************************
 *    Right_Encoder   --->  Increment the counter by 1 when called
 */
 void Right_Encoder (){
  // Incrementing the Counter for a pulse.
  encoder_pos_B = encoder_pos_B + 1;

  // distance moved by left Wheel.
  distance_right_wheel = encoder_pos_B * 1.1;
 }

 /************************************************************************
 *    Reset_Encoder   --->  Reset the counter
 */
 void Reset_Encoder (){
   encoder_pos_A = 0;
   encoder_pos_B = 0;
 }

 
void setup() {
  // put your setup code here, to run once:
  
  pinMode(encoder_A, INPUT);
  pinMode(encoder_B, INPUT);

   /*********************************************************************
    *   attaching the intrupt function for reading encoder values.
    *   
    *   Interrupt   |   Pin    |          Type          |   Description
    *   
    *   interupt 0      pin 2     rising edge detection      Left Wheel
    *   interupt 1      pin 3     rising edge detection      Right Wheel
    */
    attachInterrupt(0, Left_Encoder, RISING);
    attachInterrupt(1, Right_Encoder, RISING);

  Serial.begin(57600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  char data_in;
  
  if (Serial.available() > 0){
    data_in = Serial.read();

    if (data_in == 'r'){
      Reset_Encoder();
    }
    
  }
  
  Serial.print("Encoder A : ");
  Serial.print(encoder_pos_A);

  Serial.print("\t");
  
  Serial.print("Encoder B : ");
  Serial.println(encoder_pos_B);
  
}
