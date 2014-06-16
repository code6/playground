complete <- function(directory, id = 1:332) {
  ## 'directory' is a character vector of length 1 indicating
  ## the location of the CSV files
  
  ## 'id' is an integer vector indicating the monitor ID numbers
  ## to be used
  
  ## Return a data frame of the form:
  ## id nobs
  ## 1  117
  ## 2  1041
  ## ...
  ## where 'id' is the monitor ID number and 'nobs' is the
  ## number of complete cases
  
  nobs <- vector(length=length(id))
  pos <- 0
  for (i in id) {
    csv.name <- paste0(sprintf("%03s", i), ".csv")
    csv.path <- paste0(directory, "/", csv.name)
    data <- read.csv(csv.path)
    pos <- pos + 1
    nobs[pos] <- nrow(subset(data, !is.na(data$sulfate)&!is.na(data$nitrate)))
  }
  data.frame(id, nobs)
}