# Bop-it-PlaygroundExpressboard
A recreation of the childhood game Bop-it on the PEB to be handheld/portable.
Game Rules:
- Game Objective: Players must react to randomized commands within the time limit to avoid failure.
- Challenge Duration: Each challenge lasts 5 seconds, but successful completions reduce the time limit by 500ms, making the game progressively harder.
- Failure Reset: If the player fails a challenge, the time limit resets to 5 seconds and they start over.
- Commands: The game randomly selects one of four possible actions:
- "Bop It!" → Press either button.
- "Switch It!" → Toggle the slide switch.
- "Yell At It!" → Increase ambient sound level significantly.
- "Shroud It!" → Decrease light level significantly.
Inputs & Sensors Used:
- Buttons: Press either the left or right button to complete "Bop It!"
- Slide Switch: Must toggle during "Switch It!" to prevent exploits.
- Sound Sensor: Measures ambient sound level.
- Success: Sound level increases by at least 75 compared to the starting value.
- Light Sensor: Detects environmental brightness.
- Success: Light level decreases by at least 25 compared to the starting value.
Game Outputs:
- Serial Monitor: Displays current sensor values, challenge type, and success/failure messages for debugging.
- LED & Sound Feedback:
- Success: Plays high-pitched tone (1000 Hz) and reduces challenge time.
- Failure: Plays low-pitched tone (200 Hz) and resets challenge time.
Best Place to Play:
✔ Moderate Light Environment: The game relies on detecting changes in brightness—playing in total darkness makes "Shroud It" impossible.
✔ Quiet or Moderate Sound Environment: Background noise in extremely loud environments can interfere with "Yell At It."
Unplayable Environments:
❌ Pitch Black Darkness → "Shroud It" cannot register a drop in light.
❌ Very Loud Rooms → "Yell At It" might auto-complete or fail unpredictably due to constant ambient noise.
