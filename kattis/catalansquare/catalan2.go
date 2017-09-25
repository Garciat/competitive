package main

import "fmt"
import "math/big"

func product(xo int, dx int, mx int) *big.Int {
  p := big.NewInt(1)
  for x := xo; x <= mx; x += dx {
    p.Mul(p, big.NewInt(int64(x)))
  }
  return p
}

func catalan(n int) *big.Int {
  c := n / 2
  d := n % 2
  m := n - c
  
  g := 0
  i := m
  for {
    i /= 2
    if i <= 0 {
      break
    }
    g += i
  }
  
  k := 1 << uint(c - g)
  top := product(n - d + 3, 2, n * 2)
  top.Mul(top, big.NewInt(int64(k)))
  
  nodds := (m + 1) / 2
  odds := make([]*big.Int, nodds)
  t := 3
  for j := 0; j < nodds; j += 1 {
    odds[j] = big.NewInt(int64(t))
    t += 2
  }
  
  bot := big.NewInt(1)
  for j := m; j > 0; j /= 2 {
    p := big.NewInt(1)
    z := 3
    for x := 0; x < nodds && z <= j; x += 1 {
      p.Mul(p, odds[x])
      z += 2
    }
    bot.Mul(bot, p)
  }
  
  return top.Div(top, bot)
}

func main() {
  var n int
  fmt.Scanf("%d", &n)
  c := catalan(n + 1)
  fmt.Println(c)
}
