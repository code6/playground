library("data.table")
legalDate <- c('1/2/2007', '2/2/2007')
dat <- fread("household_power_consumption.txt", na.strings="?")
dat <- dat[dat$Date %in% legalDate, ]
dat$Global_active_power <- as.numeric(dat$Global_active_power)
png("plot1.png")
hist(dat$Global_active_power,main = "Global Active Power", xlab = 'Global Active Power(kilowatts)', col=2)
dev.off()