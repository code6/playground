library("data.table")
Sys.setlocale(category = "LC_ALL", locale = "en_US.UTF-8")
legalDate <- c('1/2/2007', '2/2/2007')
dat <- fread("household_power_consumption.txt", na.strings="?")
dat <- dat[dat$Date %in% legalDate, ]

dat$Globals_active_power <- as.numeric(dat$Global_active_power)
xval <- as.POSIXct(paste(dat$Date, dat$Time), format="%d/%m/%Y %T")

png("plot3.png")
plot(xval, dat$Sub_metering_1, type="l", ylab="Energy sub metering", xlab="")
lines(xval, dat$Sub_metering_2, col ="red")
lines(xval, dat$Sub_metering_3, col ="blue")
legend("topright",  lwd=1, pch=NA, merge=FALSE, col = c("black", "blue", "red"), legend = c("Sub_metering_1", "Sub_metering_2", "Sub_metering_3"))
dev.off()