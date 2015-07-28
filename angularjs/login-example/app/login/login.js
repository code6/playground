(function () {
    'use strict';
    angular.module('app').controller('LoginCtrl', ['$location', 'UserService', 'FlashService', function ($location, UserService, FlashService) {
        var vm = this;

        vm.login = login;

        function login() {
            vm.dataLoading = true;
            UserService.Login.query({'email': vm.email, 'password': vm.password}, function (users) {
                if (users.length > 0) {
                    $location.path('/');
                } else {
                    FlashService.Error("Email or password is incorrect.");
                    vm.dataLoading = false;
                }
            }, function (response) {
                FlashService.Error("Email or password is incorrect.");
                vm.dataLoading = false;
            });
        }
    }]);
})();