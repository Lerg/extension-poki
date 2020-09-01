# Poki Extension for Defold

This extension allows you to distribute your game on the [Poki](https://poki.com) platform.

# Setup

Paste this URL as a dependency in your `game.project` file.

```
https://github.com/Lerg/extension-poki/archive/master.zip
```

# API Reference

# Functions

## poki.init(callback)

### callback - function, called when the extension has been initialized.

Initializes the extension.

---

## poki.set_debug(is_debug)

### is_debug - boolean, enabled if `true`.

Sets debugging state.

---

## poki.game_loading_start()

Indicates that the game has started loading.

---

## poki.game_loading_finished()

Indicates that the game has finished loading.

---

## poki.gameplay_start()

Indicates that the gameplay has started.

---

## poki.gameplay_stop()

Indicates that the gameplay has stopped.

---

## poki.commercial_break(callback)

### callback - function, called when the break is over.

Activates a commercial break.

---

## poki.rewarded_break(callback)

### callback - function, called when the break is over with the success argument, boolean.

Activates a rewarded break.

### Syntax

```language-lua
poki.rewarded_break(function(success)
    if success then
        -- Give reward.
    end
end)
```

---

## poki.happy_time(intensity)

### intensity - number, happiness level, from 0.0 to 1.0.

Indicate a happy moment for the player.

# Properties

## poki.is_initialized

Becomes `true` when the extension has been initialized.

---

## poki.is_ads_blocked

Becomes `true` if during the initialization Poki detects that the user likely has an ad blocker.