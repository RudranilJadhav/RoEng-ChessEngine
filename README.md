# RoEng-ChessEngine
**RoEng** is a **UCI-compliant chess engine written entirely in C**, focused on performance, clean architecture, and classic game-search techniques.  
The engine uses **bitboards**, **alpha–beta search**, and **Zobrist hashing** to efficiently explore the game tree and make strong move decisions.

---

## Features

- **UCI Protocol Support**  
  Compatible with chess GUIs like **Arena**, **CuteChess**, and **Lichess (via API)**

- **Bitboard-Based Board Representation**  
  Fast and memory-efficient move generation using 64-bit bitboards

- **Minimax Search with Alpha–Beta Pruning**  
  Efficient game-tree exploration

- **Zobrist Hashing & Transposition Table**  
  Avoids re-evaluating repeated positions

- **Heuristic Evaluation Function**
  - Material scoring
  - Piece-square tables
  - Basic positional evaluation
