(function () {
    'use strict';
    angular.module('lamuran').controller('RegisterCtrl', function ($location, UserService, FlashService) {
        var vm = this;

        vm.register = register;

        function register() {
            vm.dataLoading = true;
            UserService.register(vm.email, vm.password, function (response) {
                if (response.success) {
                    FlashService.Success('Registration successful', true);
                    UserService.set_credentials(vm.email, vm.password);
                    $location.path('/');
                } else {
                    FlashService.Error(response.message);
                    vm.dataLoading = false;
                }
            });
        }
    });
})();