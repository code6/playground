
## Head

* [project using angular js](https://github.com/angular/angular.js/wiki/Projects-using-AngularJS)
* opensource project using angular
    * [angular-app](https://github.com/angular-app/angular-app)
* https://builtwith.angularjs.org/

## 2015.7.24

Question:
  * html 是放在 vm 里面还是放在 static 里面？客户端不需要用到 html 吗？

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

