// Playground - noun: a place where people can play

import Foundation

extension String {
    subscript (i: Int) -> String {
        return String(Array(self)[i])
    }
    subscript (r: Range<Int>) -> String {
        var start = advance(startIndex, r.startIndex)
        var end = advance(startIndex, r.endIndex)
        return substringWithRange(Range(start: start, end: end))
    }
    var length:Int { return (self as NSString).length }
    var strip:String {
        return self.stringByTrimmingCharactersInSet(NSCharacterSet.whitespaceAndNewlineCharacterSet())
    }
    var reversed:String {
        var result:[String] = []
        for ch in self {
                result.append(String(ch))
        }
        return "".join(result.reverse())
    }
    func slice(start:Int=0, end:Int?=nil) -> String {
        let s = self as NSString
        var new_end:Int
        if ((end) != nil) {
            new_end = min(end!, s.length)
        } else {
            new_end = s.length
        }
        return  s.substringWithRange(NSRange(location: start, length:new_end - start))
    }
    func split(sep:String = "") -> [String] {
        return self.componentsSeparatedByString(sep)
    }
    func group(var step:Int) -> [String] {
        var result:[String] = []
        var next_i:Int
        step = max(step, 1)
        for var i = 0; i < self.length; i = next_i {
            next_i = i + step
            result.append(self.slice(start: i, end: next_i))
        }
        return result
    }
}

func splitWordString(var s:String) -> [String] {
    return s.split(sep: " ").filter({w in !w.strip.isEmpty}).map({w in w.strip + " "})
}

class NumberToWord {
    let zero = "zero "
    let tens = splitWordString("unit ten  twenty  thirty  forty  fifty  sixty  seventy  eighty  ninety")
    let onesAndTeens = [""] + splitWordString("one  two  three  four  five  six  seven  eight  nine  ten eleven  twelve  thirteen fourteen fifteen sixteen seventeen  eighteen nineteen")
    let hunderd = "hunderd "
    let scale = [""] + splitWordString("thousand million billion trillion quadrillion sextillion septillion octillion nontillion decillion ")
    let fractionScale = [""] + splitWordString("tenth hundredth thousandth  ten-thousandth hundred-thousandth millionth ten-millionth hundred-millionth billionth ten-billionth hundred-billionth")
    
    var andString:String
    var hypenString:String
    
    init(showAnd: Bool = true, showHypen: Bool = true) {
        self.andString = showAnd ? "and " : ""
        self.hypenString = showHypen ? "-" : " "
    }

    func composeScale(var val:String, var power:String) -> String {
        // 123 => "one hundred [and] twenty-three"
        switch val {
        case "0":
            return self.zero
        case "000":
            return ""
        case let v where (v.length == 3) && v.hasSuffix("00"):
            //100, 200 ... 900
            return onesAndTeens[v[0].toInt()!] + hunderd + power
        default:
            // "123" becomes Array((1,"hundred"), (2, "ten"), (3, "one"))
            var groups = Array(Zip2(val.group(1).map({x in x.toInt()!}).reverse(), ["one", "ten", "hundred"]) ).reverse()
            return "".join(groups.map({x -> String in
                    switch x {
                        case let (d, "hundred") where d > 0:
                            return self.onesAndTeens[d] + self.hunderd + self.andString
                        case let (d, "ten") where d > 1 && groups.last!.0 == 0:
                            return self.tens[d]
                        case let (d, "ten") where d > 1 && groups.last!.0 > 0:
                            return self.tens[d].strip + self.hypenString
                       case let (d, "one") where (groups.count == 3 && groups[1].0 == 1) || (groups.count == 2 && groups[0].0 == 1):
//                        case let (d, "one") where contains(groups, (1, "one")):
                            return self.onesAndTeens[10 + d]
                        case let (d, "one"):
                            return self.onesAndTeens[d]
                        case _:
                            return ""
                    }
            })) + power
        }
    }
    
    func compose(var number:String)->String {
        //return empty string if numeral is empty
        if number == "" {
            return ""
        }
                
        if number[0] == "-" {
            return "minus " + compose(number.slice(start:1))
        }
        
        // "1234" becomes Array((1,"thousand"), (234, ""))
        var groups = Array(Zip2(number.reversed.group(3).map({w in w.reversed}), scale)).reverse()
        groups
        var result = "".join(groups.map({ (val, power) in self.composeScale(val, power: power)}))
        return result
    }

    func compseFraction(var number:String)->String {
        if number == "" {
            return ""
        }

        //ignore leading zero
        var i = 0
        for ; i < number.length; i++ {
            if number[i] != "0" {
                break;
            }
        }
            
        return i == number.length ? self.zero : compose(number.slice(start:i))
        
    }
    
    func convert(var numeral:String) -> String {
        //return empty string if numeral is empty
        if numeral.strip == "" {
            return ""
        }
        
        let splitNumberArr = numeral.strip.split(sep: ".")
        var cardinal = splitNumberArr[0]
        var fraction = splitNumberArr.count > 1 ? splitNumberArr[1] : ""
        
        return (compose(cardinal) + (fraction.isEmpty ? "" : andString + compseFraction(fraction) + fractionScale[fraction.length])).strip
    }
}

var n2w = NumberToWord()


var testcases = ["9223372036854775806", "0", "-1", "1", "100", "1000", "-59", "-600900", "0.1", "0.2", "0.001", "-0.0001", "0.00001"].map({x in n2w.convert(x)})
testcases







