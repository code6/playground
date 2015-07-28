
## Head

* [project using angular js](https://github.com/angular/angular.js/wiki/Projects-using-AngularJS)
* opensource project using angular
    * [angular-app](https://github.com/angular-app/angular-app)
* https://builtwith.angularjs.org/


## Question

* 小文件过多怎么办？比如各个页面的js需要合起来吗？


## 2015.7.26

今天打算把使用 json-server来mock 登陆/注册这个东西搞完。
主要有两个事情：

* 在 angular config module 中添加mock选项, 可以设置mock的url_prefix
    看到的一种做法是添加 url 参数，但这样的话需要一直有这个参数，方便吗？
    或许也可以添加一个测试端口? 这里突然想到 angular test，这块可能得结合起来考虑，现在先忽略吧。
    初步考虑先尝试写死路径，然后添加 mock 选项，后续再考虑跟 angular test 结合的事情。
    
* 于 json-server 交互完成注册/登陆各种场景。
    * 登陆用户名密码不正确, 用户不存在
    * 注册新用户
    * 用户登录

[json-server 如何使用](https://egghead.io/lessons/nodejs-creating-demo-apis-with-json-server)
[mocking server](http://modernweb.com/2013/09/09/mocking-server-dependencies-in-javascript-and-angularjs/)

我的计划就是边模仿的时候边学习，当然也得花点时间去把基础打的再扎实一点。

本来打算在 lamuran 里面写这个 login demo，不过考虑最后还是要删掉，可以尝试使用一下 angular-seed，顺便学习一下这个 bootstrap project 里面都用到哪些好东西。

* [html5boilerplate](https://html5boilerplate.com/)




## 2015.7.24

Question:
  * html 是放在 vm 里面还是放在 static 里面？客户端不需要用到 html 吗？
    A: 对于我现在要做的尝试这个问题不重要。如果是纯 angular 的做法的话是不需要有vm的。如果要用vm的话，就把html都放在vm里面，这样客户端来请求资源的时候再渲染一下罢了。

今天主要来学习用 angular 来快速做一下用户的注册登陆功能, 后端先用 json-server 来 fake 一下 api 调用，暂不考虑安全性。

考虑使用 $resource 来做 rest 服务了:

 * https://docs.angularjs.org/api/ngResource/service/$resource

可以参考一些已经上线的 angular 网站来观察他们是怎么做的:

* http://www.gifteng.com/?login
  这家基本都是用 api 的，全部都封装到一个 services.js 里面了，而且不直接使用 $http 而是 $resources。
* https://www.vitaliator.com/login
    这家写的挺工整的，登陆之后客户端仅存储一个 authtoken 来标记是哪个用户。全部操作基本上都是用 http 发异步请求来完成。
* http://opentaste.co/login/
    这家写的也不错。他把所有api相关的调用都封到一个 api.js 里面去了。不过貌似他的 login/signup 都是直接发post请求的，不走 api。
* https://www.fivetran.com/login
  这家用 typejavascript 。。
* https://learni.st/login
  这家混淆过了，看不懂

