`include "sdram_master_defines.v"
/*
hl.ren.pub@gmail.com
*/


module sdram_master(
	// signals to connect to an Avalon clock source interface
	clk,
	reset,
	
	// signals to connect to an Avalon-MM slave interface
	avs_s1_chipselect,
	avs_s1_address,
	avs_s1_read,
	avs_s1_write,
	avs_s1_readdata,
	avs_s1_writedata,
	avs_s1_byteenable,
	avs_s1_waitrequest,

	// read master port interface
	avm_read_address,
	avm_read_read,
	//avm_read_byteenable,
	avm_read_readdata,
	avm_read_waitrequest,
	
	// write master port interface
	avm_write_address,
	avm_write_write,
	//avm_write_byteenable,
	avm_write_writedata,
	avm_write_waitrequest

	);
	
input	clk;
input 	reset;
input 	avs_s1_chipselect;
input 	[2:0] 	avs_s1_address;
input 	avs_s1_read;
output 	reg [31:0] 	avs_s1_readdata;
input 	avs_s1_write;
input 	[31:0] 	avs_s1_writedata;
input 	[3:0] 	avs_s1_byteenable;
output	avs_s1_waitrequest;

	// read master port interface
output	reg	[31:0]	avm_read_address;
output	reg	avm_read_read;
//output	reg	[3:0]	avm_read_byteenable;
//input	[31:0]	avm_read_readdata;
input	[15:0]	avm_read_readdata;
input	avm_read_waitrequest;
	
	// write master port interface
output	reg	[31:0]	avm_write_address;
output	reg	avm_write_write;
//output	reg	[3:0]	avm_write_byteenable;
//output	reg	[31:0]	avm_write_writedata;
output	reg	[15:0]	avm_write_writedata;
input	avm_write_waitrequest;

reg	[31:0]	S_addr;//source address
reg	[31:0]	D_addr;//destination  address
reg	[31:0]	Longth;

reg	Status;

//reg 	[31:0] 	DMA_DATA;
reg 	[15:0] 	DMA_DATA;

reg 	[31:0]	DMA_Cont;

reg	avs_s1_read_last;
always@(posedge clk)
begin
	avs_s1_read_last <= avs_s1_read;
end

wire	avs_s1_waitrequest;
assign	avs_s1_waitrequest = ~(avs_s1_read_last | avs_s1_write);

//read and write regs
always@(posedge clk or posedge reset)
begin
		if(reset) begin
			S_addr 		<= 32'h0;	
			D_addr 		<= 32'h0;	
			Longth 		<= 32'h0;
		end
		else 	begin
			if((avs_s1_chipselect==1'b1) && (avs_s1_write==1'b1)) begin
				case(avs_s1_address)
					`S_ADDR:			S_addr 		<= avs_s1_writedata;
					`D_ADDR:			D_addr 		<= avs_s1_writedata;
					`LONGTH:			Longth 		<= avs_s1_writedata;
				endcase
			end
			else	begin
				if((avs_s1_chipselect==1'b1) && (avs_s1_read==1'b1)) begin
					case(avs_s1_address)
						`S_ADDR:			avs_s1_readdata <= S_addr;
						`D_ADDR:			avs_s1_readdata <= D_addr;
						`LONGTH:			avs_s1_readdata <= Longth;
						`STATUS_ADDR:	avs_s1_readdata <= {31'h0,Status};
						default: 			avs_s1_readdata <= 32'h0;
					endcase
				end
			end
		end
end


//start signal
reg	start;
always@(posedge clk or posedge reset)
begin
	if(reset)
		start 		<= 1'b0;
	else 	if((avs_s1_chipselect==1'b1) & (avs_s1_write==1'b1) & (avs_s1_address == `START_ADDR))	
				start 	<= 1'b1;
			else start 	<= 1'b0;
end

//status signal
reg	done;
reg done_last;
always@(posedge clk)
begin
	if(reset) 	done_last 		<= 1'b0;
	else 		done_last 		<= done;
end


always@(posedge clk)
begin
	if(reset)
	begin
		Status <= 1'b0;
	end
	else 	if((avs_s1_chipselect==1'b1) &  (avs_s1_write==1'b1)  & (avs_s1_address == `START_ADDR) )	
			begin
				Status <= 1'b0;
			end
			else 	if( (done_last == 1'b0 )&( done == 1'b1) )
					begin
						Status <= 1'b1;
					end
end

//FSM

reg	[5:0]	DMA_state;

parameter	DMA_IDLE				=	0;
parameter	READ					=	1;
parameter	WAIT_READ				=	2;
parameter	WRITE				=	3;
parameter	WAIT_WRITE			=	4;
parameter	CALC_NEXT				=	5;
parameter	DMA_DONE				=	6;

always@(posedge clk)
begin
	if(reset) begin
		DMA_state <= DMA_IDLE;
		DMA_Cont 	<= 32'h0;
	end
	else begin
		case(DMA_state)
			DMA_IDLE: begin
				DMA_Cont <= 32'h0;
				done 				<= 1'b0;
				if(start) 
					DMA_state 		<= READ;
			end
			READ: begin
				avm_read_address <= S_addr + DMA_Cont;
				//avm_read_byteenable <= 4'b0001; 
				avm_read_read <= 1'b1;
				DMA_state	<= WAIT_READ;
			end
			WAIT_READ: begin
				if(avm_read_waitrequest == 1'b0 )
				begin
					avm_read_read <= 1'b0;
					DMA_DATA <= avm_read_readdata;
					DMA_state <= WRITE;
				end
			end
			WRITE: begin
				avm_write_address <= D_addr + DMA_Cont;
				//avm_write_byteenable <= 4'b0001;
				avm_write_write <= 1'b1;
				avm_write_writedata <= DMA_DATA;
				//avm_write_writedata <= DMA_Cont;//temp test
				DMA_state <= WAIT_WRITE;
			end
			WAIT_WRITE: begin
				if(avm_write_waitrequest == 1'b0 )
					begin
						DMA_Cont <= DMA_Cont + 32'h2;
						//avm_write_address <= 0;
						avm_write_write <= 1'b0;
						if(DMA_Cont < Longth)
							DMA_state <= READ;
						else
							DMA_state <= DMA_DONE;
							
					end
			end
			DMA_DONE: begin
				done <= 1'b1;
				DMA_state <= DMA_IDLE;
			end
			default: begin
				DMA_state <= DMA_IDLE;
			end			
		endcase
	end
end
endmodule
