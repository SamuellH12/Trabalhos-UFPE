
module encoder(
    input wire [9:0] key, 
    input wire enable, clk,
    output reg load,
  	output wire [3:0] data, clk_dvd
);
    wire dvdOut;
	 wire dbcOut;

    divideSec dvd (.out_clk(dvdOut), .clk(clk));
	 debouncer dbc (.out_clk(dbcOut), .clk(clk));
    Mux2To1 mux (.D0(dvdOut), .D1(dbcOut), .Sel(enable), .Y(clk_dvd) ); 
    keyToByte ktb (.key(key), .data(data));

    reg filter;

    always @ (posedge dbcOut)
      begin
        if(enable)
          begin
            filter <= (key == 0);
            load <= (key != 0) & filter;
          end
        else
          begin
            filter <= 1'b1;
            load <= 1'b0;
          end
      end

endmodule



module divideSec( output reg out_clk, input wire clk );
  integer num;
 
  initial 
    begin 
        out_clk = 1'b0;
        num = 0;
    end
  
  always @ (posedge clk)
    begin
      num <= num + 1;

		if( num == 50_000_000/2 )       
        begin
            num <= 0;
            out_clk <= ~out_clk;
        end
    end
  
endmodule

module debouncer( output reg out_clk, input wire clk );
  integer num;
 
  initial 
    begin 
        out_clk = 1'b0;
        num = 0;
    end
  
  always @ (posedge clk)
    begin
		num  <= num + 1;

		if( num == 5_000_000/2 ) //        
        begin
            num <= 0;
            out_clk <= ~out_clk;
        end
    end
  
endmodule


module Mux2To1 (output wire Y, input wire D0, D1, input wire Sel);
    assign Y = ~Sel&D0 | Sel&D1;
endmodule


module keyToByte( input wire [9:0] key, output reg [3:0] data );

    always @ (key) begin
        if(key[0]) data = 4'b0000;
        else
        if(key[1]) data = 4'b0001;
        else
        if(key[2]) data = 4'b0010;
        else
        if(key[3]) data = 4'b0011;
        else
        if(key[4]) data = 4'b0100;
        else
        if(key[5]) data = 4'b0101;
        else
        if(key[6]) data = 4'b0110;
        else
        if(key[7]) data = 4'b0111;
        else
        if(key[8]) data = 4'b1000;
        else
        if(key[9]) data = 4'b1001;
		  else data = 4'b1001;
    end

endmodule

