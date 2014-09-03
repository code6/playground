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
    func slice(start:Int=0, end:Int?=nil) -> String {
        let s = self as NSString
        var new_end:Int
        if ((end) != nil) {
            new_end = end!
        } else {
            new_end = s.length
        }
        return  s.substringWithRange(NSRange(location: start, length:new_end - start))
    }
    func split(sep:String = "") -> [String] {
        return self.componentsSeparatedByString(sep)
    }
    var strip:String {
        return self.stringByTrimmingCharactersInSet(NSCharacterSet.whitespaceAndNewlineCharacterSet())
    }
}

func splitWordString(var s:String) -> [String] {
    return s.split(sep: " ").filter({w in !w.strip.isEmpty}).map({w in w.strip + " "})
}

class NumberToWord {
    let zero = "zero"
    let tens = splitWordString("unit ten  twenty  thirty  forty  fifty  sixty  seventy  eighty  ninety")
    let onesAndTeens = splitWordString("one  two  three  four  five  six  seven  eight  nine  eleven  twelve  thirteen fourteen fifteen sixteen seventeen  eighteen nineteen")
    let handred = "hunderd "
    let scale = [""] + splitWordString("thousand million billion trillion quadrillion sextillion septillion octillion nontillion decillion ")
    
    var andString:String
    var hypenString:String
    
    init(showAnd: Bool = true, showHypen: Bool = true) {
        self.andString = showAnd ? "and " : ""
        self.hypenString = showHypen ? "-" : " "
    }
    
    func compose(var number:String)->String {
        //return empty string if numeral is empty
        if number == "" {
            return ""
        }
        
        
        if number[0] == "-" {
            return "minus " + compose(number.slice(start:1))
        }
        
        //if (numeral) "minus " + compose(-numeral) else compose(numeral)
        return ""
    }
    
    func convert(var numeral:String) -> String {
        //return empty string if numeral is empty
        if numeral.strip == "" {
            return ""
        }
        
        let splitNumberArr = numeral.strip.split(sep: ".")
        var cardinal = splitNumberArr[0]
        var fraction = splitNumberArr.count > 1 ? splitNumberArr[1] : ""
        
        return compose(cardinal) + (fraction.isEmpty ? "" : andString) + compose(fraction)
    }
}




NumberToWord().onesAndTeens
NumberToWord().tens
NumberToWord().scale




