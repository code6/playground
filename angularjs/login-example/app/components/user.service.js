/**
 * Created by zhichunw on 7/27/15.
 */
(function () {
    'use strict';
    angular.module('lamuran.components.user', ['lamuran.components.api']).factory('UserService', function (ApiService, $rootScope) {
        var service = {};

        service.login = login;
        service.register = register;
        service.set_credentials = set_credentials;
        service.clear_credentials = clear_credentials;

        return service;

        function login(email, password, callback) {
            ApiService.user.login({"email": email, "password": password}).then(function (result) {
                var response;
                if (result.data.length > 0) {
                    response = {success: true};
                } else {
                    response = {success: false, message: "Username or password is incorrect"}
                }
                callback(response);
            })
        }

        function register(email, password, callback) {
            ApiService.user.register({"email": email, "password": password}).then(function (result) {
                var response;
                console.log(result);
                if (result.data) {
                    response = {success: true};
                } else {
                    response = {success: false, message: "Register error"}
                }
                callback(response);
            });
        }

        function set_credentials(email, password) {
            $rootScope.globals = {
                user: {
                    email: email,
                }
            }
        }
        function clear_credentials() {
            $rootScope.globals = {}
        }
    });
})();