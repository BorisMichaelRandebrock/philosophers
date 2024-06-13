# Dining Philosophers Problem

This program is an implementation of the classic `Dining Philosophers` problem using threads.   
The problem illustrates synchronization issues and potential deadlocks in concurrent programming.

## Table of Contents

<img align="right" src="https://github.com/BorisMichaelRandebrock/philosophers/assets/98555508/fc8565b9-59f5-448c-8037-416af1e687a2"
     alt="5 Philosophos around a table with 5 plates and 5 forks"  width="400" height="400">

- [Introduction](#introduction)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [Contributing](#contributing)


## Introduction

The Dining Philosophers problem involves five philosophers sitting at a table who do nothing but eat, sleep &  think.  
   Between each pair of philosophers, there is a fork. A philosopher must pick up both forks to eat.  
    The problem is to design a protocol such that no philosopher will starve and the system will not deadlock.

## Requirements

- C Compiler 
- Pthreads Library (if using Linux) otherwise  comment in Makefile the flag `-lpthread` in line 24.

## Leaks & Friends
- if you are working with Mac you can run `make tleaks` for running `leaks -atExit--` 
- if you have the valgrind installed you can run:  
	`make valgrind`  
	`make viking`  
	`make ragnarok`  
for checking different aspects.
In order to change the testing parameters, you can do so in lines 37, 40, 43 & 46 in the Makefile
also, uncomment the flag `-fsanitize=thread` if you wish to see the sanitizer in action.


## Installation

 Clone the repository:  
    https://github.com/BorisMichaelRandebrock/philosophers.git  
   cd xxx/philo

## Usage 

### Run the program:
<make> 

### How It Works
#### ./philo number_of_philos time_to_die time_to_eat time_to_sleep [amount_of_meals]
- `number_of_philos`: 
Once compiled you enter the amount of philosophers invited to the potentially deadly dinner. Initially the maximum number of philos is limited to 200 (for evaluation purposes), but you can increase this number at will in the macro PHILO_MAX  (line 30 in philo.h). I have it tested with up to 2000 philos.
- `time_to_die`:
Amount of miliseconds - limitation required to eat before starvation causes death. 
- `time_to_eat`:
aom - time granted to each philo to eat in her/his turn.
- `time_to_sleep`:
aom - sleep is necessary... is it not?
- `amount_of_meals`:
Is an optional value. If you enter an amount of meals, then this will be the maximum amount of meals that each philo will consume and enable the waiter to close the Restaurant.  

Otherwise, the restaurant will never close unless the untimely death of one of our guests...  
Obviously,.. it is up2you to grant sufficient time to eat, sleep & eventually think.
examples:  
`5 800 200 200` - is an eternal dinner party.  
`5 400 200 200` is a certain visit @ the funeral.  
`5 405 200 200 200` will be a happy ending after 200 meals.  


## Overview
The program simulates the Dining Philosophers problem using threads to represent each philosopher. Each philosopher thread alternates between thinking and attempting to eat. To eat, a philosopher must acquire locks on both the left and right forks (mutex -> mutual exclusion). The challenge is to avoid deadlock and ensure that no philosopher is starved.

### Thread Synchronization
Mutexes: Used to represent forks (and other protected variables like dinner ending and so on..).  
 A philosopher must lock both forks (mutexes) to eat.

#### Implementation Details
`Initialization`: Create philosopher threads and initialize mutexes.  
`Thinking`: A philosopher spends some time thinking.  
`Hungry`: A philosopher tries to pick up both forks.  
`Eating`: A philosopher eats if both forks are available.  
`Release`: After eating, the philosopher releases the forks and goes back to thinking.
Avoiding Deadlock   
`Numbering Forks and Philosophers`: Philosophers are numbered i + 1 through x and forks are numbered from 0 to x -1. Philo[i] picks up fork[i-1] and fork[i].  
`Ordering of Forks`: To prevent circular wait, each philosopher picks up the lower-numbered fork first (except philosopher[0], who picks fork[philo_number -1]) & fork[i].
Initial deadlock is avoided by sending even philos to a short slumber.

## Contributing
Contributions are welcome! Please submit a pull request or open an issue to discuss improvements or bugs.
![dining_philosophers](https://github.com/BorisMichaelRandebrock/philosophers/assets/98555508/fc8565b9-59f5-448c-8037-416af1e687a2)

