pollutantmean <- function(directory, pollutant, id = 1:332) {
  ## 'directory' is a character vector of length 1 indicating
  ## the location of the CSV files
  
  ## 'pollutant' is a character vector of length 1 indicating
  ## the name of the pollutant for which we will calculate the
  ## mean; either "sulfate" or "nitrate".
  
  ## 'id' is an integer vector indicating the monitor ID numbers
  ## to be used
  
  ## Return the mean of the pollutant across all monitors list
  ## in the 'id' vector (ignoring NA values)
  
  my.list <- list()
  for (i in id) {
    csv.name <- paste0(sprintf("%03s", i), ".csv")
    csv.path <- paste0(directory, "/", csv.name)
    my.list[[csv.name]] <- read.csv(csv.path)
  }
  csv.data <- do.call(rbind, my.list)
  pdata = subset(csv.data, select=pollutant)[,1]
  mean(pdata[!is.na(pdata)])

}