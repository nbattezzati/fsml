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
fsm myFirtFSM {
  // ... and this is a comment
}
```
You jus need to use the keyword `fsm` followed by a *name* and the enclose the FSM code in a pare of `{}`.

### States and transitions
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
