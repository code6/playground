/**
 *
 * Created by zhichunw on 7/27/15.
 */
(function () {
    'use strict';

    angular
        .module('lamuran').controller('HomeCtrl', function (UserService, $rootScope) {
            var vm = this;
            vm.email = $rootScope.globals.user.email;
        });

})();
