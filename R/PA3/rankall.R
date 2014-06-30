rankall <- function(outcome, num = "best") {
  ## Read outcome data
  ## Check that state and outcome are valid
  ## For each state, find the hospital of the given rank
  ## Return a data frame with the hospital names and the
  ## (abbreviated) state name
  outcomeList <- list("heart attack" = "Hospital.30.Day.Death..Mortality..Rates.from.Heart.Attack",
                      "heart failure" = "Hospital.30.Day.Death..Mortality..Rates.from.Heart.Failure",
                      "pneumonia" = "Hospital.30.Day.Death..Mortality..Rates.from.Pneumonia"
  )
  outcomeName <- outcomeList[[outcome]]
  if (is.null(outcomeName)) {
    stop("invalid outcome")
  }
  
  orderFlag = 1
  if (num == "best") {
    num <- 1  
  } else {
    if (num == "worst") {
      orderFlag = -1
      num <- 1
    } else {
      num <- as.numeric(num)      
      if (is.na(num)) {
        return(NA)
      }
    }
  }

  
  data <- read.csv("outcome-of-care-measures.csv", colClasses = "character")
  data[,outcomeName] <- as.numeric(data[,outcomeName]) * orderFlag
  data <- data[complete.cases(data[,outcomeName]),]
  data <- data[ order(data[,"State"], data[,outcomeName], data[,"Hospital.Name"]),]
  
  data$rank <- ave(data[,outcomeName], data$State, FUN=function(x) {rank(x, ties.method="first")})  
  stateSet <- unique(data$State)
  rankData <- subset(data, rank == num,  select=c("State", "Hospital.Name") )  
  hospitalSet <- sapply(stateSet, function(state) { pos <- match(state, rankData$State); if (!is.na(pos)) rankData[pos,"Hospital.Name"] else NA })
  data.frame(hospital=hospitalSet, state=stateSet)
}