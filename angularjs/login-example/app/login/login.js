(function () {
    'use strict';
    angular.module('lamuran').controller('LoginCtrl', function ($location, UserService, FlashService) {
        var vm = this;

        vm.login = login;

        function login() {
            vm.dataLoading = true;
            UserService.login(vm.email, vm.password, function (response) {
                if (response.success) {
                    UserService.set_credentials(vm.email, vm.password);
                    $location.path('/');
                } else {
                    FlashService.Error("Email or password is incorrect.");
                    vm.dataLoading = false;
                }
            });
        }
    });
})();