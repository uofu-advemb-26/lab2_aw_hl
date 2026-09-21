# Lab 2 Test Plan

## Adam W and Harrison

### 1. How to setup test scenario

- We need to restrucuture hello_freertos.c to lend to easier testing.
For example, refactor the character case logic into a sub function with a return type that we can easily drive inputs and outputs to verify.

We also need to modify the global variables (state) to rather be inputs to the system (parameters) so that we can exercise specific testing states.
- count
- on

Isolate tasks and offload logic to functions. 

### 2. How to Exercise System

Write unit tests with UNITY testing framework to test the behavior of the offloaded task logic.

Use specific unity assertions like:
/begin{itemize}
/item{TEST_ASSERT_EQUAL_INT, to test char logic, register values for led, local variables, etc} //
/end{itemize}

### 3. Expected Behavior

LED should blink at a known rate.
Input char case should be reversed (lowercase -> uppercase, and vice versa). All other char types should just send back themselves. 