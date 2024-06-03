/**************************
botões: start stop clear --

switche 17 -> door_closed
switche [9:0] -> keys
**************************/


module Microwave(
  input wire clk, startn, stopn, clearn, door_closed,
  input wire [9:0] key,
  output wire mag_on, clkLed, loadLed, clearLed,
  output wire [6:0] S1, S2, S3
);

  wire on;
  wire off;
  wire zero;
  wire clk_d;
  wire load;
  wire [3:0] data;
  wire [3:0] N1;
  wire [3:0] N2;
  wire [3:0] N3;
 
  assign clear = ~clearn;
  assign mag_on = on;
  assign off = ~on;
  
  // modulos
  control ctrl (.startn(startn), .stopn(stopn), .clear( clear ), .door_closed(door_closed), .timer_done( zero ), .Q( on ) );
  encoder ecd  (.key(key), .data( data ), .clk(clk), .clk_dvd( clk_d ), .enable( off ), .load( load ) );   
  timer   tm   (.data( data ), .load( load ), .clk( clk_d ), .en( on ), .clear( clear ), .su(N1), .sd(N2), .mn(N3), .zerado( zero ) );
  decode  dcd  (.N1( N1 ), .N2( N2 ), .N3( N3 ), .S1(S1), .S2(S2), .S3(S3) );
  
	
  //leds para debug (essencialmente)
  assign clearLed = clear;
  assign clkLed = clk_d;
  assign loadLed = load;

  
endmodule


