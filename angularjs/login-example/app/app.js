(function () {
    'use strict';

// Declare app level module which depends on views, and components
    angular.module('lamuran', [
        'ngRoute',
        'ngResource',
        'lamuran.components.user',
        'lamuran.components.flash',
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
    }]).run(function ($rootScope, $location) {
        $rootScope.API_PREFIX = "http://localhost:3000/api";
        $rootScope.$on('$locationChangeStart', function (event, next, current) {
            // redirect to login page if not logged in and trying to access a restricted page
            var restrictedPage = $location.path() == '/';
            var loggedIn = $rootScope.globals != undefined;
            if (restrictedPage && !loggedIn) {
                $location.path('/login');
            }
        });
    });
})();
