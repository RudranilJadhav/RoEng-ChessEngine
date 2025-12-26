
# ROENG : Chess Engine

**ROENG** is UCI Chess Engine written in C !

### Performance on Lichess
**Lichess Profile :**  [View Profile](https://lichess.org/@/ROENG)

**Lichess ELO Rating :**

- **Bullet :**  [1897](https://lichess.org/@/ROENG/perf/bullet)
- **Blitz :** [1777](https://lichess.org/@/ROENG/perf/blitz)

### Installation Guide
```
git clone https://github.com/RudranilJadhav/RoEng-ChessEngine.git
cd RoEng-ChessEngine
make

```
You can add ROENG to any UCI compatible GUI including Arena Chess, CuteChess and
Lichess-Bots(API). 

[Here guide to deploy engine on Lichess-Bots](https://github.com/lichess-bot-devs/lichess-bot/wiki/How-to-Install)

### About Engine and it's features
- Used Bitboards for board representation
- Basic move genrator for genration of peudo-legal and legal moves
- Incremental updates with make move and undo move functions
- Zorbist Hashing to avoid repetition of previously searched positions
- Hurustic Evaluation based on with Piece-Square Table
- Alpha Beta search optimized by negamax algorithm, quiescence with move ordering

### Acknowledgements
- [Chess Programming Wiki](https://www.chessprogramming.org/)
- [Bitboard Chess Engine by Code Monkey King](https://github.com/maksimKorzh/bbc/blob/master/src/old_versions/bbc_1.0.c)
- [Art of Chess Programming in Rust](https://rustic-chess.org/)


