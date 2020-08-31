
// https://kripken.github.io/emscripten-site/docs/porting/connecting_cpp_and_javascript/Interacting-with-code.html

var ExtensionPokiJS = {
	ExtensionPokiJS_init: function() {
		PokiSDK.init().then(
			() => {
				console.log("Poki SDK successfully initialized");
				// your code to continue to game
				//continueToGame();
			}   
		).catch(
			() => {
				console.log("Initialized, but the user likely has adblock");
				// your code to continue to game
				//continueToGame();
			}   
		);
	},

	ExtensionPokiJS_set_debug: function() {
		PokiSDK.setDebug(true);
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

	ExtensionPokiJS_commercial_break: function() {
		PokiSDK.commercialBreak().then(
			() => {
				console.log("Commercial break finished, proceeding to game");
			}
		);
	},

	ExtensionPokiJS_rewarded_break: function() {
		PokiSDK.rewardedBreak().then(
			(success) => {
				console.log("Rewarded break finished, success = " + success);
			}
		);
	}
}

autoAddDeps(ExtensionPokiJS, '$ExtensionPokiJS');
mergeInto(LibraryManager.library, ExtensionPokiJS);
