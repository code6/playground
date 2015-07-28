/**
 * Created by zhichunw on 7/27/15.
 */
(function () {
    'use strict';
    angular.module('app').factory('UserService', ['$rootScope', '$resource',
        function ($rootScope, $resource) {
            return {
                Register: $resource($rootScope.buildResourceUrl('api/user/register'), {}, {}),
                Login: $resource($rootScope.buildResourceUrl('api/user/login/'), {}, {}),
            }
        }]);
})();