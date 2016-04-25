/**
 * @file
 * JS functions for quicktab remember.
 */

(function($) {
  Drupal.behaviors.quicktabs_remember = {
    attach: function(context, settings) {
      $('.quicktabs-tabs > li > a', context).on('click', function() {
        var quickTabName = Drupal.quicktabs.getQTName($(this).closest('.quicktabs-wrapper').get(0));
        var currentTabId = $(this).attr('id');
        var tabName = currentTabId.substring(currentTabId.lastIndexOf('-') + 1);
        $.get('quicktab_update/' + quickTabName + '/' + tabName);
      });
    }
  };
})(jQuery);
