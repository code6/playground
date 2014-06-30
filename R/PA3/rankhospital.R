hospitalranks <- function(state, outcome) {
  ## Read outcome data
  ## Check that state and outcome are valid
  ## Return data.frame (hospital name, rate) in that state with lowest 30-day death
  ## rate first
  data <- read.csv("outcome-of-care-measures.csv", colClasses = "character")  
  stateSet <- unique(data$State)
  if (!is.element(state, stateSet)) {
    stop("invalid state")
  }
  outcomeList <- list("heart attack" = "Hospital.30.Day.Death..Mortality..Rates.from.Heart.Attack",
                      "heart failure" = "Hospital.30.Day.Death..Mortality..Rates.from.Heart.Failure",
                      "pneumonia" = "Hospital.30.Day.Death..Mortality..Rates.from.Pneumonia"
  )
  outcomeName <- outcomeList[[outcome]]
  if (is.null(outcomeName)) {
    stop("invalid outcome")
  }  
  sb <- subset(data, State==state, select = c("Hospital.Name", outcomeName))
  sb[,2] <- as.numeric(sb[,2])  
  sb <- sb[complete.cases(sb[,2]),]
  sb[order(sb[,2], sb[,1]),]
}

rankhospital <- function(state, outcome, num = "best") {
  ## Read outcome data
  ## Check that state and outcome are valid
  ## Return hospital name in that state with the given rank
  ## 30-day death rate
  data <- hospitalranks(state, outcome)
  if (num == "best") {
    data[,1][1]
  } else {
    if (num == "worst") {
      data[,1][nrow(data)]
    } else {
      num <- as.numeric(num)      
      if (!is.na(num) & (num <= nrow(data)) & (num >= 1) ) {
        data[,1][num]
      } else {
        NA
      }
    }
  }
}