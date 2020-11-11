# Finite State Machine Language (FSML) compiler

## 1. Introduction
FSML is a **formal language** to describe Finite State Machines (FSMs) in a simple and effective manner.

FSML has been thought from programmers **for programmers**.
 
It was born from the need to have a simple but effective way, not using graphical tools, to write an FSM and to have it **translated to C language** (*and maybe others in the future*).

Whit FSML is possible to describe **states and transitions**, as well as arbitrary code that shall be executed within them.
There are also some constructs that allow to describe common features like **retries** and **timeouts**, in a very simple way.

FSML is **portable**, since it is compiled to C and is completely **standalone**, not relying on any other third-party library.
  

## 2. How to use it
### FSM structure
The first thing to is to define the FSM itself:
```
fsm myFirstFSM {
  // ... and this is a comment
}
```
You jus need to use the keyword `fsm` followed by a *name* and the enclose the FSM code in a pare of `{}`.

### States
Then you have to define states within the FSM:
```
state [start] firstState
on ( /* here it goes a condition */ ) go middleState;

state middleState
on ( /* ...condition... */ ) go endState;

state [end] endState;
```
So, use keyword `state` to define a new state, followed by an optional *type* that can be either `start`, `end` or `err`, followed by the *name* of the state.

Every transition that brings to another state is described by the construct `on-go`. The keyword `on` is followed by a condition between `()`, then `go` and the name of the end state. Before digging into conditions, let's make a digression about variables.

### Input and Variables
FSML has three families of variables:
- internal variables, visible only inside the FSM (defined by the keyword `var`)
- input variables, that the code that uses the FSM can set from the extern (`input`)
- output variables (`output`), more on these later

Except for the variable family, the definition is exactly the same as in C language, with a type, the name and an initializer (*mandatory*!)
```
var int myVar = 0;
input short condition = 0;
```

### Transitions 
Let's go back to trantions and have a deeper look into this construct. We've previously mentioned that a transition is specified by the keyweord `on`, followed by a condition and the *actuator* `go`, that specifies the next state.
In order to be activated, a transition need its condition to be evaluated to true. This condition is expressed in a pair of brackets `()`, that contain a boolean expression using variables and inputs.
```
state [start] firstState
on (myVar > 0) go secondState
on (myVar == 0) go thirdState;
```
In the previous snippet, if the internal variable `myVar` is greater than 0, this will activate a transition toward `secondState`. If the condition `myVar == 0` evaluates to true, instead, the transition will bring the FSM to the state `thirdState`. In case none of the conditions are true, the FSM will stay in the same state, i.e. `firstState`.

### Errors
If an error state exists (i.e. a state with the `err` type), the transition actuator can be `err` instead of `go`, followed by a label that identifies the type of error, e.g.:
```
state [start] firstState
on (myVar > 0) go secondState
on (myVar == 0) go thirdState
on (myVar < 0) err negativeValue;

state [end, err] lastState;
```

### Retries
On thing that is usefull expecially in embedded systems and critical applications, is to retry a certain operation that has failed.
A special construct can be used for this, the `until-retry`.
```
until (MAX_RETRIES) {
   state waitStep1
   on (input1 == OK) go waitStep2;
   
   state waitStep2
   on ((input1 == OK) && (input2 == OK)) go endState
   on (input1 == FAIL) retry;
} err tooManyRetries;

state [end, err] endState;
```
In the code above, there are two states surrounded by an `until` block. This block is composed by the keyword `until`, followed by a pair of brackets `()` that contains a *constant* value, that specifies the maximum number of retries. The `until` block ends with a transition actuator (in this case an `err` actuator), that specifies what the FSM shall do next, if the maximum number of retries have been reached.

The `until` block can contain any number of states, that can use the `retry` transition actuator to go to the first state of the block.
