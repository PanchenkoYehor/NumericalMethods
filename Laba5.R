{
  library(dplyr)
  library(ggplot2)
  library(statsr)
  library(matlib)
}

p = c(-4, -2, 0, 2, 4)


f <- function(x) {
  return (x + 8 / (1 + exp(x / 4)))
}

g <- function(x) {
  res = 0
  for (i in 1:5) {
    
    mlt = 1
    for (j in 1:5) {
      
      if (i == j) {
        next
      }
      
      mlt = mlt * (x - p[j]) / (p[i] - p[j])
    }
    
    res = res + mlt * f(p[i])
  }
  
  return (res)
}

{
  delta_y <- function(i, k) {
    if (k == 0) {
      return (f(p[i + 1]))
    } else {
      return (delta_y(i + 1, k - 1) - delta_y(i, k - 1))
    }
  }
  
  gnNewtonLection <- function(x) {
    res = 0
    mlt = 1
    
    for (i in 0:4) {
      
      res = res + mlt * delta_y(0, i)
      if (i == 4) {
        break
      }
      
      mlt = mlt * (x - p[i + 1])
      mlt = mlt / (i + 1)
      mlt = mlt / 2
      
    }
    
    return (res)
      
  }
  print(gnNewtonLection(-10))   
}


curve(x^3-3*x, -2, 2)
{
  curve(f, -10, 10, col = 2)
  curve(g, -10, 10, col = 3, add = TRUE)
  curve(gnNewtonLection, -10, 10, col = 4, add = TRUE)
  
}

{
  curve(f, -10, 10, col = 2)
  curve(x/2+4, -10, 10, col = 3, add = TRUE)
}
  
