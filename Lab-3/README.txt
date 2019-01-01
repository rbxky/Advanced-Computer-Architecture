Objective
This project is to implement the in-order and out-of-order pipeline.

Background & Implementation
In addition to the basic 5-stage pipeline, there are several new data structures and stages for the out-of-order pipeline:

Data structure:
Register Alias Table (RAT): It stores a valid bit and the physical register ID for each entry. In this project, the physical register is embedded in the ROB. If the entry is valid, then the entry is renamed, otherwise the value is got from Architecture Register File (ARF) directly.
Reservation Station (REST): It saves a valid bit, scheduled bit, tags (mapping from RAT to ROB) and ready bits for two sources. The instruction can be scheduled when both of th ready bits are set. And the entry is kept until it finishes EX stage and the signal from BCAST stage is sent.
Reorder Buffer (ROB): It stores a valid bit, ready bit, and the destination register. The entry is inserted when the instruction is in the RB stage (valid bit is set to 1). The ready bit will be set to 1 when the BCAST of the instruction is done. Finally, the instruction can be removed from ROB when both of the valid and ready bits are 1. This data struction is maintained via the head and tail pointers: when an entry is added, the tail pointer is increased by 1; when an instruction is commited (retired), then the head pointer is increased by 1. This strategy can ensure the pipeline remains in-order during the commit stage, even though the scheduling process may be out-of-order.
Stage:
Rename (RN): Check the availablility of ROB and REST, and update the entries for them. Read the registers from ARF or ROB, based on the value in RAT.
Scheduling (SC):

In-Order: Always check the oldest instruction in REST. If this instruction is ready, then schedule it.

Out-of-order: Check if there is any instruction ready to be schedule regardless of the age, then schedule the ready one that is the oldest.

Broadcast (BCAST): Once the instruction is executed, then this stage has to broadcast the message to the REST to wake up the relevant instructions. Then update corresponding ROB entry (ready bit = 1). In this stage, the instruction can be removed from REST.
Commit: This stage is in charge of checking if the oldest instruction in ROB is valid and ready. If yes, then this instruction is retired from this stage, otherwise the pipeline is stalled until the oldest instruction is valid and ready.


Notes
To validate the design of the project, the instructors provided CPI evaluation results for each of the trace files. The implementation is executable and having correct results. For out-of-order pipeline machines, although the hardware complexity is increased, the CPI can be more close to the ideal CPI (=1), which means it has less stalls in the pipeline.
This code is executable only on Gatech ECE server.
