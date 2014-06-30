source('rankhospital.R')  

best <- function(state, outcome) {
  sb <- hospitalranks(state, outcome)
  sb[,1][1]
}
