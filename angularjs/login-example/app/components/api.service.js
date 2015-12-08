/**
 * Created by zhichunw on 7/30/15.
 */
(function () {
    'use strict';
    /* API component */
    angular.module('lamuran.components.api', [])
        .factory('ApiService', function ($rootScope, $http) {
            var get, post;
            get = function (url) {
                return function (params) {
                    return $http.get($rootScope.API_PREFIX + url, {'params': params});
                };
            };
            post = function (url) {
                return function (data) {
                    return $http.post($rootScope.API_PREFIX + url, data);
                };
            };
            return {
                'user': {
                    'login': get("/user/login"),
                    'register': post("/user/register")
                }
            };
        });
})();