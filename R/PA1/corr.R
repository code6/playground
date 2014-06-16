corr <- function(directory, threshold = 0) {
  ## 'directory' is a character vector of length 1 indicating
  ## the location of the CSV files
  
  ## 'threshold' is a numeric vector of length 1 indicating the
  ## number of completely observed observations (on all
  ## variables) required to compute the correlation between
  ## nitrate and sulfate; the default is 0
  
  ## Return a numeric vector of correlations  
  co <- vector(mode="numeric", length=10)
  for (i in 1:332) {
    csv.name <- paste0(sprintf("%03s", i), ".csv")
    csv.path <- paste0(directory, "/", csv.name) 
    data <- read.csv(csv.path)
    data <- subset(data, !is.na(data$sulfate)&!is.na(data$nitrate), select=c("sulfate", "nitrate"))
    if (nrow(data) > threshold) {      
      co[i] <- cor(data[,1], data[,2])
    } else {
      co[i] <- NA
    }
  }
  co[!is.na(co)]
}