(function () {
    'use strict';
    angular.module('app').controller('RegisterCtrl', ['$location', 'UserService', 'FlashService', function ($location, UserService, FlashService) {
        var vm = this;

        vm.register = register;

        function register() {
            vm.dataLoading = true;
            new UserService.Register({'email': vm.email, 'password': vm.password}).$save(function (response) {
                if (response.success) {
                    FlashService.Success('Registration successful', true);
                    $location.path('/login');
                } else {
                    FlashService.Error(response.message);
                    vm.dataLoading = false;
                }
            });
        }
    }]);
})();