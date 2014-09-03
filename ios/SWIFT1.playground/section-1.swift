import Foundation

// Challenge 10 – Bloginator (use Xcode6-Beta6)

/**
R1 – Create a constant array of String literals called “types” with the
values: technology, memes, cat videos
**/
// implement code for R1 below

let types = ["technology", "memes", "cat videos"]

func randomInt(N:Int) -> Int{
    return Int(arc4random_uniform(UInt32(N)))
}



/**
R2 – Create a BlogPost class with the following properties:

1. type – String, constant. A random value from the types
array. (Hint: you can use arc4random_uniform to randomly select a value.)
2. views – Optional Int. Set to nil.
3. author – String
4. email – String
5. order – Int. Set to zero.

Create an initializer to set the author’s name and email. Create a “teaser”
method that returns a String with the author’s name and number of views:
“Mike Smith has 5 views for this blog post”. If views are nil,
return “No one has read your blog post yet. Pity.”.
**/
// implement code for R2 below

class BlogPost {
    let type = types[randomInt(types.count)]
    var views:Int? = nil
    var author:String
    var email:String
    var order = 0
    
    init(author:String, email:String) {
        self.author = author
        self.email = email
    }
    
    func teaser() -> String {
        var ret = "No one has read your blog post yet. Pity."
        if views != nil {
            ret = "\(author)  has \(views) views for this blog post"
        }
        return ret
    }
}



/**
R3 – Create a “randomAuthor” function that returns a tuple. Then create
an “Author” struct with a “name” and “email” property. Add 5 Author structs
to a dictionary using the author’s name as the key. This function returns
a randomly selected name and email of an Author from the dictionary.
**/
// implement code for R3 below

struct Author {
    var name:String
    var email:String
    init(name:String, email:String) {
        self.name = name
        self.email = email
    }
}

var authors = [String:Author]()

authors["Bai Juyi"] = Author(name:"Bai Juyi", email:"BaiJuyi@google.com")
authors["Bai Li"] = Author(name:"Bai Li", email:"BaiLi@google.com")
authors["Du Fu"] = Author(name:"Du Fu", email:"BuFu@google.com")
authors["Yangxiu Ou"] = Author(name:"Yangxiu Ou", email:"YangxuOu@google.com")
authors["Du Mu"] = Author(name:"Du Mu", email:"DuMu@google.com")


func randomAuthor() -> (String, String) {
    var ele = authors.values.array[randomInt(authors.count)]
    return (ele.name, ele.email)
}



/**
R4 – Create an array of 10 blog posts with a for loop. Set the “author”
property to the value returned from “randomAuthor” function and set
the “order” property to the value of the index of the for loop used to
populate this array.
**/
// implement code for R4 below

var blogposts = [BlogPost]()

for i in 1...10 {
    var ele = randomAuthor()
    var post = BlogPost(author: ele.0, email: ele.1)
    post.order = i
    blogposts.append(post)
}


/**
R5 – Create a “randomViews” function that accepts the “type” of blog post
for an input. Create an array literal of Ints (these are the possible view
counts) with the values: 10, 20, 30, 40, 50. Select a random value from
this possible view count array and create a switch that returns nil if
the views are 10, 0 if the views are either 20 or 30, else return the randomly
selected number of views. If the “type” passed to the function is
“cat videos” always return nil.
**/
// implement code for R5 below

func randomViews(type:String)->Int? {
    if type == "cat videos" {
        return nil
    }
    let possibleViewCounts = [10, 20, 30, 40, 50]
    var viewCount = possibleViewCounts[randomInt(possibleViewCounts.count)]
    switch viewCount {
    case 10:
        return nil
    case 20, 30:
        return 0
    default:
        return viewCount
    }
}


/**
R6 – Iterate the array of blog posts, generate a value from “randomViews” function
for each one and set it to the blog post “views” property. Then println the
value of each post.teaser().
**/
// implement code for R6 below
for post in blogposts {
    var view = randomViews(post.type)
    post.views = view
    println(post.teaser())
}



/**
R7 – Write a simple stack using a struct with Generics
that has three methods. It should push and pop BlogPosts and also
returns the current count of BlogPosts. Iterate the array of blog posts
and push each one onto the “blogs” stack. Println the count of items in
the stack. Use a for loop to iterate the “blogs” stack, pop the top one
off and println the blog’s teaser. Println the count of items in the stack.
**/
// implement code for R7 below


struct Stack<ItemType> {
    var arr = [ItemType]()
    mutating func push(item: ItemType) {
        arr.append(item)
    }
    mutating func pop()->ItemType {
        return arr.removeLast()
    }
    func count()->Int {
        return arr.count
    }
}

var stackOfBlogPosts = Stack<BlogPost>();

for post in blogposts {
    stackOfBlogPosts.push(post)
}

stackOfBlogPosts.count()

for i in 1...stackOfBlogPosts.count() {
    var post = stackOfBlogPosts.pop()
    println(post.teaser())
}

stackOfBlogPosts.count()


