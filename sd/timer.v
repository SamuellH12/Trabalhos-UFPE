
module timer( 
    input wire [3:0] data, load, clk, en, clear,
    output wire [3:0] su, sd, mn, 
    output wire zerado
);

  // defino a lógica das conexões
  wire [3:0] osu, osd, omn;
  wire zsu, zsd, zmn;
  wire ensd, enmn;
  wire overflow;

  MOD10 rsu( .num(osu), .zero(zsu), .data(data), .load(load), .clk(clk), .en(en),   .clear(clear) );
  MOD6  rsd( .num(osd), .zero(zsd), .data(osu),  .load(load), .clk(clk), .en(ensd), .clear(clear), .overflow(overflow), .tratarOverflowN(zmn), .enGlobal(en));
  MOD10 rmn( .num(omn), .zero(zmn), .data(osd),  .load(load), .clk(clk), .en(enmn), .clear(clear), .soma1(overflow));

  // defino a lógica das saídas
  assign zerado = zsu & zsd & zmn;
  assign ensd = zsu & en;
  assign enmn = zsu & zsd & en;
  assign su = osu;
  assign sd = osd;
  assign mn = omn;
    
endmodule



module MOD10(output reg [3:0] num, 
				 output wire zero, 
				 input wire [3:0] data, load, clk, en, clear, soma1 );
  
  assign zero = (num == 4'b0000);
  reg filter;
  
   always @ (posedge clk)
    begin
			if( clear )   num <= 4'b0000;
			else if( en ) num <= num - 1;
			else if(load) num <= data;
			
			if(soma1 & ~filter) num <= num + 1;
			filter <= soma1 & en;

			if( en & zero & ~clear ) num <= 4'b1001;
    end
	 
  
endmodule



module MOD6(output reg [3:0] num, 
            output wire zero, overflow, 
            input wire [3:0] data, load, clk, en, clear, tratarOverflowN, enGlobal );
  
  assign zero = (num == 4'b0000);
  assign overflow = ((num > 4'b0101) & ~tratarOverflowN) | (enGlobal & (num > 4'b0110));
	
  always @ (posedge clk)
    begin
			if( clear )   num <= 4'b0000;
			else if( ~tratarOverflowN & overflow ) num <= num - 4'b0110;
			else if( enGlobal & overflow ) num <= num - 4'b0111;
			else if( en ) num <= num - 1;
			else if(load) num <= data;
			
			if( en & zero & ~clear ) num <= 4'b0101;
    end
  
endmodule

