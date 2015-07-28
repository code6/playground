(function () {
    'use strict';

// Declare app level module which depends on views, and components
    angular.module('app', [
        'ngRoute',
        'ngResource',
    ]).config(['$routeProvider', function ($routeProvider) {
        $routeProvider
            .when('/', {
                controller: 'HomeCtrl',
                templateUrl: 'home/home.html',
                controllerAs: 'vm'
            })
            .when('/login', {
                controller: 'LoginCtrl',
                templateUrl: 'login/login.html',
                controllerAs: 'vm'
            })
            .when('/register', {
                controller: 'RegisterCtrl',
                templateUrl: 'register/register.html',
                controllerAs: 'vm'
            })
            .otherwise({redirectTo: '/login'});
    }]).run(['$rootScope', function ($rootScope) {
        $rootScope.buildResourceUrl = function (path) {
            return "http://localhost:3000/" + path;
        };
    }]);
})();
