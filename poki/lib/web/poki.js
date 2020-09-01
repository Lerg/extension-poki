
var extension = {
	ExtensionPokiJS_init: function(callback) {
		PokiSDK.init().then(
			() => {
				Module.dynCall_vi(callback, [0]);
			}   
		).catch(
			() => {
				Module.dynCall_vi(callback, [1]);
			}   
		);
	},

	ExtensionPokiJS_set_debug: function(is_debug) {
		PokiSDK.setDebug(is_debug);
	},

	ExtensionPokiJS_game_loading_start: function() {
		PokiSDK.gameLoadingStart();
	},

	ExtensionPokiJS_game_loading_finished: function() {
		PokiSDK.gameLoadingFinished();
	},

	ExtensionPokiJS_gameplay_start: function() {
		PokiSDK.gameplayStart();
	},

	ExtensionPokiJS_gameplay_stop: function() {
		PokiSDK.gameplayStop();
	},

	ExtensionPokiJS_commercial_break: function(callback) {
		PokiSDK.commercialBreak().then(
			() => {
				Module.dynCall_v(callback);
			}
		);
	},

	ExtensionPokiJS_rewarded_break: function(callback) {
		PokiSDK.rewardedBreak().then(
			(success) => {
				Module.dynCall_vi(callback, [success ? 1 : 0]);
			}
		);
	},

	ExtensionPokiJS_happy_time: function(intensity) {
		PokiSDK.happyTime(intensity);
	}
}

mergeInto(LibraryManager.library, extension);
