# Multithreaded Tic-Tac-Toe (C++)

This project is a Tic-Tac-Toe simulation built in C++ using multithreading. It uses two separate threads for players X and O, with a mutex to make sure both threads don't access the shared game board at the same time.

## How It Works

- Two threads represent players X and O.
- Each player randomly chooses an empty spot on the board.
- A mutex is used to control access to the shared game board.
- The program checks for a winner or a tie after each move.
- The players keep taking turns until someone wins or the game ends in a tie.

## Technologies Used

- C++
- Multithreading (`std::thread`)
- Mutex synchronization (`std::mutex`)
- Random number generation

## How to Run

Compile the program using a C++ compiler:

```bash
g++ -std=c++11 -pthread tictactoe.cpp -o tictactoe
```

Then run:

```bash
./tictactoe
```

## Demo

https://github.com/user-attachments/assets/58a8b472-1ef0-4e67-9d94-e91305970446
