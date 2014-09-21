library("data.table")
Sys.setlocale(category = "LC_ALL", locale = "en_US.UTF-8")
legalDate <- c('1/2/2007', '2/2/2007')
dat <- fread("household_power_consumption.txt", na.strings="?")
dat <- dat[dat$Date %in% legalDate, ]

dat$Global_active_power <- as.numeric(dat$Global_active_power)
xval <- as.POSIXct(paste(dat$Date, dat$Time), format="%d/%m/%Y %T")
#r <- round(range(xval), "days")

png("plot2.png")
plot(xval, dat$Global_active_power, type="l", xlab="", ylab="Global Active Power(kilowatts)")
#axis.POSIXct(1, at = seq(r[1], r[2], by="day"), format="%a")
dev.off()