module control(input wire startn, stopn, clear, door_closed, timer_done, output wire Q);

    wire s, r;

    magnetronLogic ml ( .startn(startn), .stopn(stopn), .clear(clear), .door_closed(door_closed), 
                        .timer_done(timer_done), .set(s), .reset(r));
    SRLatch srl (.S(s), .R(r), .Q(Q));

endmodule



module magnetronLogic(input wire startn, stopn, clear, door_closed, timer_done,
                      output wire set, reset);
    assign set = (~startn && stopn && door_closed && ~timer_done);
    assign reset = (~stopn | timer_done | ~door_closed | clear);
	 
endmodule


module SRLatch (input wire S, R, output reg Q);

    always @ (S or R)
        begin
            if (S)
                Q <= 1'b1;
            if (R)
                Q <= 1'b0;
        end

endmodule
