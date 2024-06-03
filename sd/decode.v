

module decode(  
    input wire [3:0] N1, N2, N3,
    output wire [6:0] S1, S2, S3
);
    wire [6:0] _S1;
    wire [6:0] _S2;
    wire [6:0] _S3;
    decode7seg d1(.Seg(_S1), .Num(N1));
    decode7seg d2(.Seg(_S2), .Num(N2));
    decode7seg d3(.Seg(_S3), .Num(N3));
  
	//pra zeros a esquerda não aparecerem
  	 assign S1 = (N1 == 0 && N2 == 0 && N3 == 0 ? ~7'b0000000 : _S1 );
    assign S2 = (N2 == 0 && N3 == 0 ? ~7'b0000000 : _S2 );
    assign S3 = (N3 == 0 ? ~7'b0000000 : _S3 );
//	   assign S1 = _S1;
//    assign S2 = _S2;
//    assign S3 = _S3;

endmodule


module decode7seg (output wire [6:0] Seg,
                    input wire [3:0] Num);
 
  assign Seg = (Num == 4'b0000) ? ~7'b0111111 :
    (Num == 4'b0001) ? ~7'b0000110 :
    (Num == 4'b0010) ? ~7'b1011011 :
    (Num == 4'b0011) ? ~7'b1001111 :
    (Num == 4'b0100) ? ~7'b1100110 :
    (Num == 4'b0101) ? ~7'b1101101 :
    (Num == 4'b0110) ? ~7'b1111101 :
    (Num == 4'b0111) ? ~7'b0000111 :
    (Num == 4'b1000) ? ~7'b1111111 :
    (Num == 4'b1001) ? ~7'b1100111 :
    7'bxxxxxxx;

endmodule  

